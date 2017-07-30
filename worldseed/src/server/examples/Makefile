threads:	threads.c
	        gcc -o threadsc threads.c $(LINK_OPTS)

threadscpp:	threads.cpp
	        g++ -o threads threads.cpp $(LINK_OPTS)

all:	    
	        gcc -o threadsc threads.c $(LINK_OPTS)
	        g++ -o threads threads.cpp $(LINK_OPTS)

clean:	    
	        rm -rf threads threadsc

LINK_OPTS = -lpthread
#OPTS = -Wl,-rpath=/usr/local/lib
