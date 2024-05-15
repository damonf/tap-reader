#ifndef TAP_INTERFACE_HPP
#define TAP_INTERFACE_HPP

#include <string>
#include <utility>

#include <unistd.h>

namespace tap_reader {

class TapInterface {
    public:
        TapInterface() = default;
        TapInterface(TapInterface&& other) noexcept;
        TapInterface(const TapInterface&) = delete;

        ~TapInterface();

        TapInterface& operator=(TapInterface&& other) noexcept;
        TapInterface& operator=(const TapInterface&) = delete;

        [[nodiscard]] std::pair<bool, int> open(const std::string& name);
        [[nodiscard]] bool is_open() const;
        [[nodiscard]] std::pair<bool, int> close();

        template<class T>
        requires std::is_standard_layout_v<T>
        [[nodiscard]] std::pair<ssize_t, int> read(T& buffer) const;

    private:
        int fd_ = -1;
};

template<class T>
requires std::is_standard_layout_v<T>
std::pair<ssize_t, int> TapInterface::read(T& buffer) const {

    auto bytes_read = ::read(fd_, &buffer, sizeof(T));

    if (bytes_read == -1) {
        return std::make_pair(-1, errno); 
    }

    return std::make_pair(bytes_read, 0);
}

} // namespace tap_reader

#endif // TAP_INTERFACE_HPP
