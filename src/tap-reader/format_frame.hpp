#ifndef FORMAT_FRAME_HPP
#define FORMAT_FRAME_HPP 

#include "frame.hpp"

#include <string>

namespace tap_reader {

    [[nodiscard]] std::string format_frame(const Frame& frame, size_t count);

}

#endif // FORMAT_FRAME_HPP 
