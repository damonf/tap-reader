#ifndef FRAME_HPP
#define FRAME_HPP

#include <array>
namespace tap_reader {

struct Frame {
    constexpr static std::size_t BUF_SIZE = 4UL * 1024;

    std::array<std::byte, 6> dest_mac_;
    std::array<std::byte, 6> src_mac;
    std::array<std::byte, 2> lentype_;
    std::array<std::byte, BUF_SIZE> buffer_;
};

}

#endif // FRAME_HPP

