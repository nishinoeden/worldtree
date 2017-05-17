wsserver:	wsserver.c
	        $(CXX) -o wsserver wsserver.c $(LINK_OPTS) $(OPTS)

all:	    
	        $(CXX) -o wsserver wsserver.c $(LINK_OPTS) $(OPTS)

clean:	    
	        rm -rf wsserver

CXX = gcc
LINK_OPTS = -lpthread -lzmq
OPTS = -Wl,-rpath=/usr/local/lib
