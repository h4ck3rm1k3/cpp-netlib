# Copyright (c) Glyn Matthews 2012.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

include_directories(${CPP-NETLIB_SOURCE_DIR}/concurrency/src
  ${GTEST_INCLUDE_DIRS}
  ${CPP-NETLIB_SOURCE_DIR}
)
if (CPP-NETLIB_BUILD_TESTS)
  add_executable(cpp-netlib-thread_pool_test thread_pool_test.cpp)
  target_link_libraries(cpp-netlib-thread_pool_test
    network-concurrency
    ${Boost_LIBRARIES}
    ${GTEST_BOTH_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT})
  set_target_properties(cpp-netlib-thread_pool_test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CPP-NETLIB_BINARY_DIR}/tests)
  add_test(cpp-netlib-thread_pool_test
    ${CPP-NETLIB_BINARY_DIR}/tests/cpp-netlib-thread_pool_test)
endif()
