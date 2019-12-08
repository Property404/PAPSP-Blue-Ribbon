SHELL = /bin/sh
INC_DIR = ../args/
EXECUTABLE_NAME = apsp_serial

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++11
CXXFLAGS += -I$(INC_DIR)
CXXFLAGS += -Ofast

OBJECTS = dijkstra.o

# Build recipe
all: release
debug: CXXFLAGS+= -Og -g3
debug: release
release: $(OBJECTS)
	$(CXX) -o $(EXECUTABLE_NAME) $(OBJECTS) $(CXXFLAGS)
clean:
	rm -f $(EXECUTABLE_NAME) $(OBJECTS)
