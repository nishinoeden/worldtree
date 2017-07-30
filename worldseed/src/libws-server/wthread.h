#include <stdio.h>

/**
 * device_t contains the structure for the zmq context
 * sockets, dealers, and routers.
 *
 * @var void* context the zmq context
 * @var void* socket  the zmq socket struct
 */
typedef struct device device_t;

/**
 * worker_t struct contains the structure for the worker
 * thread that handles incoming socket connections and
 * handling all requests.
 *
 * @var pthread_t thread the worker thread
 * @var device_t device the device structure
 * @var int id the ID for the thread
 */
typedef struct worker worker_t;

/**
 * ws_wtd_new() creates a new worker_t struct and returns
 * it to the calling method. All member variables are
 * initialized before returning.
 *
 * @return worker_t*
 */
worker_t *ws_wtd_new();

/**
 * ws_wtd_start() spawns a new thread, calling the
 * ws_wtd_exec function which manages the worker thread
 *
 * @param worker_t* worker The worker thread struct
 * @return void* null
 */
void *ws_wtd_start( worker_t *worker );

/**
 * ws_wtd_exec() is called by the pthread_create function,
 * and is responsible for creating the zmq context, binding to,
 * and handling all incoming connections on a specified address
 * and port.
 *
 * @param void* wtd A reference to a worker_t struct
 * @return void* null
 */
void *ws_wtd_exec( void *wtd );

/**
 * ws_wtd_listen() handles all requests from the client, passing
 * the request off to the dispatcher, which will handle all of
 * the background processing for all requests.
 *
 * @param worker_t* worker The worker thread struct
 * @return void* null
 */
void *ws_wtd_listen( worker_t *worker );

/**
 * Prints the header and ZMQ version to stdout
 *
 * @return void* null
 */
void *ws_print_header();
