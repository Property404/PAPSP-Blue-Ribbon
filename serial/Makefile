SHELL = /bin/sh
INCLUDES = -I../args/ -I../common/
EXECUTABLE_NAME = apsp_serial

CXXFLAGS = -Wall -Wextra -Werror -std=c++11
CXXFLAGS += $(INCLUDES)

OBJECTS = dijkstra.o ../common/Graph.o

all: release

debug: CXXFLAGS+= -O0 -g3
debug: build

release: CXXFLAGS+= -Ofast -s --lto
release: build

build: $(OBJECTS)
	$(CXX) -o $(EXECUTABLE_NAME) $(OBJECTS) $(CXXFLAGS)

clean:
	rm -f $(EXECUTABLE_NAME) $(OBJECTS)
