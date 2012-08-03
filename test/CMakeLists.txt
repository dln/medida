# Build gtest from source
add_subdirectory (gtest-1.6.0)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(test_sources
  test_counter.cc
  test_snapshot.cc
)

add_executable(test-medida ${test_sources})

target_link_libraries(test-medida
  gtest
  gtest_main
  medida
)

add_test(test-medida test-medida --gtest_output=xml)

# Kludge for cmake "bug" to build and run tests from a single target
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS test-medida)
