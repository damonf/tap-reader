target_sources(test-tap-reader
    PRIVATE
      frame_formatter_test.cpp
)

target_include_directories(test-tap-reader PUBLIC ${CMAKE_CURRENT_LIST_DIR})


