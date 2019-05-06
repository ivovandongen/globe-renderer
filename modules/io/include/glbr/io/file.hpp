#pragma once

#include <fstream>
#include <iostream>
#include <streambuf>
#include <string>

namespace glbr {
namespace io {

std::string readFile(const std::string &fileName) {
    std::ifstream t(fileName);
    std::string result;

    if (t.is_open()) {
        t.seekg(0, std::ios::end);
        result.reserve(t.tellg());
        t.seekg(0, std::ios::beg);

        result.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
    } else {
        throw std::runtime_error{std::string{"Could not open file: "} + fileName};
    }

    return result;
}

}  // namespace io
}  // namespace glbr
