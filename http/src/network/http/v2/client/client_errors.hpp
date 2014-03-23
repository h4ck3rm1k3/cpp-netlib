// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef NETWORK_HTTP_V2_CLIENT_CLIENT_ERRORS_INC
#define NETWORK_HTTP_V2_CLIENT_CLIENT_ERRORS_INC

/**
 * \file
 * \brief Contains a set of error classes and exceptions for HTTP
 *        clients.
 */

#include <system_error>
#include <stdexcept>
#include <network/config.hpp>

namespace network {
namespace http {
namespace v2 {
/**
 * \ingroup http_client
 * \enum client_error network/http/v2/client/client_errors.hpp network/http/v2/client.hpp
 * \brief An enumeration of all types of client error.
 */
enum class client_error {
  // request
  invalid_request,

  // response
    invalid_response,
    };

/**
 * \brief Gets the error category for HTTP client errors.
 */
const std::error_category &client_category();

/**
 * \brief Makes an error code object from a client_error enum.
 */
std::error_code make_error_code(client_error e);

/**
 * \ingroup http_client
 * \class invalid_url network/http/v2/client/client_errors.hpp network/http/v2/client.hpp
 * \brief An exception thrown if the URL provides is invalid.
 */
class invalid_url : public std::invalid_argument {

public:

  /**
   * \brief Constructor.
   */
  explicit invalid_url();

  /**
   * \brief Destructor.
   */
  virtual ~invalid_url() noexcept;

};

/**
 * \ingroup http_client
 * \class client_exception network/http/v2/client/client_errors.hpp network/http/v2/client.hpp
 * \brief An exception thrown when there is a client error.
 */
class client_exception : public std::system_error {

public:

  /**
   * \brief Constructor.
   */
  explicit client_exception(client_error error);

  /**
   * \brief Destructor.
   */
  virtual ~client_exception() noexcept;

};

} // namespace v2
} // namespace http
} // namespace network

#endif // NETWORK_HTTP_V2_CLIENT_CLIENT_ERRORS_INC
