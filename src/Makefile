SHELL = /bin/sh

INCLUDES = -I../args/ -I../Catch2/include/ -I.
EXECUTABLE_NAME = apsp
TEST_EXECUTABLE_NAME = unit_test

SRC_DIR=.
TEST_DIR=./test/
BUILD_DIR=.

CXXFLAGS = -Wall -Wextra -Werror -std=c++11 -fmax-errors=2 -fopenmp
CXXFLAGS += $(INCLUDES)


SOURCES = Graph.cpp\
		  PriorityNode.cpp\
		  Timer.cpp\
		  parallel_apsp.cpp\
		  parallel_sssp.cpp\
		  serial_apsp.cpp\
		  serial_sssp.cpp

TEST_SOURCES = $(wildcard $(TEST_DIR)/*.cpp)
OBJECTS = $(SOURCES:%.cpp=$(BUILD_DIR)/%.o)
TEST_OBJECTS = $(TEST_SOURCES:%.cpp=$(BUILD_DIR)/%.o)

all: release

debug: CXXFLAGS+= -Og -g3 -DDEBUG
debug: build

release: CXXFLAGS+= -Ofast -s --lto
release: build

test: CXXFLAGS+= -Og
test: $(OBJECTS) $(TEST_OBJECTS)
	$(CXX) -o $(TEST_EXECUTABLE_NAME) $(OBJECTS) $(TEST_OBJECTS) $(CXXFLAGS)

build: $(OBJECTS) main.o
	$(CXX) -o $(EXECUTABLE_NAME) $(OBJECTS) main.o $(CXXFLAGS) 
clean:
	rm -f $(EXECUTABLE_NAME) $(TEST_EXECUTABLE_NAME) $(OBJECTS) $(TEST_OBJECTS) main.o
