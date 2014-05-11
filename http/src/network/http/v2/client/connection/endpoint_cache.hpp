// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef NETWORK_HTTP_V2_CLIENT_CONNECTION_ENDPOINT_CACHE_INC
#define NETWORK_HTTP_V2_CLIENT_CONNECTION_ENDPOINT_CACHE_INC

/**
 * \file
 * \brief
 */

#include <string>
#include <unordered_map>
#include <boost/asio/ip/tcp.hpp>
#include <boost/algorithm/string/case_conv.hpp>

namespace network {
  namespace http {
    inline namespace v2 {
      namespace client_connection {

      /**
       * \class endpoint_cache network/http/v2/client/connection/endpoint_cache.hpp
       * \brief
       */
      class endpoint_cache {

        /**
         * \brief
         */
        typedef boost::asio::ip::tcp::resolver resolver;

        typedef resolver::iterator resolver_iterator;

        typedef std::unordered_map<std::string,
                                   resolver_iterator> cache_type;

      public:

        /**
         * \brief
         */
        typedef cache_type::iterator iterator;

        /**
         * \brief
         */
        cache_type::iterator begin() {
          return endpoints_.begin();
        }

        /**
         * \brief
         */
        cache_type::iterator end() {
          return endpoints_.end();
        }

        /**
         * \brief
         */
        void insert(const std::string &host,
                    resolver_iterator endpoint_iterator) {
          endpoints_.insert(std::make_pair(host, endpoint_iterator));
        }

        /**
         * \brief
         */
        iterator find(const std::string &host) {
          return endpoints_.find(boost::to_lower_copy(host));
        }

        /**
         * \brief
         */
        void clear() {
          endpoint_cache().swap(*this);
        }

        /**
         * \brief
         */
        void swap(endpoint_cache &other) noexcept {
          endpoints_.swap(other.endpoints_);
        }

      private:

        cache_type endpoints_;

      };
      } // namespace client_connection
    } // namespace v2
  } // namespace http
} // namespace network

#endif // NETWORK_HTTP_V2_CLIENT_CONNECTION_ENDPOINT_CACHE_INC
