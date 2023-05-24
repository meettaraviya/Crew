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

INCLUDE := -I.
LIBPATH :=
LIBS :=
VARS := -DN=5 -DDBG

FLAGS := -Wall -std=c++20 -w
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
	
help:
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'