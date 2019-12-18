#pragma once

#include <glbr/io/http_data_source.hpp>

#include <memory>

namespace glbr {
namespace io {

class HttpDataSourceCurlWorker;

class HttpDataSourceCurlImpl : public HttpDataSource {
public:
    HttpDataSourceCurlImpl();
    ~HttpDataSourceCurlImpl() override;

    std::unique_ptr<AsyncRequest> load(const Resource& resource, Callback cb) override;

private:
    std::shared_ptr<HttpDataSourceCurlWorker> worker;
};

}  // namespace io
}  // namespace glbr
