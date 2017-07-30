#include <zmq.hpp>
#include <iostream>
#include <string>

int main( int argc, char **argv ) {
    zmq::context_t context( 1 /* I/O threads */ );
    zmq::socket_t  socket( context, ZMQ_REQ );

    std::cout << "///////////////////////////////////////////////////" << std::endl;
    std::cout << "// W o r l d S e e D  Client Test /////////////////" << std::endl;
    std::cout << "///////////////////////////////////////////////////" << std::endl;
    std::cout << "<< Connecting to the worldSeeD Server..." << std::endl;
    socket.connect( "tcp://localhost:5555" );

    // do 10 requests, waiting 1 second per request
    for( int numRequest = 0; numRequest < 10; numRequest++ ) {
        // prepare request and send "Hello"
        zmq::message_t request( 5 );
        memcpy( request.data(), "00000", 5 );
        std::cout << "<< Sending 'Hello'... [" << numRequest << "]" << std::endl;
        socket.send( request );

        // get the reply from the server
        zmq::message_t reply;
        socket.recv( &reply );
        std::cout << ">> Received: " << " [" << numRequest << "]" << std::endl;
    }

    return 0;
}
