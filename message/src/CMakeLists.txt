# Copyright (c) Glyn Matthews 2012.
# Copyright 2013, Dean Michael Berris 2013 <dberris@google.com>
# Copyright 2013, Google, Inc.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

include_directories(${CPP-NETLIB_SOURCE_DIR}/uri/src ${CPP-NETLIB_SOURCE_DIR}/message/src)

set(CPP-NETLIB_MESSAGE_SRCS
    message.cpp)

add_library(network-message ${CPP-NETLIB_MESSAGE_SRCS})
target_link_libraries(network-message network-uri)

set(CPP-NETLIB_MESSAGE_DIRECTIVES_SRCS
    directives.cpp)

add_library(network-message-directives ${CPP-NETLIB_MESSAGE_DIRECTIVES_SRCS})

set(CPP-NETLIB_MESSAGE_WRAPPERS_SRCS
    wrappers.cpp)

add_library(network-message-wrappers ${CPP-NETLIB_MESSAGE_WRAPPERS_SRCS})

# prepend current directory to make paths absolute
prependToElements( "${CMAKE_CURRENT_SOURCE_DIR}/"
    CPP-NETLIB_MESSAGE_SRCS
    CPP-NETLIB_MESSAGE_DIRECTIVES_SRCS
    CPP-NETLIB_MESSAGE_WRAPPERS_SRCS )

# propagate sources to parent directory for one-lib-build
set(CPP-NETLIB_MESSAGE_SRCS ${CPP-NETLIB_MESSAGE_SRCS} PARENT_SCOPE)
set(CPP-NETLIB_MESSAGE_DIRECTIVES_SRCS ${CPP-NETLIB_MESSAGE_DIRECTIVES_SRCS} PARENT_SCOPE)
set(CPP-NETLIB_MESSAGE_WRAPPERS_SRCS ${CPP-NETLIB_MESSAGE_WRAPPERS_SRCS} PARENT_SCOPE)
