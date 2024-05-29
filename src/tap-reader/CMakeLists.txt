target_sources(tap-reader
  PRIVATE
  arg_parser.cpp
  arg_parser.hpp
  bin_to_hex.hpp
  frame.hpp
  format_frame.cpp
  format_frame.hpp
  tap_interface.cpp
  tap_interface.hpp
  get_time.hpp
  get_time.cpp
  )

target_include_directories(tap-reader PUBLIC ${CMAKE_CURRENT_LIST_DIR})
