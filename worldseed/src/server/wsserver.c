#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

int main( int argc, char **argv ) {
    // socket to talk to clients
    void *context = zmq_ctx_new();
    void *socket = zmq_socket( context, ZMQ_REP );
    int  rc = zmq_bind( socket, "tcp://*:5555" );
    int  major, minor, patch;

    zmq_version( &major, &minor, &patch );
    assert( rc == 0 );

    printf( "///////////////////////////////////////////////////\r\n" );
    printf( "// W %d r l d S e e D  ØMQ Test ////////////////////\r\n", rc );
    printf( "///////////////////////////////////////////////////\r\n" );
    printf( "*** Running ØMQ %d.%d.%d\r\n", major, minor, patch );

    do /* main execution loop */ {
        char buffer[255];
        int  numRequest = 0, retval = 0;
        // waits on socket to receive a connection
        retval = zmq_recv( socket, buffer, 255, 0 );
        printf( ">> received [%d:%d]: %s\r\n", numRequest, retval, buffer );       

        // do some stuff
        sleep( 1 );
        // send response back to client
        zmq_send( socket, "-=[ wsserver ]=-", 16, 0 );
    } while( 1 );

    return 0;
}
