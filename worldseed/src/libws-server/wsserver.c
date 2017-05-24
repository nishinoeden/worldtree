#include <stdio.h>
#include <stdlib.h>

#include "wsbasics.h"
#include "wthread.h"

/**
 * main(): kicks off the program
 */
int main( int argc, char **argv ) {
    worker_t *worker = ws_wtd_new();
    int      rc;
    long     i = 0;
    
    ws_print_header();
    ws_wtd_start( worker );

    /* print final result once threads run to completion */
    noticemsg( "Threads completed execution." );
    return 0;
}

