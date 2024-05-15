find_package(Catch2 3 REQUIRED
  PATHS ${PROJECT_SOURCE_DIR}/third_party/bin/Catch2 NO_DEFAULT_PATH
  )

include_directories(
  SYSTEM
  "${PROJECT_SOURCE_DIR}/third_party/bin/Catch2/include"
)

add_executable(test-tap-reader)

add_subdirectory(tap-reader)

target_link_libraries(test-tap-reader
  PRIVATE
  tap-reader
  Catch2::Catch2WithMain
  # trompeloeil::trompeloeil
  )

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

include(CTest)
include(Catch)

# Run the function defined by the Catch2 CMake module
catch_discover_tests(test-tap-reader)
