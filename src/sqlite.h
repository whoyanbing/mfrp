#ifndef _SQLITE_H
#define _SQLITE_H

#include <string>
#include <sqlite3.h>
#include <openssl/md5.h>
#include <string>

class SqStmt{
		friend class Sqlite;
public:
		void bind(int index, int val);
		void bind( int index, const std::string& val);
		void bind(int index, double val);
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
		int exec(const std::string& sql);
		~Sqlite();
private:
		sqlite3* db_;
};

class AccountDAO{
public:
        bool isset_user(const std::string& name);
		void auth(const std::string& name,const std::string& pwd);
		void insert(const std::string& name,const std::string& pwd);
		void deposit(const std::string& name,double sum);
		void withdraw(const std::string& name, double sum);
		void transfer(const std::string& name1,const std::string& name2, double sum);
		long balance(const std::string& name);
private:
		Sqlite sqlite_{"../mfrp.db"};
};
#endif
