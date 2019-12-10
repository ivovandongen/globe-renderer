#include <glbr/io/http_data_source_curl.hpp>

#include <glbr/core/concurrent/scheduler.hpp>
#include <glbr/logging/logging.hpp>

#include "http_data_source_curl_worker.hpp"
#include "http_request.hpp"

#include <curl/curl.h>

#include <array>
#include <atomic>
#include <cassert>
#include <memory>
#include <thread>
#include <utility>

namespace glbr {
namespace io {

// TODO error checking on each curl_* call

static size_t onHeader(char *buffer, size_t size, size_t nmemb, void *userp) {
    // TODO
    assert(userp);
    auto request = reinterpret_cast<HttpRequestHandle *>(userp);
    assert(request);
    return size * nmemb;
}

static size_t onWrite(void *contents, size_t size, size_t nmemb, void *userp) {
    assert(userp);
    auto request = reinterpret_cast<HttpRequestHandle *>(userp);
    assert(request);
    request->body.append((char *)contents, size * nmemb);
    return size * nmemb;
}

HttpDataSourceCurlWorker::HttpDataSourceCurlWorker() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    share_ = curl_share_init();
    multi_ = curl_multi_init();

    thread = std::thread([&] {
        int transfers_running;
        while (running) {
            activatePendingRequests();

            do {
                curl_multi_wait(multi_, nullptr, 0, 1000, nullptr);
                curl_multi_perform(multi_, &transfers_running);
            } while (transfers_running);

            cleanupStaleHandles();

            CURLMsg *message = nullptr;
            while ((message = curl_multi_info_read(multi_, &transfers_running))) {
                HttpRequestHandle *request = nullptr;
                curl_multi_remove_handle(multi_, message->easy_handle);
                curl_easy_getinfo(message->easy_handle, CURLINFO_PRIVATE, (char *)&request);
                assert(request);
                request->onResult(message->data.result);
            };

            std::unique_lock<std::mutex> lock(loopMutex);
            if (running) {
                // Idle while we're waiting for new jobs
                cv_.wait(lock);
            }
        }
        logging::info("DataSourceCurlWorker loop exiting");
    });
}

HttpDataSourceCurlWorker::~HttpDataSourceCurlWorker() {
    {
        std::unique_lock<std::mutex> lock(loopMutex);
        running = false;
    }
    cv_.notify_one();
    thread.join();

    cleanupStaleHandles();

    curl_multi_cleanup(multi_);
    multi_ = nullptr;

    curl_share_cleanup(share_);
    share_ = nullptr;

    curl_global_cleanup();
}

void HttpDataSourceCurlWorker::schedule(std::weak_ptr<HttpRequestHandle> handle) {
    {
        std::lock_guard<std::mutex> lock(pendingRequestsMutex_);
        pendingRequests_.push(std::move(handle));
    }
    cv_.notify_one();
}

void HttpDataSourceCurlWorker::cleanup(HttpRequestHandle *handle) {
    {
        try {
            std::unique_lock<std::mutex> lock(staleHandlesMutex_);
            staleHandlesPool_.push(handle);
        } catch (...) {
            delete handle;
        };
    }
    cv_.notify_one();
}

void HttpDataSourceCurlWorker::activatePendingRequests() {
    std::lock_guard<std::mutex> lock(pendingRequestsMutex_);
    while (!pendingRequests_.empty()) {
        auto reqHandle = std::move(pendingRequests_.front());
        pendingRequests_.pop();
        auto request = reqHandle.lock();
        if (request) {
            request->curl_ = curl_easy_init();
            CURL *curl = request->curl_;
            auto *ptr = request.get();

            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
            curl_easy_setopt(curl, CURLOPT_PRIVATE, ptr);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, onWrite);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, ptr);
            curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, onHeader);
            curl_easy_setopt(curl, CURLOPT_HEADERDATA, ptr);
            curl_easy_setopt(curl, CURLOPT_URL, request->resource_.url().c_str());
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
            curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "gzip, deflate");
            curl_easy_setopt(curl, CURLOPT_SHARE, share_);

            // Actually start the request
            curl_multi_add_handle(multi_, curl);
        }
    }
}

void HttpDataSourceCurlWorker::cleanupStaleHandles() {
    std::unique_lock<std::mutex> lock(staleHandlesMutex_);
    while (!staleHandlesPool_.empty()) {
        auto *handle = staleHandlesPool_.front();
        staleHandlesPool_.pop();
        curl_multi_remove_handle(multi_, handle->curl_);
        curl_easy_cleanup(handle->curl_);
        delete handle;
    }
}

HttpRequestHandle::HttpRequestHandle(Resource resource, DataSource::Callback callback)
    : resource_(std::move(resource)), callback_(std::move(callback)), scheduler_(core::concurrent::Scheduler::Get()) {
    assert(scheduler_);
}

void HttpRequestHandle::onResult(CURLcode curlCode) {
    // TODO: Error checking
    if (!curl_) {
        return;
    }

    if (curlCode == CURLE_OK) {
        long httpResponseCode = 0;
        curl_easy_getinfo(curl_, CURLINFO_RESPONSE_CODE, &httpResponseCode);
        logging::info("Response code: {}", httpResponseCode);
    }

    // Schedule the callback on the caller's thread scheduler
    assert(callback_);
    scheduler_->schedule([handleRef = std::weak_ptr<HttpRequestHandle>(shared_from_this())]() mutable {
        // Make sure to move the response as we don't want copies of the response data all over the place
        auto handle = handleRef.lock();
        if (handle) {
            handle->callback_(Response{std::move(handle->body)});
        }
    });
};

}  // namespace io
}  // namespace glbr
