// #define _POSIX_C_SOURCE 200112L

#include "arg_parser.hpp"
#include "tap_interface.hpp"
#include "frame.hpp"
#include "bin_to_hex.hpp"

#include <exception>
#include <iostream>
#include <array>
#include <format>
#include <string>

#include <cstdlib>
#include <cstring>

namespace {

    namespace tr = tap_reader;

}

constexpr size_t err_buf_size = 256;

std::string get_error(int errnum) {
    std::array<char, err_buf_size> buffer{};
    auto *msg = ::strerror_r(errnum, buffer.data(), sizeof(buffer));
    return msg;
}

int main(int argc, const char *argv[]) { // NOLINT

    try {
        const tr::ArgParser arg_parser(argc, argv);

        if (!arg_parser.is_valid()) {
            std::cerr << "Usage: device_name\n";
            return EXIT_FAILURE;
        }

        const auto& device_name = arg_parser.get_device_name();

        tr::TapInterface tap_interface{};
        auto [ok, err] = tap_interface.open(device_name);

        if (!ok) {
            std::cerr
                << std::format(
                    "failed to open device '{}', error: '{}'"
                    , device_name
                    , get_error(err)
                )
                << std::endl;

            return EXIT_FAILURE;
        }

        tr::Frame frame{};

        while (true) {
            // read the next frame
            auto [bytes_read, err] = tap_interface.read(frame);

            if (err > 0) {
                std::cerr 
                    << std::format(
                        "error reading device '{}', error: '{}'"
                        ,device_name
                        ,get_error(err)
                    )
                    << std::endl;
                return EXIT_FAILURE;
            }

            if (bytes_read == sizeof(tr::Frame)) {
                std::cerr << "max buffer size reached" << std::endl;
            }

            // dump the frame
            std::cout << tr::bin_to_hex(frame, bytes_read) << std::endl;
        }

        return EXIT_SUCCESS;
    }
    catch (const std::exception& e) {
        std::cerr << e.what();
        return EXIT_FAILURE;
    }
}

