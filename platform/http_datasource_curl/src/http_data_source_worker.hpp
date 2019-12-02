#pragma once

#include <curl/curl.h>

#include <atomic>
#include <mutex>
#include <thread>

namespace glbr {
namespace io {

class HttpDataSourceCurlWorker {
public:
    HttpDataSourceCurlWorker();

    ~HttpDataSourceCurlWorker();

    void addJob(CURL *curl);
    void removeJob(CURL *curl);

private:
    std::mutex mutex_;
    std::atomic_bool running{true};
    std::thread thread;

    CURLSH *share_;
    CURLM *multi_;
};

}  // namespace io
}  // namespace glbr