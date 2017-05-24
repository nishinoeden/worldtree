CXX = gcc
LIBS = -lpthread -lzmq
OPTS = -Wl,-rpath=/usr/local/lib

# our list od dependencies and objects
DEPS = wsbasics.h wthread.h
OBJS = wsserver.o wthread.o wsbasics.o

# finalize flags
CFLAGS = $(OPTS)

%.o:        %.c $(DEPS)
	        $(CXX) -c -o $@ $< $(CFLAGS)

wsserver:	$(OBJS)
	        $(CXX) -o $@ $^ $(CFLAGS) $(LIBS)
			rm -rf $^

all:	    
	        $(CXX) -o wsserver wsserver.c wthread.c wsbasics.c $(LIBS) $(OPTS)

clean:	    
	        rm -rf wsserver

