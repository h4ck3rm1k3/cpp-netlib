# Copyright (c) Glyn Matthews 2012.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

include_directories(${CPP-NETLIB_SOURCE_DIR}/logging/src ${CPP-NETLIB_SOURCE_DIR})

set(CPP-NETLIB_LOGGING_SRCS
    logging.cpp)

add_library(network-logging ${CPP-NETLIB_LOGGING_SRCS})

# prepend current directory to make paths absolute
prependToElements( "${CMAKE_CURRENT_SOURCE_DIR}/"
    CPP-NETLIB_LOGGING_SRCS )

# propagate sources to parent directory for one-lib-build
set(CPP-NETLIB_LOGGING_SRCS ${CPP-NETLIB_LOGGING_SRCS} PARENT_SCOPE)
