#ifndef ARG_PARSER_HPP
#define ARG_PARSER_HPP

#include <string>
#include <vector>

namespace tap_reader {

class ArgParser {
  public:
    ArgParser(int argc, const char** argv);

    [[nodiscard]] bool is_valid() const;
    [[nodiscard]] const std::string& get_device_name() const;

  private:
    std::vector<std::string> args_{};
    constexpr const static std::string empty_string_{};
};

} // namespace tap_reader 

#endif // ARG_PARSER_HPP
