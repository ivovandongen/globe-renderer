#pragma once

#include <glbr/io/data_source.hpp>

namespace glbr {
namespace io {

class HttpDataSource : public DataSource {
public:
    ~HttpDataSource() override = default;

    static std::unique_ptr<HttpDataSource> Create();
};

}  // namespace io
}  // namespace glbr
