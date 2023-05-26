# - inc/
#     - *.h
# - src/
#     - *.c
#     - *.cpp
# - obj/
#     - *.o
# - main

TARGET := main
SOURCES := $(wildcard src/*.c src/*.cpp)
OBJECTS := $(patsubst src%,obj%, $(patsubst %.c,%.o, $(patsubst %.cpp,%.o,$(SOURCES))))

INCLUDE := -I. -I/usr/local/include
LIBPATH :=
LIBS := -lfann
VARS := -DN=5

FLAGS := -Wall -std=c++20 -w -g
CCFLAGS := $(FLAGS) $(VARS)
CXXFLAGS := $(FLAGS) $(VARS)

CC := g++
CXX := g++

all: $(OBJECTS)
	$(CC) $(CCFLAGS) -o bin/$(TARGET) $(OBJECTS) $(LIBPATH) $(LIBS)

obj/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

.PHONY: clean help

clean:
	rm -rf obj/*
	rm -f bin/*
