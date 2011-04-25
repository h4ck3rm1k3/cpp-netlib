#            Copyright (c) Dean Michael Berris 2010.
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)
cmake_minimum_required(VERSION 2.8)
set(CPP-NETLIB_SOURCE_DIR "../../../..")

#set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${CPP-NETLIB_SOURCE_DIR}/libs/network/build)
#find_library(Cppnetlib-uri-parsers cppnetlib-uri-parsers    PATHS ${CPP-NETLIB_SOURCE_DIR}/libs/network/build)

LINK_DIRECTORIES(${CPP-NETLIB_SOURCE_DIR}/libs/network/build)

include_directories(${CPP-NETLIB_SOURCE_DIR})
find_package( Boost 1.41.0 COMPONENTS unit_test_framework system regex date_time thread filesystem )
find_package( OpenSSL )
find_package( Threads )
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)

#add_subdirectory(http)

if (Boost_FOUND)
    set(
      TESTS
      geosp00k
        )
    foreach (test ${TESTS})
        set_source_files_properties(${test}.cpp
            PROPERTIES COMPILE_FLAGS "-Wall")
        add_executable(cpp-netlib-${test} ${test}.cpp)
        add_dependencies(cpp-netlib-${test} cppnetlib-uri-parsers)
        target_link_libraries(cpp-netlib-${test} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} cppnetlib-uri-parsers)
        if (OPENSSL_FOUND)
            target_link_libraries(cpp-netlib-${test} ${OPENSSL_LIBRARIES})
        endif()
#        set_target_properties(cpp-netlib-${test}
#            PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CPP-NETLIB_BINARY_DIR}/tests)
        add_test(cpp-netlib-${test} ${CPP-NETLIB_BINARY_DIR}/tests/cpp-netlib-${test})
    endforeach (test)

endif()

