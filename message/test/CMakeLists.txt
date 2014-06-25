# Copyright (c) Glyn Matthews 2012.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${CPP-NETLIB_SOURCE_DIR}/uri/src)
include_directories(${CPP-NETLIB_SOURCE_DIR}/message/src)

if (CPP-NETLIB_BUILD_TESTS)
  set(TESTS message_test message_transform_test)
  if(CPP-NETLIB_BUILD_SINGLE_LIB)
    set(link_cppnetlib_lib cppnetlib)
  else()
    set(link_cppnetlib_lib network-message
      network-message-directives
      network-message-wrappers)
  endif()
  foreach (test ${TESTS})
    add_executable(cpp-netlib-${test} ${test}.cpp)
    target_link_libraries(cpp-netlib-${test}
      ${Boost_SYSTEM_LIBRARY}
      ${CMAKE_THREAD_LIBS_INIT}
      ${GTEST_BOTH_LIBRARIES}
      ${link_cppnetlib_lib})
    if (OPENSSL_FOUND)
      target_link_libraries(cpp-netlib-${test} ${OPENSSL_LIBRARIES})
    endif()
    set_target_properties(cpp-netlib-${test}
      PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CPP-NETLIB_BINARY_DIR}/tests)
    add_test(cpp-netlib-${test}
      ${CPP-NETLIB_BINARY_DIR}/tests/cpp-netlib-${test})
  endforeach (test)
endif (CPP-NETLIB_BUILD_TESTS)
