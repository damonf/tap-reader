#include "format_frame.hpp"
#include "constants.hpp"
#include "frame.hpp"
#include "bin_to_hex.hpp"

#include <algorithm>
#include <array>
#include <format>
#include <string>

#include <cstddef>
#include <cstdint>
#include <utility>

namespace tap_reader {

    namespace {

         constexpr std::array<std::pair<uint16_t, const char*>, 4> ether_types_ = {{
            {0x0800, "IPv4"},
            {0x0806, "ARP"},
            {0x86DD, "IPv6"},
            {0x8100, "VLAN"}
        }};

        std::string format_mac(const std::array<unsigned char, 6>& mac) {
        
            std::string result{};
        
            for (size_t i = 0; i < 6; ++i) {
                result += std::format("{:02x}", mac.at(i));
                if (i != 5) {
                    result += ":";
                }
            }
        
            return result;
        }
        
        std::string format_lentype(const std::array<unsigned char, 2>& lentype) {
        
            uint16_t value = (
                static_cast<uint16_t>(lentype[0]) << 8)
              | static_cast<uint16_t>(lentype[1]
                );
        
            std::string result{};
        
            if (value <= LENTYPE_LEN_MAX) {
                result = std::format("{}", value);
            }
            else {
                const auto* const it = std::ranges::find_if(ether_types_,
                                       [value](const auto& pair) {
                                               return pair.first == value;
                                        });
        
                if (it != ether_types_.end()) {
                    result = std::string(it->second);
                }
                else {
                    result = "0x" + std::format("{:x}", value);
                }
            }
        
            return result;
        }
        
        std::string format_buffer(
            const std::array<unsigned char, BUF_SIZE>& buffer
            , size_t count
        ) {
            // TODO: some bounds checking
            const size_t buff_len = count - MAC_SIZE - MAC_SIZE - LENTYPE_SIZE;
            return bin_to_hex(buffer, buff_len);
        }
    }

[[nodiscard]] std::string format_frame(const Frame& frame, size_t count) {

    auto dest = format_mac(frame.dest_mac_);
    auto src = format_mac(frame.src_mac_);
    auto lentype = format_lentype(frame.lentype_);
    auto buffer = format_buffer(frame.buffer_, count);

    return std::format("{} {} {} {}", dest, src, lentype, buffer);
}

} // namespace tap_reader
