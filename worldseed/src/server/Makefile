wsserver:	worldSeeD.cpp
	        g++ -o wsserver worldSeeD.cpp $(LINK_OPTS) $(OPTS)

wsclient:	wsclient.cpp
	        g++ -o wsclient wsclient.cpp $(LINK_OPTS) $(OPTS)

all:	    
	        g++ -o wsserver worldSeeD.cpp $(LINK_OPTS) $(OPTS)
	        g++ -o wsclient wsclient.cpp $(LINK_OPTS) $(OPTS)

clean:	    
	        rm -rf wsserver wsclient

LINK_OPTS = -lzmq
OPTS = -Wl,-rpath=/usr/local/lib
