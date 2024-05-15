#ifndef BIN_TO_HEX_HPP
#define BIN_TO_HEX_HPP

#include <iostream>
#include <iomanip>
#include <span>
#include <sstream>
#include <string>


namespace tap_reader {

template<class T>
requires std::is_standard_layout_v<T>
std::string bin_to_hex(const T& data, size_t count) {

    if (count >= sizeof(T)) {
        throw std::invalid_argument("count >= sizeof(T)");
    }

    auto bytes = std::span<const std::byte>(
        reinterpret_cast<const std::byte*>(&data) // NOLINT
        , count
    );

    std::stringstream ss;
    ss << std::hex << std::setfill('0');

    for (const auto& byte : bytes) {
        ss << std::setw(2) << static_cast<unsigned int>(byte);
    }

    return ss.str();
}

}

#endif // BIN_TO_HEX_HPP
