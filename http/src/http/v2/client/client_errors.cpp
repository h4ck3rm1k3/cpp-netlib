// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <network/config.hpp>
#include <network/http/v2/client/client_errors.hpp>
#include <string>

namespace network {
namespace http {
namespace v2 {
class client_category_impl : public std::error_category {

public:

  client_category_impl() = default;

  virtual ~client_category_impl() noexcept;

  virtual const char *name() const noexcept;

  virtual std::string message(int ev) const;

};

client_category_impl::~client_category_impl() noexcept {

}

const char *client_category_impl::name() const noexcept {
  static const char name[] = "client_error";
  return name;
}

std::string client_category_impl::message(int ev) const {
  switch (client_error(ev)) {

  case client_error::invalid_request:
    return "Invalid HTTP request.";
  case client_error::invalid_response:
    return "Invalid HTTP response.";
  default:
    break;
  }
  return "Unknown client error.";
}

const std::error_category &client_category() {
  static client_category_impl client_category;
  return client_category;
}

std::error_code make_error_code(client_error e) {
  return std::error_code(static_cast<int>(e), client_category());
}

invalid_url::invalid_url()
  : std::invalid_argument("Requires HTTP or HTTPS URL.") {

}

invalid_url::~invalid_url() noexcept {

}

client_exception::client_exception(client_error error)
  : std::system_error(make_error_code(error)) {

}

client_exception::~client_exception() noexcept {

}
} // namespace v2
} // namespace http
} // namespace network
