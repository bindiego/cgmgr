PWD := $(shell pwd)
includedir=$(PWD)/include
srcdir=$(PWD)/src
libsdir=$(PWD)/libs
CC=g++
AR=ar
CFLAGS=-I$(includedir) -L$(srcdir) -g -pthread -fPIC -c -Wall -std=c++11
LDFLAGS=-L$(libsdir) -g -fPIC
LDLIBS=-pthread
OBJECTS=$(SOURCES:.cpp=.o)
SOURCES=cgmgr.cpp
alib=libcgmgr.a
dylib=libcgmgr.so

all: static dynamic
	cp *.a *.so $(PWD)/../cgmgr/libs

%.o: $(srcdir)/%.cpp
	$(CC) $(CFLAGS) $< -o $@

static: $(OBJECTS)
	$(AR) rvs $(alib) $(OBJECTS)
	cp $(PWD)/include/*.h $(PWD)/../cgmgr/include
	cp *.a $(PWD)/../cgmgr/libs
	cp $(PWD)/include/*.h $(PWD)/../jni/include
	cp *.a $(PWD)/../jni/libs

dynamic: $(OBJECTS)
	$(CC) $(LDFLAGS) -shared $(OBJECTS) -o $(dylib) $(LDLIBS)
	cp $(PWD)/include/*.h $(PWD)/../cgmgr/include
	cp *.so $(PWD)/../cgmgr/libs

clean:
	@-rm -rf *.o $(alib) $(dylib)
