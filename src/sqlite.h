#ifndef _SQLITE_H
#define _SQLITE_H

#include <string>
#include <sqlite3.h>

class SqStmt{
		friend class Sqlite;
public:
		void bind(int index, int val);
		void bind( int index, const std::string& val);
		int step();
		int column_int(int n);
        const char* column_txt(int n);
		~SqStmt();
private:
		sqlite3_stmt* stmt_;
};

class Sqlite{
public:
		Sqlite(const std::string& dbname);
		SqStmt prepare(const std::string& sql);
		//void exec(const std::string& sql);
		~Sqlite();
private:
		sqlite3* db_;
};

class AccountDAO{
public:
		void auth(const std::string& name,const std::string& pwd);
		void insert(const std::string& name,const std::string& pwd);
		void deposit(const std::string& name,int sum);
		void withdraw(const std::string& name, int sum);
		void transfer(const std::string& name1,const std::string& name2, int sum);
		long balance(const std::string& name);
private:
		Sqlite sqlite_{"../mfrp.db"};
};
#endif
