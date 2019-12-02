#pragma once

#include <functional>
#include <memory>
#include <string>
#include <utility>

namespace glbr {
namespace io {

class AsyncRequest {
public:
    virtual ~AsyncRequest() = default;
};

class Resource {
public:
    explicit Resource(std::string url) : url_(std::move(url)) {}

    std::string url() const { return url_; }

private:
    std::string url_;
};

class Response {
public:
    explicit Response(std::string data) : data_(std::move(data)) {}

    const std::string& data() const { return data_; };
    std::string& data() { return data_; };

private:
    std::string data_;
};

class DataSource {
public:
    using Callback = std::function<void(Response)>;
    virtual ~DataSource() = default;
    virtual std::unique_ptr<AsyncRequest> load(const Resource&, Callback cb) = 0;
};

}  // namespace io
}  // namespace glbr