#ifndef FRAME_FORMATTER_HPP
#define FRAME_FORMATTER_HPP

#include "frame.hpp"

#include <string>

namespace tap_reader {

class FrameFormatter {
    public:
        [[nodiscard]] std::string format_frame(
            const Frame& frame
          , size_t count
        ) const;
};

}

#endif // FRAME_FORMATTER_HPP
