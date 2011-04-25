// Copyright 2009 (c) Tarro, Inc.
// Copyright 2009 (c) Dean Michael Berris <mikhailberis@gmail.com>
// Hacked by James Michael DuPont<h4ck3rm1k3@flossk.org>
// Was Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Now Distributed under the License AGPL http://www.gnu.org/licenses/agpl-3.0.html
// Changes copyright 2011 James Michael DuPont <h4ck3rm1k3@flossk.org>
// 
/*`

  Run like this : ./cpp-netlib-geosp00k localhost 3000
  
See my blog posts about this idea here :
  http://osmopenlayers.blogspot.com/2011/04/location-spoofing-tool-latlonsp00k.html
and the perl implementation here: 
http://osmopenlayers.blogspot.com/2011/04/geospook-dancer.html

Source code now checked in here:
https://github.com/h4ck3rm1k3/cpp-netlib

Use this in firefox like this :
user_pref("geo.wifi.uri", "http://localhost:3000/location/");

so go to about:config in your browser and set the key geo.wifi.uri to point to your server.

It does not matter what url you use, it always answers the same one.
  
 */
#include <boost/network/protocol/http/server.hpp>
#include <boost/network/protocol/http/impl/response.ipp>
#include <iostream>
#include <boost/asio/buffer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/network/protocol/http/tags.hpp>
#include <boost/network/traits/string.hpp>
#include <boost/network/protocol/http/traits/vector.hpp>
#include <boost/network/protocol/http/message/header.hpp>


namespace http = boost::network::http;


/*<< Defines the server. >>*/
struct geosp00k;
typedef http::server<geosp00k> myserver;
using namespace boost::network::http;
/*<< Defines the request handler.  It's a class that defines two
     functions, `operator()` and `log()` >>*/
struct geosp00k {

  geosp00k()
    :
    lat(42.65402),
    lon(21.1598),
    alt(100.0),
    speed(300.0)
  {

  }
  double lat;
  double lon;
  double alt;
  double speed;


  static boost::network::http::basic_response<tags::http_server> stock_reply(
boost::network::http::basic_response<boost::network::http::tags::http_server>::status_type
 status, std::string content) {
            using boost::lexical_cast;
            basic_response<tags::http_server> rep;
            rep.status = status;
            rep.content = content;
            rep.headers.resize(2);
            rep.headers[0].name = "Content-Length";
            rep.headers[0].value = lexical_cast<std::string>(rep.content.size());
            rep.headers[1].name = "Content-Type";
            rep.headers[1].value = "application/json";
            return rep;
        }

    /*<< This is the function that handles the incoming request. >>*/
    void operator() (myserver::request const &request,
                     myserver::response &response) {
      //        myserver::string_type ip = source(request);
	alt += 0.1;
	lat += 0.001;
	lon += 0.001;

        std::ostringstream data;
        data <<"{\"location\":{\"latitude\":"<< lat 
	     <<",\"longitude\":"<< lon
	     <<",\"accuracy\":10," 
	     <<"\"speed\":" << speed
	     <<",\"altitude\":" << alt 
	     <<"}}";;
        response = stock_reply(myserver::response::ok, data.str());

	std::cerr <<" latitude:"<< lat 
	     <<" longitude:"<< lon
	     <<" altitude:" << alt 
	     <<"\n";

    }
    /*<< It's necessary to define a log function, but it's ignored in
         this example. >>*/
    void log(...) {
        // do nothing
    }
};


int main(int argc, char * argv[]) {
    
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " address port" << std::endl;
        return 1;
    }

    try {
        /*<< Creates the request handler. >>*/
      geosp00k handler;
        /*<< Creates the server. >>*/
      myserver server_(argv[1], argv[2], handler);
        /*<< Runs the server. >>*/
        server_.run();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
//]
