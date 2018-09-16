#pragma once

#include <string>
#include <sstream>

namespace NFlappyBird {
    template<typename T>
    std::string toString(T t) {
        std::stringstream ss;

        ss << t;

        return ss.str();
    }
}
