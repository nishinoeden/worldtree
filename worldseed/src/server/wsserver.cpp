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
    socket.bind( "tcp://*:5555" );

    std::cout << "///////////////////////////////////////////////////" << std::endl;
    std::cout << "// W o r l d S e e D  ZeroMQ Test /////////////////" << std::endl;
    std::cout << "///////////////////////////////////////////////////" << std::endl;

    do /* main execution loop */ {{{
        // send a reply back to client
        zmq::message_t reply( 13 );
        memcpy( reply.data(), "Message rcvd!", 13 );
        //socket.send( reply );

        zmq::message_t request;

        // wait for next request from client
        socket.recv( &request );
        socket.send( reply );
        std::cout << "*** received: " << request.data() << std::endl;

        // do some stuff
        sleep( 1 );

        // send a reply back to client
        //zmq::message_t reply( 13 );
        memcpy( reply.data(), "*** WorldSeeD", 13 );
        socket.send( reply );
    }}} while( true );

    return 0;
}
