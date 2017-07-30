#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 12

void* printHello( void *threadId ) {
    long thread_id = (long)threadId;
    int  i;

    for( i = 0; i < 5; i++ ) {
        printf( ">>> [thread: %d] $ Hello, World!\r\n", thread_id ); 
        sleep( 1 );
    }

    pthread_exit( NULL );
}

int main( int argc, char **argv ) {
    pthread_t threads[NUM_THREADS];
    int       rc;
    long      i;

    printf( "///////////////////////////////////////////////////\r\n" );
    printf( "// W o r l d S e e D  Thread Test /////////////////\r\n" );
    printf( "///////////////////////////////////////////////////\r\n" );

    for( i = 0; i < NUM_THREADS; i++ ) {
        printf( "*** main() : creating thread, %d\r\n", i );
        rc = pthread_create( &threads[i], NULL, printHello, (void *)i );

        if( rc ) {
            printf( "!!! unable to create thread, %d - rc %d\r\n", i, rc );
            exit( -1 );
        }

        sleep(1);
    }

    pthread_exit( NULL );
    return rc;
}
