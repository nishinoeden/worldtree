#!/usr/bin/php -q
<?php
/**
 * Socket testing
 *
 * Uses PHP builtin socket library to create a server, creating
 * a new socket, binding on the ip and port, and sending & receiving
 * messages/data.
 *
 * @author Skyler Sully <echelon.alchemist@gmail.com>
 */
$ipaddr = "0.0.0.0";
socketConfig( $socket, $ipaddr, 5555 );

printf( "///////////////////////////////////////////////////". PHP_EOL );
printf( "// W o r l d S e e D  ØMQ Test ////////////////////". PHP_EOL );
printf( "///////////////////////////////////////////////////". PHP_EOL );

$counter = 0; /* initialize counter */
do /* main execution loop */ {{{
    $iSocket = socket_accept( $socket );
    socket_set_blocking( $iSocket, true );
    echo ">> Client {$iSocket} connected.". PHP_EOL;
    //stream_set_blocking( $iSocket, true );
    $request = fgets( $iSocket ); // blocks on request
    echo ">> Received: {$request}". PHP_EOL;

    // send a reply
    $reply = "*** [ECHO](wsserver): ". strrev( $request );
    fwrite( $iSocket, $reply );
    $counter++;
}}} while( $counter < 10 );

// close the socket
fclose( $socket );
return 0;

function socketConfig( &$socket, $ip = "127.0.0.1", $port = 5555 ) {{{
    $socket = socket_create(
        AF_INET, SOCK_STREAM, getprotobyname("tcp")
    ); // create TCP socket resource

    if( !is_resource( $socket ) ) {
        echo "*** error: couldn't create socket resource.". PHP_EOL;
        echo socketError( $socket );
        die();
    }

    // bind socket to IP and port
    if( !socket_bind( $socket, $ip, $port ) ) {
        echo "*** error: couldn't bind to tcp://{$ip}:{$port}". PHP_EOL;
        echo socketError( $socket );
        die();
    }

    // begin listening on proto://ip:port
    if( !socket_listen( $socket, 10 ) ) {
        echo "*** error: couldn't listen on tcp://{$ip}:{$port}". PHP_EOL;
        echo socketError( $socket );
        die();
    }
    
    stream_set_blocking( $socket, true );
    return $socket;
}}}

function socketError( $socket = null ) {{{
    if( is_resource( $socket ) ) {
        $eCode = socket_last_error( $socket );
    } else {
        $eCode = socket_last_error();
    }

    // get the message using the error code
    $message = socket_strerror( $eCode );
    // clear out socket error
    if( is_resource( $socket ) ) {
        socket_clear_error( $socket );
    }

    return "    what(): (${eCode}) ${message}". PHP_EOL;
}}}
