#!/bin/bash
all: Sqlite

s.o: sqlite.cc sqlite.h
	g++ -o s.o -c sqlite.cc
at.o: Account_test.cc sqlite.h
	g++ -o at.o -c Account_test.cc
Sqlite: s.o at.o 
	g++ -o Sqlite s.o at.o -lsqlite3

.PHONY: clean
clean:
	rm -f s.o at.o Sqlite

