CC=c++
CFLAGS=-std=c++11 -Wall -Wc++11-extensions -I./src/include -I/usr/local/include
LDFLAGS=-L/usr/local/lib -lgtest 
SOURCES=main.cpp src/context_functions.cpp src/uniform_functions.cpp
TESTSOURCES=tests/test.cpp tests/material.cpp
EXECUTABLE=example
TESTEXECUTABLE=example-test
OBJECTS=$(SOURCES:.cpp=.o)
TESTOBJECTS=$(TESTSOURCES:.cpp=.o)

all: $(SOURCES) $(EXECUTABLE)

test: $(TESTSOURCES) $(TESTEXECUTABLE)

$(TESTEXECUTABLE):$(TESTOBJECTS)
	$(CC) $(LDFLAGS) $(TESTOBJECTS) -o $@

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

