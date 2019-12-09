SHELL = /bin/sh

INCLUDES = -I../args/
EXECUTABLE_NAME = apsp

SRC_DIR=.
BUILD_DIR=.

CXXFLAGS = -Wall -Wextra -Werror -std=c++11 -fmax-errors=2
CXXFLAGS += $(INCLUDES)


SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:%.cpp=$(BUILD_DIR)/%.o)

all: release

debug: CXXFLAGS+= -O0 -g3
debug: build

release: CXXFLAGS+= -Ofast -s --lto
release: build

build: $(OBJECTS)
	$(CXX) -o $(EXECUTABLE_NAME) $(OBJECTS) $(CXXFLAGS)

clean:
	rm -f $(EXECUTABLE_NAME) $(OBJECTS)
