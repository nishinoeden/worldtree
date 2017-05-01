#include <zmq.hpp>
#include <iostream>

int main( int argc, char** argv ) {
    zmq::context_t context( 1 /* I/O threads */ );
    zmq::socket_t  socket( context, ZMQ_REP );
    socket.bind( "tcp://lo:5555" );

    std::cout << "///////////////////////////////////////////////////" << std::endl;
    std::cout << "// W o r l d S e e D  ZeroMQ Test /////////////////" << std::endl;
    std::cout << "///////////////////////////////////////////////////" << std::endl;

    do {{{
        // wait for next request from client
        zmq::message_t request;
        socket.recv( &request );
        std::cout << "*** received: " << request.data() << std::endl;

        // do some stuff
        sleep( 1 );

        // send a reply back to client
        zmq::message_t reply( 13 );
        //memcpy( reply.data(), "Message rcvd!", 13 );
        memcpy( reply.data(), "*** WorldSeeD", 13 );
        socket.send( reply );
    }}} while( true );

    return 0;
}
