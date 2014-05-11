// Copyright (C) 2013 by Glyn Matthews
// Copyright 2011 Dean Michael Berris <dberris@google.com>.
// Copyright 2011 Google, Inc.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef NETWORK_HTTP_V2_CLIENT_CONNECTION_ASYNC_RESOLVER_INC
#define NETWORK_HTTP_V2_CLIENT_CONNECTION_ASYNC_RESOLVER_INC

/**
 * \file
 * \brief
 */

#include <functional>
#include <boost/asio/ip/tcp.hpp>

namespace network {
  namespace http {
    inline namespace v2 {
      namespace client_connection {
        /**
         * \class async_resolver network/http/v2/client/connection/async_resolver.hpp
         * \brief Resolves and maintains a cache of hosts.
         */
        class async_resolver {

          async_resolver(const async_resolver &) = delete;
          async_resolver &operator = (const async_resolver &) = delete;

        public:

          /**
           * \brief resolver
           */
          typedef boost::asio::ip::tcp::resolver resolver;

          /**
           * \brief resolver_iterator
           */
          typedef resolver::iterator resolver_iterator;

          /**
           * \typedef resolve_callback
           */
          typedef std::function<void (const boost::system::error_code &,
                                      resolver_iterator)> resolve_callback;

          /**
           * \brief Constructor.
           */
          async_resolver() {

          }

          /**
           * \brief Destructor.
           */
          virtual ~async_resolver() noexcept {

          }

          /**
           * \brief Resolves a host asynchronously.
           * \param host The hostname to resolve.
           * \param port The port number.
           * \param callback A callback handler.
           */
          virtual void async_resolve(const std::string &host, std::uint16_t port,
                                     resolve_callback handler) = 0;

          /**
           * \brief Clears the cache of already resolved endpoints.
           */
          virtual void clear_resolved_cache() = 0;

        };
      } // namespace client_connection
    } // namespace v2
  } // namespace http
} // namespace network

#endif // NETWORK_HTTP_V2_CLIENT_CONNECTION_ASYNC_RESOLVER_INC
