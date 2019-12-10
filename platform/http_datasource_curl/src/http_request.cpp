#include "http_request.hpp"

#include <memory>

namespace glbr {
namespace io {

HttpRequest::HttpRequest(std::shared_ptr<HttpRequestHandle> handle) : handle_(std::move(handle)) {}

}  // namespace io
}  // namespace glbr