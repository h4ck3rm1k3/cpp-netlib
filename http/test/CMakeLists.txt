# Copyright 2013 Google, Inc.
# Copyright 2010, 2013 Dean Michael Berris <dberris@google.com>
# Copyright (c) Glyn Matthews 2013.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

include_directories(
  ${CPP-NETLIB_SOURCE_DIR}/config/src
  ${CPP-NETLIB_SOURCE_DIR}/message/src
  ${CPP-NETLIB_SOURCE_DIR}/uri/src
  ${CPP-NETLIB_SOURCE_DIR}/logging/src
  ${CPP-NETLIB_SOURCE_DIR}/http/src
  ${GTEST_INCLUDE_DIRS}
  #${GMOCK_INCLUDE_DIRS}
  ${IGLOO_INCLUDE_DIR}
  ${CPP-NETLIB_SOURCE_DIR})

add_subdirectory(v2)

if (OPENSSL_FOUND)
  include_directories( ${OPENSSL_INCLUDE_DIR} )
  add_definitions(-DNETWORK_ENABLE_HTTPS)
endif()


set( CPPNETLIB_LIBRARIES cppnetlib )
#set( CPPNETLIB_CLIENT_LIBRARIES ${CPPNETLIB_LIBRARIES} )
set( CPPNETLIB_SERVER_LIBRARIES ${CPPNETLIB_LIBRARIES} )
if(NOT CPP-NETLIB_BUILD_SINGLE_LIB)
    set( CPPNETLIB_LIBRARIES
        network-message
        network-message-wrappers
        network-http-message
        network-http-message-wrappers
        network-uri
        network-constants )

#    set( CPPNETLIB_CLIENT_LIBRARIES
#        ${CPPNETLIB_LIBRARIES}
#        network-http-client
#        network-http-client-connections )

    set( CPPNETLIB_SERVER_LIBRARIES
         network-http-server )
endif()


if (CPP-NETLIB_BUILD_TESTS)
  # These are the internal (simple) tests.
  set (MESSAGE_TESTS request_base_test request_test response_test
    response_incremental_parser_test)
  foreach ( test ${MESSAGE_TESTS} )
    add_executable(cpp-netlib-http-${test} ${test}.cpp)
    target_link_libraries(cpp-netlib-http-${test}
      ${Boost_LIBRARIES}
      ${GTEST_BOTH_LIBRARIES}
      ${ICU_LIBRARIES} ${ICU_I18N_LIBRARIES}
      ${CMAKE_THREAD_LIBS_INIT}
      ${CPPNETLIB_LIBRARIES} )
    set_target_properties(cpp-netlib-http-${test}
      PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CPP-NETLIB_BINARY_DIR}/tests)
    add_test(cpp-netlib-http-${test}
      ${CPP-NETLIB_BINARY_DIR}/tests/cpp-netlib-http-${test})
  endforeach(test)

#  # HTTP Client tests.
#  add_executable(cpp-netlib-http-client_test client_test.cpp)
#  target_link_libraries(cpp-netlib-http-client_test
#    ${Boost_LIBRARIES}
#    ${GTEST_BOTH_LIBRARIES}
#    ${ICU_LIBRARIES} ${ICU_I18N_LIBRARIES}
#    ${CMAKE_THREAD_LIBS_INIT}
#    ${CPP-NETLIB_LOGGING_LIB}
#    ${CPPNETLIB_CLIENT_LIBRARIES} )
#  if (OPENSSL_FOUND)
#    target_link_libraries(cpp-netlib-http-client_test ${OPENSSL_LIBRARIES})
#  endif()
#  set_target_properties(cpp-netlib-http-client_test
#    PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CPP-NETLIB_BINARY_DIR}/tests)
#  add_test(cpp-netlib-http-client_test
#    ${CPP-NETLIB_BINARY_DIR}/tests/cpp-netlib-http-client_test)
#
  # HTTP Server tests
  set (SERVER_TESTS server_simple_sessions_test server_dynamic_dispatcher_test
    server_default_connection_manager_test server_test)
  foreach (test ${SERVER_TESTS})
    add_executable(cpp-netlib-http-${test} ${test}.cpp)
    target_link_libraries(cpp-netlib-http-${test}
      ${Boost_LIBRARIES}
      ${GTEST_BOTH_LIBRARIES}
      ${CMAKE_THREAD_LIBS_INIT}
      ${CPPNETLIB_SERVER_LIBRARIES} )
    set_target_properties(cpp-netlib-http-${test} PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY ${CPP-NETLIB_BINARY_DIR}/tests)
    add_test(cpp-netlib-http-${test}
      ${CPP-NETLIB_BINARY_DIR}/tests/cpp-netlib-http-${test})
  endforeach(test)
endif()
