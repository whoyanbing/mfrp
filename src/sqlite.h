#ifndef _SQLITE_H
#define _SQLITE_H

#include <string>
#include <sqlite3.h>
<<<<<<< HEAD
#include <openssl/md5.h>
=======
#include <string>

extern std::string DB_PATH;
>>>>>>> e69753ce7b3dbb6255efedcc917a50ad053876ce

class SqStmt{
		friend class Sqlite;
public:
		void bind(int index, int val);
<<<<<<< HEAD
		void bind( int index, const std::string& val);
		void bind(int index, double val);
		int step();
		int column_int(int n);
        const char* column_txt(int n);
=======
		void bind(int index, double val);
		void bind(int index, const std::string& val);
		int step();
		int column_int(int num);
		const char* column_txt(int num);
>>>>>>> e69753ce7b3dbb6255efedcc917a50ad053876ce
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
<<<<<<< HEAD
        bool isset_user(const std::string& name);
		void auth(const std::string& name,const std::string& pwd);
		void insert(const std::string& name,const std::string& pwd);
		void deposit(const std::string& name,double sum);
		void withdraw(const std::string& name, double sum);
		void transfer(const std::string& name1,const std::string& name2, double sum);
		long balance(const std::string& name);
private:
		Sqlite sqlite_{"../mfrp.db"};
=======
		void auth(const std::string& name, const std::string& pwd);
		/*void insert(const std::string& name, const std::string& pwd);
		bool deposit(const std::string& name, int sum);
		bool withdraw(const std::string& name, int sum);
		bool transfer(const std::string& name1,const std::string& name2, int sum);
		long balance(const std::string& name);*/
private:
		Sqlite sqlite_(std::string DB_PATH);
>>>>>>> e69753ce7b3dbb6255efedcc917a50ad053876ce
};
#endif
