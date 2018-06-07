#include "sqlite.h"
#include <iostream>

void SqStmt::bind(int index, int val)
{
	sqlite3_bind_int(stmt_, index, val);
}

void SqStmt::bind(int index, const std::string& val)
{
	sqlite3_bind_text(stmt_, index, val.c_str(), -1, SQLITE_STATIC);
}

int SqStmt::step()
{
	return sqlite3_step(stmt_);
}

int SqStmt::column_int(int n)
{
    return sqlite3_column_int(stmt_,n);
}

const char* SqStmt::column_txt(int n)
{
    return (const char*)sqlite3_column_text(stmt_,n);
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

/*void Sqlite::exec(const std::string& sql)
{
	sqlite3_exec(db_, sql.c_str(), -1);
}*/

Sqlite::~Sqlite()
{
	sqlite3_close(db_);
}

void AccountDAO::auth(const std::string& name,const std::string& pwd)
{
    SqStmt st = sqlite_.prepare("select * from user where USERNAME=? and PASSWORD=?");
    st.bind(1,name);
    st.bind(2,pwd);
    if(st.step() == SQLITE_ROW)
        std::cout << "login success" << std::endl;
    else
        std::cout << "error" << std::endl;
}

void AccountDAO::insert(const std::string& name,const std::string& pwd)
{
    SqStmt st = sqlite_.prepare("insert into user(USERNAME,PASSWORD) values(?,?)");
    st.bind(1,name);
    st.bind(2,pwd);
    if(st.step())
        std::cout << "insert success!" << std::endl;
    else
        std::cout << "insert error" << std::endl;
}

void AccountDAO::deposit(const std::string& name,int sum)
{
    SqStmt st = sqlite_.prepare("update user set BALANCE=BALANCE+? where USERNAME=?");
    st.bind(1,sum);
    st.bind(2,name);
    if(st.step())
        std::cout << "deposit success!" << std::endl;
    else
        std::cout << "deposit error" << std::endl;    
}

void AccountDAO::withdraw(const std::string& name,int sum)
{
    SqStmt st = sqlite_.prepare("update user set BALANCE=BALANCE-? where USERNAME=?");
    st.bind(1,sum);
    st.bind(2,name);
    if(st.step())
        std::cout << "withdraw success!" << std::endl;
    else
        std::cout << "withdraw error" << std::endl;    
}


void AccountDAO::transfer(const std::string& name1,const std::string& name2, int sum)
{
    SqStmt st1 = sqlite_.prepare("update user set BALANCE=BALANCE-? where USERNAME=?");
    st1.bind(1,sum);
    st1.bind(2,name1);
    SqStmt st2 = sqlite_.prepare("update user set BALANCE=BALANCE+? where USERNAME=?");
    st2.bind(1,sum);
    st2.bind(2,name2);
    if(st1.step() && st2.step())
        std::cout << "deposit success!" << std::endl;
    else
        std::cout << "deposit error" << std::endl;    
}
