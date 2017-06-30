CXX = gcc
LIBS = -lpthread -lzmq
OPTS = -Wl,-rpath=/usr/local/lib

# our list od dependencies and objects
DEPS = wsbasics.h wthread.h
OBJS = wsserver.o wthread.o wsbasics.o

# finalize flags
CFLAGS = 

%.o:        %.c $(DEPS)
	        $(CXX) -c -o $@ $< $(CFLAGS)

wsserver:	$(OBJS)
	        $(CXX) -o $@ $^ $(CFLAGS) $(LIBS) $(OPTS)

clean:	    
	        rm -rf wsserver

clear:
	        rm -rf *.o

#all:	    
#	        $(CXX) -o wsserver wsserver.c wthread.c wsbasics.c $(LIBS) $(OPTS)
