# Build gtest from source
add_subdirectory (gtest-1.6.0)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(test_sources
  test_counter.cc
  test_ewma.cc
  test_metric_name.cc
  test_metrics_registry.cc
  test_snapshot.cc
  test_uniform_sample.cc
)

add_executable(test-medida ${test_sources})

target_link_libraries(test-medida
  gtest
  gtest_main
  medida
)

add_test(test-medida test-medida --gtest_output=xml)
