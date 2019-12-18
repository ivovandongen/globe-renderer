#pragma once

#include <glbr/core/expected.hpp>

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

class Error {
public:
    enum class Type { NOT_FOUND, BAD_REQUEST, SERVER_ERROR, OTHER };

    Error(Type type, std::string message) : type_(type), message_(std::move(message)) {}

    Type code() const { return type_; }
    const std::string& message() const { return message_; };

private:
    std::string message_;
    Type type_;
};

class DataSource {
public:
    using ResponseHolder = core::expected<Response, Error>;
    using Callback = std::function<void(ResponseHolder)>;
    virtual ~DataSource() = default;
    virtual std::unique_ptr<AsyncRequest> load(const Resource&, Callback cb) = 0;
};

}  // namespace io
}  // namespace glbr