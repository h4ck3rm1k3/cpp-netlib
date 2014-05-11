// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef NETWORK_HTTP_V2_CLIENT_CONNECTION_ASYNC_CONNECTION_INC
#define NETWORK_HTTP_V2_CLIENT_CONNECTION_ASYNC_CONNECTION_INC

/**
 * \file
 * \brief
 */

#include <functional>
#include <string>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/buffer.hpp>
#include <network/config.hpp>

namespace network {
  namespace http {
    inline namespace v2 {
      namespace client_connection {
        /**
         * \class async_connection network/http/v2/client/connection/async_connection.hpp
         * \brief Manages a connection through a socket.
         */
        class async_connection {

          async_connection(const async_connection &) = delete;
          async_connection &operator = (const async_connection &) = delete;

        public:

          /**
           * \typedef connect_callback
           */
          typedef std::function<void (const boost::system::error_code &)> connect_callback;

          /**
           * \typedef write_callback
           */
          typedef std::function<void (const boost::system::error_code &, std::size_t)> write_callback;

          /**
           * \typedef read_callback
           */
          typedef std::function<void (const boost::system::error_code &, std::size_t)> read_callback;

          /**
           * \brief Constructor.
           */
          async_connection() = default;

          /**
           * \brief Destructor.
           */
          virtual ~async_connection() noexcept { }

          /**
           * \brief Asynchronously creates a connection to an endpoint.
           * \param endpoint The endpoint to which to connect.
           * \param callback A callback handler.
           */
          virtual void async_connect(const boost::asio::ip::tcp::endpoint &endpoint,
                                     const std::string &host,
                                     connect_callback callback) = 0;

          /**
           * \brief Asynchronously writes data across the connection.
           * \param command_streambuf
           * \param callback A callback handler.
           */
          virtual void async_write(boost::asio::streambuf &command_streambuf,
                                   write_callback callback) = 0;

          /**
           * \brief Asynchronously reads some data from the connection.
           * \param command_streambuf
           * \param delim A delimiter string which, if found, the socket
           *        will stop reading.
           * \param callback A callback handler.
           */
          virtual void async_read_until(boost::asio::streambuf &command_streambuf,
                                        const std::string &delim,
                                        read_callback callback) = 0;

          /**
           * \brief Asynchronously reads some data from the connection.
           * \param command_streambuf
           * \param callback A callback handler.
           */
          virtual void async_read(boost::asio::streambuf &command_streambuf,
                                  read_callback callback) = 0;

          /**
           * \brief Cancels an operation on a connection.
           */
          virtual void cancel() = 0;

        };
      } // namespace client_connection
    } // namespace v2
  } // namespace http
} // namespace network

#endif // NETWORK_HTTP_V2_CLIENT_CONNECTION_ASYNC_CONNECTION_INC
