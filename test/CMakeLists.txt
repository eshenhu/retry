cmake_minimum_required (VERSION 3.5)
project(retry_test CXX)
enable_testing()

set(CMAKE_CXX_STANDARD 11)
find_package(Boost 1.45.0 COMPONENTS unit_test_framework REQUIRED)

include_directories( ${Boost_INCLUDE_DIRS} )

# declares a test with our executable
add_definitions(-DBOOST_TEST_DYN_LINK)
add_executable(retry_test retry_test.cpp)
target_link_libraries(retry_test ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

# declares a test with our executable
add_test(DemoTest retry_test)