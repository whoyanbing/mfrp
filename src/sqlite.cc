#include "sqlite.h"
#include <iostream>

void SqStmt::bind(int index, int val)
{
	sqlite3_bind_int(stmt_, index, val);
}

void SqStmt::bind(int index, double val)
{
	sqlite3_bind_double(stmt_, index, val);
}

void SqStmt::bind(int index, const std::string& val)
{
	sqlite3_bind_text(stmt_, index, val.c_str(), -1, SQLITE_STATIC);
}

int SqStmt::step()
{
	return sqlite3_step(stmt_);
}

int SqStmt::column_int(int num)
{
	return sqlite3_column_int(stmt_, num);	
}

const char* SqStmt::column_txt(int num)
{
	return (const char*)sqlite3_column_text(stmt_, num);
}

SqStmt::~SqStmt()
{
	sqlite3_finalize(stmt_);
}

Sqlite::Sqlite(const std::string& dbname)
{
	sqlite3_open(dbname.c_str(), &db_);
}

SqStmt Sqlite::prepare(const std::string& sql)
{
	SqStmt stmt;
	sqlite3_prepare_v2(db_, sql.c_str(), -1, &stmt.stmt_, NULL);
	return stmt;
}

void Sqlite::exec(const std::string& sql)
{
	sqlite3_exec(db_, sql.c_str(), NULL, NULL, 0);
}

Sqlite::~Sqlite()
{
	sqlite3_close(db_);
}

void AccountDAO::auth(const std::string& name, const std::string& pwd)
{
	SqStmt st = sqlite_.prepare("select * from user where username=? and password=?");
	st.bind(1,name);
	st.bind(2,pwd);
	if(st.step() == SQLITE_ROW)
		std::cout << "login success" << std::endl;
	else
		std::cout << "error" << std::endl;
}
