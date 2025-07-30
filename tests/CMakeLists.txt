add_executable(test_fft test_fft.cpp)

target_link_libraries(test_fft PRIVATE
    GTest::gtest
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_fft)
