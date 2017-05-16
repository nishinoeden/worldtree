#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define L_NTHD 5    /* number of threads */

typedef struct device device_t;
struct device {
    void      *context;           /* zmq context */
    void      *socket;            /* zmq socket object */
};

/**
 * worker_t struct contains the structure for all worker threads.
 */
typedef struct worker {
    pthread_t  wrapper;            /* the wrapper thread */
    pthread_t  threads[L_NTHD];    /* the thread pool */
    device_t   device;
    char       *name;              /* name of the worker thread */
    int        id;                 /* id of the worker thread */
} worker_t;

void *printHello( void* threadId ) {
    long thread_id = (long)threadId;
    int  i;

    for( i = 0; i < L_NTHD; i++ ) {
        printf( ">>> running thread %d\r\n", thread_id );
        sleep(1);
    }

    pthread_exit( NULL );
}

/**
 * main(): kicks off the program
 */
int main( int argc, char **argv ) {
    printf( "Hello, World!\r\n" );

    worker_t worker;
    long    rc, i = 99;

    printf( "*** main() : creating threads\r\n" );
    rc = pthread_create( &worker.wrapper, NULL, printHello, (void *)i );

    pthread_exit( NULL );
    return 0;
}


