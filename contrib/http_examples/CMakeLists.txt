# Copyright (c) Dean Michael Berris 2010.
# Copyright (c) Glyn Matthews 2013.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

include_directories(
  ${CPP-NETLIB_SOURCE_DIR}/config/src
  ${CPP-NETLIB_SOURCE_DIR}/uri/src
  ${CPP-NETLIB_SOURCE_DIR}/logging/src
  ${CPP-NETLIB_SOURCE_DIR}/http/src
  ${CPP-NETLIB_SOURCE_DIR})
if (OPENSSL_FOUND)
  include_directories(${OPENSSL_INCLUDE_DIR})
endif (OPENSSL_FOUND)

set( CPP-NETLIB_LOGGING_LIB "" )
if( NOT CPP-NETLIB_DISABLE_LOGGING AND NOT CPP-NETLIB_BUILD_SINGLE_LIB)
  set( CPP-NETLIB_LOGGING_LIB network-logging )
endif()

set(EXAMPLES
  simple_wget
  read_headers
  )

foreach(example ${EXAMPLES})
  add_executable(${example} ${example}.cpp)
  target_link_libraries(${example}
    network-uri
    network-http-v2-client
    ${Boost_LIBRARIES}
    ${ICU_LIBRARIES} ${ICU_I18N_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    )
  set_target_properties(${example} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CPP-NETLIB_BINARY_DIR}/example)
endforeach(example)
