#include "wthread.h"

#include <stdio.h>
#include <stdlib.h>
//#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include <zmq.h>

#define NUM_THRD 5    /* number of threads */

/**
 * typedef struct device device_t;
 *
 * device_t contains the structure for the zmq context
 * sockets, dealers, and routers.
 *
 * @var void* context the zmq context
 * @var void* socket  the zmq socket struct
 */
struct device {
    void      *context;
    void      *socket;
};

/**
 * typedef struct worker worker_t;
 *
 * worker_t struct contains the structure for the worker
 * thread that handles incoming socket connections and
 * handling all requests.
 *
 * @var pthread_t thread the worker thread
 * @var device_t device the device structure
 * @var int id the ID for the thread
 */
struct worker {
    pthread_t  thread;
    device_t   device;
    worker_t   *next;
    worker_t   *prev;
    int        id;
};

/**
 * ws_wtd_new() creates a new worker_t struct and returns
 * it to the calling method. All member variables are
 * initialized before returning.
 *
 * @return worker_t*
 */
worker_t *ws_wtd_new() {
    worker_t *wthread = malloc( sizeof(worker_t) );
    int       rc, tLimit;
    long      tid;
    
    wthread->next = NULL;
    wthread->prev = NULL;
    wthread->id = 0;

    return wthread;
}

/**
 * ws_wtd_start() spawns a new thread, calling the
 * ws_wtd_exec function which manages the worker thread
 *
 * @param worker_t* worker The worker thread struct
 * @return void* null
 */
void *ws_wtd_start( worker_t *worker ) {
    int      rc;
    long     i = 0;

    rc = pthread_create( &worker->thread, NULL, ws_wtd_exec, worker );

    if( rc ) {
        fprintf( stderr, "!!! unable to create worker thread, rc %d\r\n", rc );
        exit( -1 );
    }

    /* join on main worker thread and wait for completion */
    pthread_join( worker->thread, NULL );
}

/**
 * ws_wtd_exec() is called by the pthread_create function,
 * and is responsible for creating the zmq context, binding to,
 * and handling all incoming connections on a specified address
 * and port.
 *
 * @param void* wtd A reference to a worker_t struct
 * @return void* null
 */
void *ws_wtd_exec( void *wtd ) {
    // create a new context and socket
    worker_t *worker = (worker_t *)wtd;
    worker->device.context = zmq_ctx_new();
    worker->device.socket = zmq_socket( worker->device.context, ZMQ_REP );
    int      rc = zmq_bind( worker->device.socket, "tcp://*:5555" );

    assert( rc == 0 );       /* ensure worker binds on socket */
    ws_wtd_listen( worker ); /* begin accepting incoming connections */

    // clean up all messes
    zmq_close( worker->device.socket );
    zmq_ctx_destroy( worker->device.context );
    pthread_exit( NULL );
}

/**
 * ws_wtd_listen() handles all requests from the client, passing
 * the request off to the dispatcher, which will handle all of
 * the background processing for all requests.
 *
 * @param worker_t* worker The worker thread struct
 * @return void* null
 */
void *ws_wtd_listen( worker_t *worker ) {
    int      numRequest = 0;

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
    }}} while( 1 );

    return NULL;
}

/**
 * Prints the header and ZMQ version to stdout
 *
 * @return void* null
 */
void* ws_print_header() {
    int  major, minor, patch;

    zmq_version( &major, &minor, &patch );
    printf( "///////////////////////////////////////////////////\r\n" );
    printf( "// W o r l d S e e D  Thread Test /////////////////\r\n" );
    printf( "///////////////////////////////////////////////////\r\n" );
    printf( "*** Running ØMQ %d.%d.%d\r\n", major, minor, patch );

    return NULL;
}

