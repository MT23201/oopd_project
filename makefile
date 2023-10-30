CXX=g++

CXXFLAGS = -std=c++17 -Wall

SRC= part1.cpp

DEBUG_BINARY = debug_exe

RELEASE_BINARY = optimized_exe

all: debug release

debug: $(SRC)

	$(CXX) $(CXXFLAGS) -g $(SRC) -o $(DEBUG_BINARY)

release: $(SRC)

	$(CXX) $(CXXFLAGS) -O2 $(SRC) -o $(RELEASE_BINARY)