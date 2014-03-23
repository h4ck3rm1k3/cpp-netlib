// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef NETWORK_HTTP_V2_STATUS_INC
#define NETWORK_HTTP_V2_STATUS_INC

/**
 * \file
 * \brief Constants for the HTTP error status.
 *
 * http://tools.ietf.org/html/rfc6585
 * http://httpstatus.es/
 */

#include <string>
#include <unordered_map>
#include <functional>

namespace network {
namespace http {
namespace v2 {
namespace status {
/**
 * \ingroup http
 * \enum code
 * \brief Provides the full set of HTTP status codes.
 */
enum class code {
  // informational
  continue_ = 100,
    switch_protocols = 101,

  // successful
    ok = 200,
    created = 201,
    accepted = 202,
    non_auth_info = 203,
    no_content = 204,
    reset_content = 205,
    partial_content = 206,

  // redirection
    multiple_choices = 300,
    moved_permanently = 301,
    found = 302,
    see_other = 303,
    not_modified = 304,
    use_proxy = 305,
    temporary_redirect = 307,

  // client error
    bad_request = 400,
    unauthorized = 401,
    payment_required = 402,
    forbidden = 403,
    not_found = 404,
    method_not_allowed = 405,
    not_acceptable = 406,
    proxy_auth_required = 407,
    request_timeout = 408,
    conflict = 409,
    gone = 410,
    length_required = 411,
    precondition_failed = 412,
    request_entity_too_large = 413,
    request_uri_too_long = 414,
    unsupported_media_type = 415,
    request_range_not_satisfiable = 416,
    expectation_failed = 417,
    precondition_required = 428,
    too_many_requests = 429,
    request_header_fields_too_large = 431,

  // server error
    internal_error = 500,
    not_implemented = 501,
    bad_gateway = 502,
    service_unavailable = 503,
    gateway_timeout = 504,
    http_version_not_supported = 505,
    network_authentication_required = 511,
    };
} // namespace status
} // namespace v2
} // namespace http
} // namespace network

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
namespace std {
template <>
struct hash<network::http::v2::status::code> {
  std::size_t operator()(network::http::v2::status::code status_code) const {
    hash<std::uint16_t> hasher;
    return hasher(static_cast<std::uint16_t>(status_code));
  }
};
} // namespace std
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

namespace network {
namespace http {
namespace v2 {
namespace status {
/**
 * \ingroup http_client
 * \fn
 * \brief Returns a message based on the status code provided.
 * \param code The status code.
 * \returns The corresponding status message.
 */
inline
std::string message(code status_code) {
  static std::unordered_map<code, std::string> status_messages{
    {code::continue_, "Continue"},
    {code::switch_protocols, "Switching Protocols"},
    {code::ok, "OK"},
    {code::created, "Created"},
    {code::accepted, "Accepted"},
    {code::non_auth_info, "Non-Authoritative Information"},
    {code::no_content, "No Content"},
    {code::reset_content, "Reset Content"},
    {code::partial_content, "Partial Content"},
    {code::multiple_choices, "Multiple Choices"},
    {code::moved_permanently, "Moved Permanently"},
    {code::found, "Found"},
    {code::see_other, "See Other"},
    {code::not_modified, "Not Modified"},
    {code::use_proxy, "Use Proxy"},
    {code::temporary_redirect, "Temporary Redirect"},
    {code::bad_request, "Bad Request"},
    {code::unauthorized, "Unauthorized"},
    {code::payment_required, "Payment Required"},
    {code::forbidden, "Forbidden"},
    {code::not_found, "Not Found"},
    {code::method_not_allowed, "Method Not Allowed"},
    {code::not_acceptable, "Not Acceptable"},
    {code::proxy_auth_required, "Proxy Authentication Required"},
    {code::request_timeout, "Request Timeout"},
    {code::conflict, "Conflict"},
    {code::gone, "Gone"},
    {code::length_required, "Length Required"},
    {code::precondition_failed, "Precondition Failed"},
    {code::request_entity_too_large, "Request Entity Too Large"},
    {code::request_uri_too_long, "Request Uri Too Long"},
    {code::unsupported_media_type, "Unsupported Media Type"},
    {code::request_range_not_satisfiable, "Request Range Not Satisfiable"},
    {code::expectation_failed, "Expectation Failed"},
    {code::precondition_required, "Precondition Required"},
    {code::too_many_requests, "Too Many Requests"},
    {code::request_header_fields_too_large, "Request Header Fields Too Large"},
    {code::internal_error, "Internal Error"},
    {code::not_implemented, "Not Implemented"},
    {code::bad_gateway, "Bad Gateway"},
    {code::service_unavailable, "Service Unavailable"},
    {code::gateway_timeout, "Gateway Timeout"},
    {code::http_version_not_supported, "HTTP Version Not Supported"},
    {code::network_authentication_required, "Network Authentication Required"},
      };

  auto it = status_messages.find(status_code);
  if (it != status_messages.end()) {
    return it->second;
  }
  return "Invalid Status Code";
}
} // namespace status
} // namespace v2
} // namespace http
} // namespace network


#endif // NETWORK_HTTP_V2_CONSTANTS_INC
