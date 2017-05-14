#!/usr/bin/python
''' 
    Simple Socket Server using Threads
'''

import socket
import sys

HOST = ''   # Symbolic name, meaning all available interfaces
PORT = 8888 # Arbitrary non-privileged port

print "///////////////////////////////////////////////////"
print "// W o r l d S e e D  0MQ Test ////////////////////"
print "///////////////////////////////////////////////////"

sock = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
print '*** Socket created.'

# Bind socket to local host and port
try:
    sock.bind(( HOST, PORT ))
except:
    print '*** ERROR: Bind failed; ERR_CODE: ' + str( msg[0] ) + ' MESSAGE : ' + msg[1]
    sys.exit()

print '*** Socket bind on \'' + HOST + ':' + str( PORT ) + '\''

# Start listening on socket
sock.listen( 10 )
print '*** Socket currently listening on \'' + HOST + ':' + str( PORT ) + '\''

# Now, keep talking with the client
while 1:
    # wait on a connection (blocking call)
    conn, addr = sock.accept()
    print '<< Connected to ' + addr[0] + ':' + str(addr[1])

# close the socket connection
sock.close()
