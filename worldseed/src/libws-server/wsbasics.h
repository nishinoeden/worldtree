#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>

/* define log levels */
#define LOG_PID     1
#define LOG_CRIT    2
#define LOG_ERR     3
#define LOG_WARNING 4 
#define LOG_NOTICE  5

/* defines ANSI color codes */
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

/* define ANSI bold colors */
#define B_RED   "\x1B[1;31m"
#define B_GRN   "\x1B[1;32m"
#define B_YEL   "\x1B[1;33m"
#define B_BLU   "\x1B[1;34m"
#define B_MAG   "\x1B[1;35m"
#define B_CYN   "\x1B[1;36m"
#define B_WHT   "\x1B[1;37m"

/**
 * Displays a message to STDOUT.  The message will be prefixed with a !!! when
 * $level is LOG_ERR, /!\ when $level is LOG_WARNING, and will be prefixed with
 * a *** on any other level
 *
 * @function printmsg
 * @param int level The log level of the message
 * @param const char* string The formatted string for output
 * @param va_args args The arguments for the formatted string
 */
void printmsg( int level, const char *string, va_list args );

/**
 * Convenience method for message( LOG_ERR, $message ).  The optional $quit flag
 * (defaults to true) quits the application after printing the message to the screen.
 *
 * @param bool quit Flag to quit the program
 * @param const char* string The formatted string for output
 * @param mixed ... The arguments for the string
 */
void errormsg( bool quit, const char *string, ... );

/**
 * Convenience method for message( LOG_WARNING, string, ... ).  Should be used
 * exclusively for displaying warning messages
 *
 * @param const char* string The message to be displayed
 * @param mixed ... The arguments for the string
 */
void warningmsg( const char *string, ... );

/**
 * Convenience method for message( LOG_NOTICE, string, ... ).  Should be used
 * exclusively for displaying notice/debug messages
 *
 * @param const char* string The message to be displayed
 * @param mixed ... The arguments for the string
 */
void noticemsg( const char *string, ... );
