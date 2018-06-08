
all: Sqlite

s.o: sqlite.cc sqlite.h
	g++ -o s.c -c sqlite.cc
st.o: sqlite_test.cc sqlite.h
	g++ -o st.c -c sqlite_test.cc
at.o: Account_test.cc sqlite.h
	g++ -o at.c -c Account_test.cc
f.o: function.cc sqlite.h
	g++ -o f.c -c function.cc
Sqlite: s.o st.o at.o f.o
	g++ -o Sqlite s.o st.o st.o f.o -lsqlite3
.PHONY: clean
clean:
	rm -f s.o st.o at.o f.o Sqlite

