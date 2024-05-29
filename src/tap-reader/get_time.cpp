#include "get_time.hpp"

#include <chrono>
#include <format>
#include <string>
#include <ctime>

namespace tap_reader {

std::string get_time() {

    const auto now = std::chrono::system_clock::now();
    const std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

    std::tm now_tm{};
    ::localtime_r(&now_time_t, &now_tm); // NOLINT(misc-include-cleaner)

    auto now_ms = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()) % 1000000;

    return std::format("{:02}:{:02}:{:02}.{:06}"
                       , now_tm.tm_hour
                       , now_tm.tm_min
                       , now_tm.tm_sec
                       , now_ms.count()
                       );
}

}
