// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef NETWORK_HTTP_V2_CLIENT_CONNECTION_NORMAL_CONNECTION_INC
#define NETWORK_HTTP_V2_CLIENT_CONNECTION_NORMAL_CONNECTION_INC

/**
 * \file
 * \brief
 */

#include <boost/asio/write.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_service.hpp>
#include <network/config.hpp>
#include <network/http/v2/client/connection/async_connection.hpp>

namespace network {
  namespace http {
    inline namespace v2 {
      namespace client_connection {

      /**
       * \class
       * \brief
       */
      class normal_connection : public async_connection {

        normal_connection(const normal_connection &) = delete;
        normal_connection &operator = (const normal_connection &) = delete;

      public:

        /**
         * \brief
         */
        explicit normal_connection(boost::asio::io_service &io_service)
          : io_service_(io_service) {

        }

        /**
         * \brief Destructor.
         */
        virtual ~normal_connection() noexcept {

        }

        virtual void async_connect(const boost::asio::ip::tcp::endpoint &endpoint,
                                   const std::string &host,
                                   connect_callback callback) {
          using boost::asio::ip::tcp;
          socket_.reset(new tcp::socket{io_service_});
          socket_->async_connect(endpoint, callback);
        }

        virtual void async_write(boost::asio::streambuf &command_streambuf,
                                 write_callback callback) {
          boost::asio::async_write(*socket_, command_streambuf, callback);
        }

        virtual void async_read_until(boost::asio::streambuf &command_streambuf,
                                      const std::string &delim,
                                      read_callback callback) {
          boost::asio::async_read_until(*socket_, command_streambuf, delim, callback);
        }

        virtual void async_read(boost::asio::streambuf &command_streambuf,
                                read_callback callback) {
          boost::asio::async_read(*socket_, command_streambuf,
                                  boost::asio::transfer_at_least(1), callback);
        }

        virtual void cancel() {
          socket_->cancel();
        }

      private:

        boost::asio::io_service &io_service_;
        std::unique_ptr<boost::asio::ip::tcp::socket> socket_;

      };
      } // namespace client_connection
    } // namespace v2
  } // namespace http
} // namespace network

#endif // NETWORK_HTTP_V2_CLIENT_CONNECTION_NORMAL_CONNECTION_INC
