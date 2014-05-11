// Copyright (C) 2013 by Glyn Matthews
// Copyright 2011 Dean Michael Berris <dberris@google.com>.
// Copyright 2011 Google, Inc.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef NETWORK_HTTP_V2_CLIENT_CONNECTION_TCP_RESOLVER_INC
#define NETWORK_HTTP_V2_CLIENT_CONNECTION_TCP_RESOLVER_INC

/**
 * \file
 * \brief
 */

#include <stdexcept>
#include <cstdint>
#include <string>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/exception/all.hpp>
#include <network/config.hpp>
#include <network/http/v2/client/connection/async_resolver.hpp>
#include <network/http/v2/client/connection/endpoint_cache.hpp>

namespace network {
  namespace http {
    inline namespace v2 {
      namespace client_connection {
        /**
         * \class tcp_resolver network/http/v2/client/connection/tcp_resolver.hpp
         * \brief Resolves and maintains a cache of hosts.
         */
        class tcp_resolver : public async_resolver {

          tcp_resolver(const tcp_resolver &) = delete;
          tcp_resolver &operator = (const tcp_resolver &) = delete;

        public:

          using async_resolver::resolver;
          using async_resolver::resolver_iterator;
          using async_resolver::resolve_callback;

          /**
           * \brief Constructor.
           */
          tcp_resolver(boost::asio::io_service &service, bool cache_resolved = false)
            : resolver_(service)
            , cache_resolved_(cache_resolved) {

          }

          /**
           * \brief Destructor.
           */
          virtual ~tcp_resolver() noexcept {

          }

          virtual void async_resolve(const std::string &host, std::uint16_t port,
                                     resolve_callback handler) {
            if (cache_resolved_) {
              auto it = endpoint_cache_.find(host);
              if (it != endpoint_cache_.end()) {
                boost::system::error_code ec;
                handler(ec, it->second);
                return;
              }
            }

            resolver::query query(host, std::to_string(port));
            resolver_.async_resolve(query,
                                    [host, handler, this](const boost::system::error_code &ec,
                                                          resolver_iterator endpoint_iterator) {
                                      if (ec) {
                                        handler(ec, resolver_iterator());
                                      }
                                      else {
                                        if (cache_resolved_) {
                                          endpoint_cache_.insert(host, endpoint_iterator);
                                        }
                                        handler(ec, endpoint_iterator);
                                      }
                                    });
          }

          virtual void clear_resolved_cache() {
            endpoint_cache_.clear();
          }

        private:

          resolver resolver_;
          bool cache_resolved_;
          endpoint_cache endpoint_cache_;

        };
      } // namespace client_connection
    } // namespace v2
  } // namespace http
} // namespace network

#endif // NETWORK_HTTP_V2_CLIENT_CONNECTION_TCP_RESOLVER_INC
