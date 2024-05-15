add_executable(tap
  main.cpp
  )

target_link_libraries(tap PRIVATE tap-reader)
