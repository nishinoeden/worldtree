#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include <zmq.h>

#define NUM_THRD 5    /* number of threads */

typedef struct device device_t;
struct device {
    void      *context;
    void      *socket;
};

/**
 * worker_t struct contains the structure for all worker threads.
 */
typedef struct worker worker_t;
struct worker {
    pthread_t  thread;
    device_t   device;
    worker_t   *next;
    worker_t   *prev;
    int        id;
};

worker_t* ws_wtd_new() {
    worker_t *wthread = malloc( sizeof(worker_t) );
    int       rc, tLimit;
    long      tid;
    
    wthread->next = NULL;
    wthread->prev = NULL;
    wthread->id = 0;

    return wthread;
}

void *ws_wtd_init( void *wtd ) {
    // create a new context and socket
    worker_t *worker = (worker_t *)wtd;
    worker->device.context = zmq_ctx_new();
    worker->device.socket = zmq_socket( worker->device.context, ZMQ_REP );
    int      rc = zmq_bind( worker->device.socket, "tcp://*:5555" );
    int      numRequest = 0;

    assert( rc == 0 );  /* ensure worker binds on socket */

    do /* main execution loop */ {{{
        char buffer[255];
        int  retval = 0;

        // waits on socket to receive a connection
        retval = zmq_recv( worker->device.socket, buffer, 255, 0 );
        printf( ">> received [%d:%d]: %s\r\n", numRequest, retval, buffer );

        // do some stuff
        usleep( 50000 );

        // send response back to client
        zmq_send( worker->device.socket, "WORLDSEED", 9, 0 );
        numRequest++;
    }}} while( numRequest < 128 );

    // clean up all messes
    zmq_close( worker->device.socket );
    zmq_ctx_destroy( worker->device.context );
    pthread_exit( NULL );
}

void* ws_print_header() {
    int  major, minor, patch;

    zmq_version( &major, &minor, &patch );
    printf( "///////////////////////////////////////////////////\r\n" );
    printf( "// W o r l d S e e D  Thread Test /////////////////\r\n" );
    printf( "///////////////////////////////////////////////////\r\n" );
    printf( "*** Running ØMQ %d.%d.%d\r\n", major, minor, patch );

    return NULL;
}

/**
 * main(): kicks off the program
 */
int main( int argc, char **argv ) {
    worker_t *worker = ws_wtd_new();
    int      rc;
    long     i = 0;
    
    ws_print_header();

    printf( "*** main() : creating threads\r\n" );
    rc = pthread_create( &worker->thread, NULL, ws_wtd_init, worker );
    
    if( rc ) {
        printf( "!!! unable to create thread, %d - rc %d\r\n", i, rc );
        exit( -1 );
    }

    /* join on main worker thread and wait for completion */
    pthread_join( worker->thread, NULL );

    /* print final result once threads run to completion */
    printf( "*** Threads completed execution.\r\n" );
    return 0;
}

