#!/bin/bash

all: bin/atm

bin/f.o: src/function.cc src/function.h
	g++ -o bin/f.o -c src/function.cc

bin/s.o: src/sqlite.cc src/sqlite.h
	g++ -o bin/s.o -c src/sqlite.cc

bin/A.o: src/ATM.cc src/ATM.h
	g++ -o bin/A.o -c src/ATM.cc

bin/m.o: src/main.cc src/sqlite.h
	g++ -o bin/m.o -c src/main.cc

bin/atm: bin/f.o bin/m.o bin/A.o bin/s.o
	g++ -o bin/atm bin/f.o bin/s.o bin/A.o bin/m.o -lsqlite3 -lcrypto

.PHONY: clean
clean:
	rm -f bin/*.o bin/atm

