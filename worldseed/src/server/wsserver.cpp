#include <zmq.hpp>
#include <iostream>
#include <string>

#ifndef _WIN32
    #include <unistd.h>
#else
    #include <windows.h>
    #define sleep(n)    Sleep(n)
#endif

int main( int argc, char **argv ) {
    zmq::context_t context( 1 /* I/O threads */ );
    zmq::socket_t  socket( context, ZMQ_REP );
    int            major, minor, patch;

    zmq_version( &major, &minor, &patch );
    socket.bind( "tcp://*:5555" );

    std::cout << "///////////////////////////////////////////////////" << std::endl;
    std::cout << "// W o r l d S e e D  ZeroMQ Test /////////////////" << std::endl;
    std::cout << "///////////////////////////////////////////////////" << std::endl;
    std::cout << "*** Running ØMQ " << major << "." << minor << "." << patch << std::endl;

    try {
        do /* main execution loop */ {{{
            // send a reply back to client
            zmq::message_t reply( 13 );
            zmq::message_t request;

            // wait for next request from client
            socket.recv( &request );
            std::cout << "*** received: " << request.data() << std::endl;

            // do some stuff
            sleep( 1 );

            // send a reply back to client
            memcpy( reply.data(), "*** WorldSeeD", 13 );
            socket.send( reply );
        }}} while( true );
    } catch( const char *msg ) {
        std::cerr << "*** Exception occurred: " << msg << std::endl;
    }

    return 0;
}
