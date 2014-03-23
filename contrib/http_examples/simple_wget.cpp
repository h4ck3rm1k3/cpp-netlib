// Copyright (c) Glyn Matthews 2009-2013.
// Copyright 2012 Google, Inc.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//[ simple_wget_main
/*`
  This is a very basic clone of wget. It's missing a lot of
  features, such as content-type detection, but it does the
  fundamental things the same.

  It demonstrates the use of the `uri` and the `http::client`.
*/

#include <network/http/client.hpp>
#include <string>
#include <fstream>
#include <iostream>

namespace http = network::http;

namespace {
std::string get_filename(const std::string& path) {
  auto index = path.find_last_of('/');
  auto filename = path.substr(index + 1);
  return filename.empty() ? "index.html" : filename;
}
}  // namespace

int main(int argc, char* argv[]) {

  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " url" << std::endl;
    return 1;
  }

  try {
    http::client client;
    http::request request{network::uri{std::string{argv[1]}}};
    request.version("1.0");
    request.append_header("Connection", "close");
    request.append_header("User-Agent", "cpp-netlib simple_wget example");
    auto future_response = client.get(request);
    auto response = future_response.get();

    auto filename = get_filename(request.path());
    std::cout << "Saving to: " << filename << std::endl;
    std::ofstream ofs(filename.c_str());
    ofs << response.body() << std::endl;
  }
  catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  return 0;
}
