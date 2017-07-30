clean:	    
	        rm -rf wsserver wsclient

wsclient:	wsclient.cpp
	        g++ -o wsclient wsclient.cpp $(LINK_OPTS) $(OPTS)

wsserverc:	wsserver.c
	        gcc -o wsserver wsserver.c $(LINK_OPTS) $(OPTS)

wsserver:	wsserver.cpp
	        g++ -o wsserver wsserver.cpp $(LINK_OPTS) $(OPTS)

all:	    
	        g++ -o wsserver wsserver.cpp $(LINK_OPTS) $(OPTS)
	        g++ -o wsclient wsclient.cpp $(LINK_OPTS) $(OPTS)

LINK_OPTS = -lzmq
OPTS = -Wl,-rpath=/usr/local/lib
