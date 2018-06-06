#ifndef _SQLITE_H
#define _SQLITE_H

#include <sqlite3.h>

class SqStmt{
		friend class Sqlite;
public:
		SqStmt();
		void bind(const int& m, const int& n);
		void bind(const int& m, const std::string& c, const int& n);
		int step();
		void column();
		~SqStmt();
private:
		sqlite3_stmt* stmt_;
};

class Sqlite{
public:
		Sqlite(const std::string& dbname);
		SqStmt prepare(const std::string& sql);
		void exec(const std::string& sql);
		~Sqlite();
private:
		sqlite3* db_;
};

class AccountDAO{
public:
		void auth(const std::string& name,const std::string& pwd);
		void insert();
		bool deposit(const std::string& name,const int& sum);
		bool withdraw(const std::string& name,const int& sum);
		bool transfer(const std::string& name1,const std::string& name2,const int& sum);
		long balance(const std::string& name);
private:
		Sqlite sqlite_;
};
#endif
