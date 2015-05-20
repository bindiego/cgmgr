PWD := $(shell pwd)
includedir=$(PWD)/include
srcdir=$(PWD)/src
libsdir=$(PWD)/libs
CC=g++
CFLAGS=-I$(includedir) -L$(srcdir) -g -pthread -c -Wall -fopenmp -std=c++11
LDFLAGS=-L$(libsdir) -g
LDLIBS=-pthread -lgomp -lcgmgr
SOURCES=cgmgr.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXE=cgmgr

.PHONY:
all: $(SOURCES) $(EXE)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

$(EXE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LDLIBS)

clean:
	@-rm -rf *.o $(EXE) include/* libs/*

run: all
	@./$(EXE)
