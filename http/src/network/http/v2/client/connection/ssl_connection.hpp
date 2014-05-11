// Copyright (C) 2013 by Glyn Matthews
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef NETWORK_HTTP_V2_CLIENT_CONNECTION_SSL_CONNECTION_INC
#define NETWORK_HTTP_V2_CLIENT_CONNECTION_SSL_CONNECTION_INC

/**
 * \file
 * \brief
 */

#include <memory>
#include <vector>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio/placeholders.hpp>
#include <network/config.hpp>
#include <network/http/v2/client/connection/async_connection.hpp>
#include <network/http/v2/client/client.hpp>

namespace network {
  namespace http {
    inline namespace v2 {
      namespace client_connection {
      /**
       * \class
       * \brief
       */
      class ssl_connection : public async_connection {

        ssl_connection(const ssl_connection &) = delete;
        ssl_connection &operator = (const ssl_connection &) = delete;

      public:

        /**
         * \brief
         */
        ssl_connection(boost::asio::io_service &io_service, const client_options &options)
          : io_service_(io_service)
          , options_(options) {

        }

        /**
         * \brief Destructor.
         */
        virtual ~ssl_connection() noexcept {

        }

        virtual void async_connect(const boost::asio::ip::tcp::endpoint &endpoint,
                                   const std::string &host,
                                   connect_callback callback) {
          context_.reset(new boost::asio::ssl::context(boost::asio::ssl::context::sslv23));
          auto certificate_paths = options_.openssl_certificate_paths();
          auto verifier_paths = options_.openssl_verify_paths();
          bool use_default_verification = certificate_paths.empty() && verifier_paths.empty();
          if (!use_default_verification) {
            for (auto path : certificate_paths) {
              context_->load_verify_file(path);
            }
            for (auto path : verifier_paths) {
              context_->add_verify_path(path);
            }
            context_->set_verify_mode(boost::asio::ssl::context::verify_peer);
            context_->set_verify_callback(boost::asio::ssl::rfc2818_verification(host));
          }
          else {
            context_->set_default_verify_paths();
            context_->set_verify_mode(boost::asio::ssl::context::verify_none);
          }
          socket_.reset(new boost::asio::ssl::stream<
                          boost::asio::ip::tcp::socket>(io_service_, *context_));

          using namespace std::placeholders;
          socket_->lowest_layer().async_connect(endpoint,
                                                [=] (const boost::system::error_code &ec) {
                                                  handle_connected(ec, callback);
                                                });
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
          //socket_->cancel();
        }

      private:

        void handle_connected(const boost::system::error_code &ec, connect_callback callback) {
          if (!ec) {
            auto existing_session = SSL_get1_session(socket_->native_handle());
            if (existing_session) {
              socket_->async_handshake(boost::asio::ssl::stream_base::client, callback);
            }
            else {
              SSL_set_session(socket_->native_handle(), existing_session);
              SSL_connect(socket_->native_handle());
              callback(ec);
            }
          }
          else {
            callback(ec);
          }
        }

        boost::asio::io_service &io_service_;
        client_options options_;
        std::unique_ptr<boost::asio::ssl::context> context_;
        std::unique_ptr<
          boost::asio::ssl::stream<boost::asio::ip::tcp::socket>> socket_;

      };
      } // namespace client_connection
    } // namespace v2
  } // namespace http
} // namespace network

#endif // NETWORK_HTTP_V2_CLIENT_CONNECTION_SSL_CONNECTION_INC
