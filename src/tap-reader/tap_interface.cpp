#include "tap_interface.hpp"

#include <string>
#include <utility>
#include <stdexcept>

#include <cstring>
#include <cerrno>
#include <net/if.h> // ifreq
#include <linux/if_tun.h> // IFF_TUN, IFF_NO_PI
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

namespace tap_reader {

TapInterface::TapInterface(TapInterface&& other) noexcept
    :
    fd_{other.fd_}
{
    other.fd_ = -1;
}

TapInterface& TapInterface::operator=(TapInterface&& other) noexcept {
    fd_ = other.fd_;
    other.fd_ = -1;

    return *this;
}

TapInterface::~TapInterface() {
    if (fd_ != -1) {
        ::close(fd_);
    }
}

std::pair<bool, int> TapInterface::open(const std::string& name) {

    if (fd_ != -1) {
        throw std::domain_error("already opened");
    }

    if (name.length() >= IFNAMSIZ) {
        throw std::domain_error("device name is too long");
    }

    fd_ = ::open("/dev/net/tun", O_RDWR); // NOLINT
    if (fd_ == -1) {
        return std::make_pair(false, errno); 
    }

    struct ifreq ifr{};
    ifr.ifr_flags = IFF_TAP | IFF_NO_PI;
    ::strncpy(&ifr.ifr_name[0], name.c_str(), IFNAMSIZ - 1);
    int res = ::ioctl(fd_, TUNSETIFF, &ifr); // NOLINT
    if (res == -1) {
        return std::make_pair(false, errno); 
    }

    return std::make_pair(true, 0);
}

bool TapInterface::is_open() const {
    return fd_ != -1;
}

} // namespace tap_reader
