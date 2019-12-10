#include <glbr/io/http_data_source_curl.hpp>

#include <glbr/logging/logging.hpp>

#include "http_data_source_curl_worker.hpp"
#include "http_request.hpp"

#include <memory>

namespace glbr {
namespace io {

std::unique_ptr<HttpDataSource> HttpDataSource::Create() {
    return std::make_unique<HttpDataSourceCurlImpl>();
}

HttpDataSourceCurlImpl::HttpDataSourceCurlImpl() : worker(std::make_unique<HttpDataSourceCurlWorker>()) {
    logging::info("Creating a new CURL HttpDataSource");
}

HttpDataSourceCurlImpl::~HttpDataSourceCurlImpl() {
    logging::info("Destroying CURL HttpDataSource");
}

std::unique_ptr<AsyncRequest> HttpDataSourceCurlImpl::load(const Resource& resource, DataSource::Callback cb) {
    std::shared_ptr<HttpRequestHandle> handle(new HttpRequestHandle(resource, std::move(cb)),
                                              [worker = this->worker.get()](HttpRequestHandle* handle) {
                                                  if (worker) {
                                                      worker->cleanup(handle);
                                                  } else {
                                                      delete handle;
                                                  }
                                              });
    worker->schedule(handle);
    return std::make_unique<HttpRequest>(std::move(handle));
}

}  // namespace io
}  // namespace glbr
