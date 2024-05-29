#ifndef HEX_TO_BIN_HPP
#define HEX_TO_BIN_HPP 

#include <charconv>
#include <format>
#include <stdexcept>
#include <string>
#include <array>

namespace tap_reader_tests {

template<size_t SIZE>
[[nodiscard]]
std::array<unsigned char, SIZE> hex_to_bin(const std::string& hex) {

    if (hex.size() > SIZE * 2) {
        throw std::invalid_argument("hex string is too long");
    }
    if (hex.size() % 2 != 0) {
        throw std::invalid_argument("hex string must have even length");
    }

    std::array<unsigned char, SIZE> arr{};

    size_t j = 0;
    for (std::size_t i = 0; i < hex.size(); i += 2) {
        unsigned int byte = 0;
        const auto *last = hex.data() + i + 2;
        auto res = std::from_chars(hex.data() + i, last, byte, 16); // NOLINT
        if (res.ec != std::errc() || res.ptr != last) {
            throw std::invalid_argument(std::format("invalid hex char in string: {}, idx: {}", hex, i));
        }
        arr.at(j++) = static_cast<unsigned char>(byte);
    }

    return arr;
}

}

#endif // HEX_TO_BIN_HPP 

