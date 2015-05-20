PWD := $(shell pwd)
JHOME := $(shell echo $(JAVA_HOME))
includedir=$(PWD)/include
srcdir=$(PWD)/src
libsdir=$(PWD)/libs
CC=g++
CFLAGS=-I$(includedir) -I$(JHOME)/include -I$(JHOME)/include/linux \
	   -L$(srcdir) -g -pthread -fPIC -c -Wall -std=c++11
LDFLAGS=-L$(libsdir) -g -fPIC
LDLIBS=-pthread -lcgmgr
OBJECTS=$(SOURCES:.cpp=.o)
SOURCES=libcgmgrj.cpp
jnilib=libcgmgrj.so
jar=LibCgmgrJ.jar
jarsrc=LibCgmgrJ.java
javatest=CgmgrJ.java
jcp=.:$(PWD)/libs

.PHONY:
all: jni jar

%.o: $(srcdir)/%.cpp
	$(CC) $(CFLAGS) $< -o $@

jnigen: jar
	javah -jni LibCgmgrJ
	mv LibCgmgrJ.h include

jni: $(OBJECTS)
	$(CC) $(LDFLAGS) -shared $(OBJECTS) -o $(jnilib) $(LDLIBS)
	mv $(jnilib) libs

jar: $(jarsrc)
	javac -cp $(jcp) $(jarsrc)
	jar cf $(jar) LibCgmgrJ.class
	mv $(jar) libs

test: $(javatest)
	javac -cp $(jcp) $(javatest)

run: test 
	java -cp $(jcp) -Djava.library.path=.:$(PWD)/libs CgmgrJ

clean:
	@-rm -rf *.o *.class libs/*.so
