// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef NETWORK_HTTP_V2_METHOD_INC
#define NETWORK_HTTP_V2_METHOD_INC

/**
 * \file
 * \brief HTTP request methods.
 */

#include <string>
#include <ostream>

namespace network {
namespace http {
namespace v2 {
enum class method { get, post, put, delete_, head, options, trace, connect, merge, patch, };

inline
std::ostream &operator << (std::ostream &os, method m) {
  switch (m) {
  case method::get:
    return os << "GET";
  case method::post:
    return os << "POST";
  case method::put:
    return os << "PUT";
  case method::delete_:
    return os << "DELETE";
  case method::head:
    return os << "HEAD";
  case method::options:
    return os << "OPTIONS";
  case method::trace:
    return os << "TRACE";
  case method::connect:
    return os << "CONNECT";
  case method::merge:
    return os << "MERGE";
  case method::patch:
    return os << "PATCH";
  }
  return os;
}
} // namespace v2
} // namespace http
} // namespace network


#endif // NETWORK_HTTP_V2_METHOD_INC
