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
        void column(int n, int& val);
        void column(int n, double& val);
        void column(int n, std::string& val);
		~SqStmt();
private:
		sqlite3_stmt* stmt_ = nullptr;
};

class Sqlite{
public:
		Sqlite();
		SqStmt prepare(const std::string& sql);
		int exec(const std::string& sql);
        int changes();
		~Sqlite();
private:
		sqlite3* db_;
};

class AccountDAO{
public:
		void auth(const std::string& name,const std::string& pwd);
		void auth(const std::string& name);
        void log(const std::string&name,const std::string& ope, double sum);
		void insert(const std::string& name,const std::string& pwd);
		void deposit(const std::string& name,double sum);
		void deposit_(const std::string& name,double sum);
		void withdraw(const std::string& name, double sum);
		void withdraw_(const std::string& name, double sum);
		void transfer(const std::string& name1,const std::string& name2, double sum);
		double balance(const std::string& name);
private:
		Sqlite sqlite_;
};
#endif
