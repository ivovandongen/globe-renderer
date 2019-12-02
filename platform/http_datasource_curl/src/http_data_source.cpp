#include <glbr/io/http_data_source_curl.hpp>

#include <glbr/core/concurrent/scheduler.hpp>
#include <glbr/logging/logging.hpp>

#include "http_data_source_worker.hpp"
#include "http_request.hpp"

#include <curl/curl.h>

#include <atomic>
#include <cassert>
#include <memory>
#include <thread>

namespace glbr {
namespace io {

// TODO error checking on each curl_* call

HttpDataSourceCurlWorker::HttpDataSourceCurlWorker() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    share_ = curl_share_init();
    multi_ = curl_multi_init();

    thread = std::thread([&] {
        int transfers_running;
        do {
            std::unique_lock<std::mutex> lock(mutex_);
            curl_multi_wait(multi_, nullptr, 0, 1000, nullptr);
            curl_multi_perform(multi_, &transfers_running);
            CURLMsg *message = nullptr;
            while ((message = curl_multi_info_read(multi_, &transfers_running))) {
                lock.unlock();
                HttpRequest *request = nullptr;
                curl_easy_getinfo(message->easy_handle, CURLINFO_PRIVATE, (char *)&request);
                request->onResult(message->data.result);
                lock.lock();
            }
        } while (running);
        logging::info("DataSourceCurlWorker loop exiting");
    });
}

HttpDataSourceCurlWorker::~HttpDataSourceCurlWorker() {
    running = false;
    thread.join();
    curl_multi_cleanup(multi_);
    multi_ = nullptr;
    curl_share_cleanup(share_);
    share_ = nullptr;
    curl_global_cleanup();
}

void HttpDataSourceCurlWorker::addJob(CURL *curl) {
    std::unique_lock<std::mutex> lock(mutex_);
    // Start requesting the information.
    curl_easy_setopt(curl, CURLOPT_SHARE, share_);
    curl_multi_add_handle(multi_, curl);
}

void HttpDataSourceCurlWorker::removeJob(CURL *curl) {
    std::unique_lock<std::mutex> lock(mutex_);
    curl_multi_remove_handle(multi_, curl);
}

HttpRequest::HttpRequest(HttpDataSourceCurlWorker *worker, const Resource &resource, DataSource::Callback callback)
    : worker_(worker), callback_(std::move(callback)), scheduler_(core::concurrent::Scheduler::Get()) {
    assert(scheduler_);
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(curl, CURLOPT_PRIVATE, this);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, onWrite);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
    curl_easy_setopt(curl, CURLOPT_URL, resource.url().c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);

    worker->addJob(curl);
}

HttpRequest::~HttpRequest() {
    worker_->removeJob(curl);

    /* always cleanup */
    curl_easy_cleanup(curl);
}

size_t HttpRequest::onHeader(char *buffer, size_t size, size_t nmemb, void *userp) {
    // TODO
    return 0;
}

size_t HttpRequest::onWrite(void *contents, size_t size, size_t nmemb, void *userp) {
    assert(userp);
    auto request = reinterpret_cast<HttpRequest *>(userp);
    request->body.append((char *)contents, size * nmemb);
    return size * nmemb;
}

void HttpRequest::onResult(CURLcode curlCode) {
    // TODO: Error checking
    if (curlCode == CURLE_OK) {
        long httpResponseCode = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpResponseCode);
        logging::info("Response code: {}", httpResponseCode);
    }

    // Schedule the callback on the caller's thread scheduler
    scheduler_->schedule([cb = std::move(callback_), response = Response{std::move(body)}]() mutable {
        // Make sure to move the response as we don't want copies of the response data all over the place
        cb(std::move(response));
    });
}

std::unique_ptr<HttpDataSource> HttpDataSource::Create() {
    return std::make_unique<HttpDataSourceCurlImpl>();
}

HttpDataSourceCurlImpl::HttpDataSourceCurlImpl() : worker(std::make_unique<HttpDataSourceCurlWorker>()) {
    logging::info("Creating a new CURL HttpDataSource");
}

HttpDataSourceCurlImpl::~HttpDataSourceCurlImpl() {
    logging::info("Destroying CURL HttpDataSource");
}

std::unique_ptr<AsyncRequest> HttpDataSourceCurlImpl::load(const Resource &resource, DataSource::Callback cb) {
    return std::make_unique<HttpRequest>(worker.get(), resource, std::move(cb));
}

}  // namespace io
}