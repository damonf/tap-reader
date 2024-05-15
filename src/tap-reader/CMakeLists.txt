target_sources(tap-reader
  PRIVATE
  arg_parser.cpp
  arg_parser.hpp
  bin_to_hex.hpp
  tap_interface.hpp
  tap_interface.cpp
  )

target_include_directories(tap-reader PUBLIC ${CMAKE_CURRENT_LIST_DIR})
