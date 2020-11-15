PWD = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

OBJS = main.cpp src/*.cpp src/constructor/*.cpp src/parser/*.cpp src/statement/*.cpp src/value/*.cpp

CC = g++

INCLUDE_PATHS = -Iinclude

COMPILER_FLAGS = -g

OBJ_NAME = jpl

all: $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(COMPILER_FLAGS) -o $(OBJ_NAME)


install:
	ln -s $(PWD)jpl /usr/local/bin/jpl

clean-linux:
	rm -f jpl

clean-windows:
	del jpl.exe
