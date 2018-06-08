#include "sqlite.h"
#include <iostream>
#include "function.cc"

void SqStmt::bind(int index, int val)
{
	sqlite3_bind_int(stmt_, index, val);
}

void SqStmt::bind(int index, const std::string& val)
{
    std::cout << val.c_str() <<  std::endl;
	std::cout << sqlite3_bind_text(stmt_, index, val.c_str(), -1, SQLITE_STATIC) << std::endl;
}

void SqStmt::bind(int index, double val)
{
	sqlite3_bind_double(stmt_, index, val);
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

int Sqlite::exec(const std::string& sql)
{
	return sqlite3_exec(db_, sql.c_str(), NULL,NULL,0);
}

Sqlite::~Sqlite()
{
	sqlite3_close(db_);
}

bool AccountDAO::isset_user(const std::string& name)
{
    SqStmt st = sqlite_.prepare("select * from user where USERNAME=?");
    st.bind(1,name);
    if(st.step() == SQLITE_ROW)
        return true;
    else
        return false;
}

void AccountDAO::auth(const std::string& name,const std::string& pwd)
{
    SqStmt st = sqlite_.prepare("select * from user where USERNAME=? and PASSWORD=?");
    st.bind(1,name);
    std::string tmp = sha256(pwd);
    st.bind(2,tmp);
    if(st.step() == SQLITE_ROW)
        std::cout << "login success" << std::endl;
    else
        std::cout << "error" << std::endl;
}

void AccountDAO::insert(const std::string& name,const std::string& pwd)
{
    SqStmt st = sqlite_.prepare("insert into user(USERNAME,PASSWORD) values(?,?)");
    st.bind(1,name);
    std::string tmp = sha256(pwd);
    st.bind(2,tmp);
    if(st.step())
        std::cout << "insert success" << std::endl;
    else
        std::cout << "error" << std::endl;
}

void AccountDAO::deposit(const std::string& name,double sum)
{
    SqStmt st = sqlite_.prepare("update user set BALANCE=BALANCE+? where USERNAME=?");
    st.bind(1,sum);
    st.bind(2,name);
    if(isset_user(name)){
        st.step();
        SqStmt st2 = sqlite_.prepare("insert into log(USERNAME,OPERATOR,MONEY) values(?,?,?)");
        st2.bind(1,name);
        st2.bind(2,"deposit");
        st2.bind(3,sum);
        st2.step();
        std::cout << "deposit success!" << std::endl;
    }else{
        std::cout << "deposit error" << std::endl;
    }
}

void AccountDAO::withdraw(const std::string& name,double sum)
{
    SqStmt st = sqlite_.prepare("update user set BALANCE=BALANCE-? where USERNAME=? and BALANCE>?");
    st.bind(1,sum);
    st.bind(2,name);
    st.bind(3,sum);
    if(st.step()){
        SqStmt st2 = sqlite_.prepare("insert into log(USERNAME,OPERATOR,MONEY) values(?,?,?)");
        st2.bind(1,name);
        st2.bind(2,"withdraw");
        st2.bind(3,sum);
        st2.step();
        std::cout << "withdraw success!" << std::endl;
    }
    else{
        std::cout << "withdraw error" << std::endl;
    }
}


void AccountDAO::transfer(const std::string& name1,const std::string& name2, double sum)
{
    int ret =  sqlite_.exec("begin");
    SqStmt st1 = sqlite_.prepare("update user set BALANCE=BALANCE-? where USERNAME=? and BALANCE>?");
    st1.bind(1,sum);
    st1.bind(2,name1);
    st1.bind(3,sum);
    ret = st1.step();
    if(ret != SQLITE_DONE){
        ret = sqlite_.exec("rollback");
    }
    SqStmt st2 = sqlite_.prepare("update user set BALANCE=BALANCE+? where USERNAME=?");
    st2.bind(1,sum);
    st2.bind(2,name2);

    if(isset_user(name2)){
        ret = st2.step();
        if(ret != SQLITE_DONE){
            ret = sqlite_.exec("rollback");
        }
        SqStmt st3 = sqlite_.prepare("insert into log(USERNAME,OPERATOR,MONEY) values(?,?,?)");
        st3.bind(1,name1);
        st3.bind(2,"transfer->" + name2);
        st3.bind(3,sum);
        st3.step();
        ret = sqlite_.exec("commit");
        std::cout << "transfer success" << std::endl;
    }else{
        ret = sqlite_.exec("rollback");
        std::cout << "error" << std::endl;
    }
}

long AccountDAO::balance(const std::string& name)
{
    SqStmt st = sqlite_.prepare("select * from user where USERNAME=?");
    st.bind(1,name);
    if(st.step() == SQLITE_ROW){
        return st.column_int(3);
    }
}
