SHELL = /bin/sh

INCLUDES = -I../args/ -I../Catch2/include/ -I.
EXECUTABLE_NAME = apsp
TEST_EXECUTABLE_NAME = unit_test

SRC_DIR=.
TEST_DIR=./test/
BUILD_DIR=.

CXXFLAGS = -Wall -Wextra -Werror -std=c++11 -fmax-errors=2 -fopenmp
CXXFLAGS += $(INCLUDES)


SOURCES = Graph.o\
		  PriorityNode.o\
		  Timer.o\
		  parallel_apsp.o\
		  parallel_sssp.o\
		  serial_apsp.o\
		  serial_sssp.o

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

build: OBJECTS+= main.o
build: $(OBJECTS)
	$(CXX) -o $(EXECUTABLE_NAME) $(OBJECTS) $(CXXFLAGS)

clean:
	rm -f $(EXECUTABLE_NAME) $(TEST_EXECUTABLE_NAME) $(OBJECTS) $(TEST_OBJECTS)
