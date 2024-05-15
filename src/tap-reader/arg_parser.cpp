#include "arg_parser.hpp"

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <span>
#include <string>

namespace tap_reader {

namespace rg = std::ranges;

ArgParser::ArgParser(int argc, const char** argv) {
    const std::span<const char*> args{argv, static_cast<size_t>(argc)};
    rg::copy_if(args, std::back_inserter(args_),
                         [](const char* arg) { return arg != nullptr; });
}

bool ArgParser::is_valid() const {
    return args_.size() == 2;
}

const std::string& ArgParser::get_device_name() const {
    if (args_.size() > 1) {
        return args_[1];
    }
    return empty_string_;
}

} // namespace tap_reader
