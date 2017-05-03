all:		worldSeeD.cpp wsclient.cpp
			g++ -o worldSeed-server worldSeeD.cpp $(LINK_OPTS) $(OPTS)
			g++ -o wsclient wsclient.cpp $(LINK_OPTS) $(OPTS)

clean:		
			rm -rf worldSeed-server wsclient

wsserver:	worldSeeD.cpp
			g++ -o worldSeed-server worldSeeD.cpp $(LINK_OPTS) $(OPTS)

wsclient:	wsclient.cpp
			g++ -o wsclient wsclient.cpp $(LINK_OPTS) $(OPTS)

LINK_OPTS = -lzmq
OPTS = -Wl,-rpath=/usr/local/lib
