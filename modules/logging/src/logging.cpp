#include <glbr/logging/logging.hpp>

namespace glbr {
namespace logging {

void setLevel(const Level &level) {
    spdlog::set_level([&level]() {
        switch (level) {
            case Level::DEBUG:
                return spdlog::level::debug;
            case Level::WARN:
                return spdlog::level::warn;
            case Level::ERROR:
                return spdlog::level::err;
            default:
                return spdlog::level::info;
        }
    }());
}

}  // namespace logging
}  // namespace glbr