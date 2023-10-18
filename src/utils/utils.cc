#include "utils.h"
#include <sstream>

std::string hex64(uint64_t value) {
    std::stringstream out;

    for (int i = 60; i >= 0; i -= 4) {
        int k = (value >> i) & 0xf;

        if (k < 10) {
            out << (char) ('0' + k);
        } else {
            out << (char) ('a' + k - 10);
        }
    }

    return out.str();
}

std::string hex8(uint64_t value) {
    std::stringstream ss;

    for (int i = 4; i >= 0; i -= 4) {
        int k = (value >> i) & 0xf;

        if (k < 10) {
            ss << ((char) ('0' + k));
        } else {
            ss << ((char) ('a' + k - 10));
        }
    }

    return ss.str();
}
