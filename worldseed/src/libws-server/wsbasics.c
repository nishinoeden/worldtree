#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "wsbasics.h"

/**
 * Displays a message to STDOUT.  The message will be prefixed with a !!! when
 * $level is LOG_ERR, /!\ when $level is LOG_WARNING, and will be prefixed with
 * a *** on any other level
 *
 * @function printmsg
 * @var int level The log level of the message
 * @var const char* string The formatted string for output
 * @var va_args args The arguments for the formatted string
 */
void *printmsg( int level, const char *string, va_list args ) {
    time_t  date;
    char    buffer[20], prefix[4];

    time( &date );            /* get the current time and format */
    strftime( buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", gmtime(&date) );
    
    // determine whether to use stdout or stderr
    if( level == LOG_ERR || level == LOG_CRIT ) {
        strcpy( prefix, "!!!" );
        fprintf( stderr, B_WHT "[" B_GRN "%s" B_WHT "] " B_RED "%s " RESET, buffer, prefix );
        vfprintf( stderr, string, args );
        fprintf( stderr, "\r\n" );
    } else {
        if( level == LOG_WARNING ) {
            strcpy( prefix, "/!\\" );
            fprintf( stdout, B_WHT "[" B_GRN "%s" B_WHT "] " B_YEL "%s " RESET, buffer, prefix );
        } else {
            strcpy( prefix, "***" );
            fprintf( stdout, B_WHT "[" B_GRN "%s" B_WHT "] " B_BLU "%s " RESET, buffer, prefix );
        }

        vfprintf( stdout, string, args );
        fprintf( stdout, "\r\n" );
    }
}

/**
 * Convenience method for message( LOG_ERR, $message ).  The optional $quit flag
 * (defaults to true) quits the application after printing the message to the screen.
 *
 * @param bool quit Flag to quit the program
 * @param const char* string The formatted string for output
 * @param mixed ... The arguments for the string
 */
void *errormsg( bool quit, const char *string, ... ) {
    va_list args;
    
    va_start( args, string ); /* format the string w/ args */
    printmsg( LOG_ERR, string, args );
    va_end( args );

    if( quit ) {
        warningmsg( "Quitting program..." );
    }
}

/**
 * Convenience method for message( LOG_WARNING, string, ... ).  Should be used
 * exclusively for displaying warning messages
 *
 * @param const char* string The message to be displayed
 * @param mixed ... The arguments for the string
 */
void *warningmsg( const char *string, ... ) {
    va_list args;
    
    va_start( args, string ); /* format the string w/ args */
    printmsg( LOG_WARNING, string, args );
    va_end( args );
}

/**
 * Convenience method for message( LOG_NOTICE, string, ... ).  Should be used
 * exclusively for displaying notice/debug messages
 *
 * @param const char* string The message to be displayed
 * @param mixed ... The arguments for the string
 */
void *noticemsg( const char *string, ... ) {
    va_list args;
    
    va_start( args, string ); /* format the string w/ args */
    printmsg( LOG_NOTICE, string, args );
    va_end( args );
}
