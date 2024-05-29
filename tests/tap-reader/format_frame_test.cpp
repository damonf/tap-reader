#include "format_frame.hpp"
#include "constants.hpp"
#include "frame.hpp"
#include "hex_to_bin.hpp"
#include "bin_to_hex.hpp"

#include <catch2/catch_test_macros.hpp>

#include <stdexcept>

#include <cstring>

namespace tr = tap_reader;

namespace tap_reader_tests {

TEST_CASE("format frame tests", "[format_frame]") {

    SECTION("test hex conversion") {
        auto bin = hex_to_bin<tr::MAC_SIZE>("02a3f4d5678b");
        auto res = tr::bin_to_hex(bin, tr::MAC_SIZE);

        REQUIRE(res == "02a3f4d5678b");
    }

    SECTION("test hex conversion invalid") {
        REQUIRE_THROWS_AS(hex_to_bin<2>("2x"), std::invalid_argument);
    }

    SECTION("test format frame") {

        const auto *buffer = "4500003c3f7e40004006f5d0c0a80001c0a80002";

        const tr::Frame frame{
            .dest_mac_ = {hex_to_bin<tr::MAC_SIZE>("02a3f4d5678b")},
            .src_mac_ = {hex_to_bin<tr::MAC_SIZE>("9a3b4c6d8e1f")},
            .lentype_ = {hex_to_bin<tr::LENTYPE_SIZE>("0014")},
            .buffer_ = {hex_to_bin<tr::BUF_SIZE>(buffer)},
        };

        auto size = tr::MAC_SIZE + tr::MAC_SIZE + tr::LENTYPE_SIZE + (::strlen(buffer) / 2);

        auto res = tr::format_frame(frame, size);

        const auto *expected = "02:a3:f4:d5:67:8b 9a:3b:4c:6d:8e:1f 20 4500003c3f7e40004006f5d0c0a80001c0a80002";

        REQUIRE(res == expected);
    }
}

}

