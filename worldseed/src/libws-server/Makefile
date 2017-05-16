wsserver:	wsserver.c
	        $(CXX) -o wsserver wsserver.c $(LINK_OPTS)

threads:	threads.c
	        $(CXX) -o threads threads.c $(LINK_OPTS)

all:	    
	        $(CXX) -o threads threads.c $(LINK_OPTS)
	        $(CXX) -o wsserver wsserver.c $(LINK_OPTS)

clean:	    
	        rm -rf threads wsserver

CXX = gcc
LINK_OPTS = -lpthread
#OPTS = -Wl,-rpath=/usr/local/lib
