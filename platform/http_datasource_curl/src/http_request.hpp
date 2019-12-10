#pragma once

#include <glbr/io/data_source.hpp>

#include <memory>

namespace glbr {
namespace io {

class HttpRequestHandle;

class HttpRequest : public AsyncRequest {
public:
    explicit HttpRequest(std::shared_ptr<HttpRequestHandle> handle);

    ~HttpRequest() override = default;

public:
    std::shared_ptr<HttpRequestHandle> handle_;
};

}  // namespace io
}  // namespace glbr