#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <cstddef>

namespace tap_reader {

const constinit static std::size_t BUF_SIZE = 4UL * 1024;
const constinit static std::size_t MAC_SIZE = 6;
const constinit static std::size_t LENTYPE_SIZE = 2;
const constinit static std::size_t LENTYPE_LEN_MAX = 1500;

}

#endif // CONSTANTS_HPP

