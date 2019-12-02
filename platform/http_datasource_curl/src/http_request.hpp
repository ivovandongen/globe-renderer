#pragma once

#include "http_data_source_worker.hpp"

#include <curl/curl.h>

namespace glbr {
namespace io {

class HttpRequest : public AsyncRequest {
public:
    static size_t onHeader(char *buffer, size_t size, size_t nmemb, void *userp);
    static size_t onWrite(void *contents, size_t size, size_t nmemb, void *userp);

    HttpRequest(HttpDataSourceCurlWorker *worker, const Resource &resource, DataSource::Callback callback);

    ~HttpRequest() override;

    void onResult(CURLcode param);

public:
    std::string body;

private:
    DataSource::Callback callback_;
    CURL *curl;
    HttpDataSourceCurlWorker *worker_;
    core::concurrent::Scheduler *scheduler_;
};

}  // namespace io
}  // namespace glbr