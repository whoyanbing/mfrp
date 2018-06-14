atm: src/main.cc src/ATM.cc src/sqlite.cc
	g++ src/main.cc src/ATM.cc src/sqlite.cc -lsqlite3 -lcrypto -o bin/atm

.PHONY: clean
clean:
	rm *.o 

