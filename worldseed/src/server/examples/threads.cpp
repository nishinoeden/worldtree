#include <iostream>
#include <cstdlib>
#include <pthread.h>

#define NUM_THREADS 12

void* printHello( void *threadId ) {
    long thread_id = (long)threadId;

    for( int i = 0; i < 5; i++ ) {
        std::cout << ">>> [thread: " << thread_id << "] $ Hello, World!" << std::endl;
        sleep( 1 );
    }

    pthread_exit( NULL );
}

int main( int argc, char **argv ) {
    pthread_t threads[NUM_THREADS];
    int       rc, i;

    std::cout << "///////////////////////////////////////////////////" << std::endl;
    std::cout << "// W o r l d S e e D  Thread Test /////////////////" << std::endl;
    std::cout << "///////////////////////////////////////////////////" << std::endl;

    for( i = 0; i < NUM_THREADS; i++ ) {
        std::cout << "*** main() : creating thread, " << i << std::endl;
        rc = pthread_create( &threads[i], NULL, printHello, (void *)i );

        if( rc ) {
            std::cerr << "!!! unable to create thread, " << rc << std::endl;
            exit( -1 );
        }
    }

    pthread_exit( NULL );
    return rc;
}
