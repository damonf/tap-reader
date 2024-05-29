#ifndef FRAME_HPP
#define FRAME_HPP

#include "constants.hpp"

#include <array>

namespace tap_reader {

struct Frame {
    std::array<unsigned char, MAC_SIZE> dest_mac_;
    std::array<unsigned char, MAC_SIZE> src_mac_;
    std::array<unsigned char, LENTYPE_SIZE> lentype_;
    std::array<unsigned char, BUF_SIZE> buffer_;
};

}

#endif // FRAME_HPP

