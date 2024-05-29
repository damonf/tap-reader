target_sources(test-tap-reader
    PRIVATE
      format_frame_test.cpp
      hex_to_bin.hpp
)

target_include_directories(test-tap-reader PUBLIC ${CMAKE_CURRENT_LIST_DIR})


