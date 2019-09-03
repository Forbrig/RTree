.PHONY: all build test clean

CXXFLAGS = -Wall -Wextra -Wpedantic -std=c++11

all: build

build: out test/out/test

out:
	mkdir -p test/out

test/out/test: test/test.cpp RTree.h
	$(CXX) -o $@ ${CXXFLAGS} $<

test: build
	./test/out/test test/data/3d.txt

clean:
	rm -rf test/out