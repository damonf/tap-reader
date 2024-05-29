#include "arg_parser.hpp"

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <ranges>
#include <span>
#include <string>

namespace tap_reader {

namespace rg = std::ranges;
namespace vw = std::views;

ArgParser::ArgParser(int argc, const char** argv) {
    const std::span<const char*> args{argv, static_cast<size_t>(argc)};
    rg::copy_if(args, std::back_inserter(args_),
                         [](const char* arg) { return arg != nullptr; });
}

bool ArgParser::is_valid() const {

    if (args_.size() < 2 || args_.size() > 3) {
        return false;
    }

    auto options_view =
        args_ | vw::filter(
                    [](const std::string& arg) { return arg[0] == '-'; });

    auto options_count = rg::distance(options_view);

    if (options_count > 1 && args_.size() != 3) {
        return false;
    }

    if (options_count > 1 || (options_count == 1 && *begin(options_view) != format_option_)) {
        return false;
    }

    return true;
}

const std::string& ArgParser::get_device_name() const {
    if (args_.size() > 1) {
        return args_[1];
    }
    return empty_string_;
}

bool ArgParser::formatted() const {
    auto it = rg::find(args_, format_option_);
    return (it != args_.end());
}

} // namespace tap_reader
