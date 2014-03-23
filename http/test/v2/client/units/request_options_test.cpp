// Copyright (C) 2013, 2014 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <gtest/gtest.h>
#include "network/http/v2/client/request.hpp"

namespace http_cm = network::http::v2::client_message;

TEST(request_options_test, default_options_resolve_timeout) {
  http_cm::request_options opts;
  ASSERT_EQ(30000, opts.resolve_timeout());
}

TEST(request_options_test, default_options_read_timeout) {
  http_cm::request_options opts;
  ASSERT_EQ(30000, opts.read_timeout());
}

TEST(request_options_test, default_options_total_timeout) {
  http_cm::request_options opts;
  ASSERT_EQ(30000, opts.total_timeout());
}

TEST(request_options_test, set_resolve_timeout) {
  http_cm::request_options opts;
  opts.resolve_timeout(10000);
  ASSERT_EQ(10000, opts.resolve_timeout());
}

TEST(request_options_test, set_max_redirects) {
  http_cm::request_options opts;
  opts.max_redirects(5);
  ASSERT_EQ(5, opts.max_redirects());
}

TEST(request_options_test, set_progress_handler) {
  std::uint64_t bytes = 0;
  http_cm::request_options opts;
  opts.progress([&bytes] (http_cm::transfer_direction direction, std::uint64_t bytes_) {
      bytes = bytes_;
    });
  opts.progress()(http_cm::transfer_direction::bytes_written, 42);
  ASSERT_EQ(42, bytes);
}
