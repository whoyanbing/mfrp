#!/bin/bash

all: bin/atm

bin/s.o: src/sqlite.cc src/sqlite.h
	g++ -o bin/s.o -c src/sqlite.cc

bin/A.o: src/ATM.cc src/ATM.h
	g++ -o bin/A.o -c src/ATM.cc

bin/m.o: src/main.cc src/sqlite.h
	g++ -o bin/m.o -c src/main.cc


bin/atm: bin/m.o bin/A.o bin/s.o
	g++ -o bin/atm bin/A.o bin/m.o bin/s.o -lsqlite3 -lcrypto

.PHONY: clean
clean:
	rm -f bin/A.o bin/m.o bin/s.o bin/atm

