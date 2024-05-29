#ifndef BIN_TO_HEX_HPP
#define BIN_TO_HEX_HPP

#include <charconv>
#include <span>
#include <string>
#include <stdexcept>

namespace tap_reader {

// Convert n bytes of binary data to hex string
template<class T>
requires std::is_standard_layout_v<T>
std::string bin_to_hex(const T& data, size_t n) {

    if (n > sizeof(T)) {
        throw std::invalid_argument("n > sizeof(T)");
    }

    auto bytes = std::span<const unsigned char>(
        reinterpret_cast<const unsigned char*>(&data) // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
        , n
    );

    std::string hex(n + n, '\0');
    size_t i = 0;
    // for (size_t i = 0; i < n + n; ++i) {
    for (const auto& byte : bytes) {
        auto res = std::to_chars(hex.data() + i, hex.data() + i + 2, byte, 16);
        if (res.ec != std::errc()) {
            throw std::invalid_argument("error converting byte to hex");
        }

        // If the result is only one digit add a leading zero
        if (res.ptr == hex.data() + i + 1) {
            *(hex.data() + i + 1)  = *(hex.data() + i);
            *(hex.data() + i) = '0';
        }
        i += 2;
    }

    return hex;
}

}

#endif // BIN_TO_HEX_HPP
