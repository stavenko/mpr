CC=c++
CFLAGS=-std=c++11 -Wall -Wc++11-extensions -I./src/include
LDFLAGS=
SOURCES=main.cpp src/context_functions.cpp src/uniform_functions.cpp
EXECUTABLE=example
OBJECTS=$(SOURCES:.cpp=.o)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

