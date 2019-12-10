#pragma once

#include <glbr/core/concurrent/scheduler.hpp>

#include "http_request.hpp"

#include <curl/curl.h>

#include <atomic>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>

namespace glbr {
namespace io {

class HttpRequestHandle;

class HttpDataSourceCurlWorker {
public:
    HttpDataSourceCurlWorker();

    ~HttpDataSourceCurlWorker();

    void schedule(std::weak_ptr<HttpRequestHandle>);

    void cleanup(HttpRequestHandle *handle);

private:
    std::mutex pendingRequestsMutex_;
    std::queue<std::weak_ptr<HttpRequestHandle>> pendingRequests_;

    std::mutex staleHandlesMutex_;
    std::queue<HttpRequestHandle *> staleHandlesPool_;

    std::mutex loopMutex;
    std::condition_variable cv_;

private:
    void activatePendingRequests();
    void cleanupStaleHandles();

private:
    CURLSH *share_;
    CURLM *multi_;

    std::atomic_bool running{true};
    std::thread thread;
};

class HttpRequestHandle : public std::enable_shared_from_this<HttpRequestHandle> {
public:
    HttpRequestHandle(Resource resource, DataSource::Callback callback);

    std::string body{};

private:
    friend class HttpDataSourceCurlWorker;
    friend class HttpDataSourceCurlImpl;

    void onResult(CURLcode param);

private:
    Resource resource_;
    DataSource::Callback callback_;
    core::concurrent::Scheduler *scheduler_;
    CURL *curl_ = nullptr;
};

}  // namespace io
}  // namespace glbr