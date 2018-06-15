#include "sqlite.h"
#include <iostream>
#include "function.h"
#include <stdexcept>

void SqStmt::bind(int index, int val)
{
	if(sqlite3_bind_int(stmt_, index, val) != SQLITE_OK)
        throw std::runtime_error("bind int error");
}

void SqStmt::bind(int index, const std::string& val)
{
	if(sqlite3_bind_text(stmt_, index, val.c_str(), -1, SQLITE_STATIC) != SQLITE_OK)
        throw std::runtime_error("bind string error");
}

void SqStmt::bind(int index, double val)
{
	if(sqlite3_bind_double(stmt_, index, val) != SQLITE_OK)
        throw std::runtime_error("bind double error");
}

int SqStmt::step()
{
	int res = sqlite3_step(stmt_);

    if(res != SQLITE_DONE && res != SQLITE_ROW){
        throw std::runtime_error("step error");
    }
    else{
        return res;
    }
}

void SqStmt::column(int n, int& val)
{
    val = sqlite3_column_int(stmt_,n);
}

void SqStmt::column(int n, double& val)
{
    val = sqlite3_column_double(stmt_,n);
}

void SqStmt::column(int n, std::string& val)
{
    val = (const char*)sqlite3_column_text(stmt_,n);
}

SqStmt::~SqStmt()
{
	sqlite3_finalize(stmt_);
}

std::string DB_PATH;

Sqlite::Sqlite()
{
	int res = sqlite3_open(DB_PATH.c_str(), &db_);

	if(res != SQLITE_OK)
        throw std::runtime_error("db open error");
}

SqStmt Sqlite::prepare(const std::string& sql)
{
    SqStmt stmt;

	if(sqlite3_prepare_v2(db_, sql.c_str(), -1, &stmt.stmt_, NULL) != SQLITE_OK){
        throw std::runtime_error("prepare error"); 
    }
    else{
	    return stmt;
    }
}

int Sqlite::changes()
{
    return sqlite3_changes(db_);
}

int Sqlite::exec(const std::string& sql)
{
	return sqlite3_exec(db_, sql.c_str(), NULL,NULL,0);
}

Sqlite::~Sqlite()
{
	sqlite3_close(db_);
}


void AccountDAO::auth(const std::string& name,const std::string& pwd)
{
    SqStmt st = sqlite_.prepare("select * from user where USERNAME=? and PASSWORD=?");
    st.bind(1,name);
    std::string tmp = sha256(pwd);
    st.bind(2,tmp);
    if(st.step() != SQLITE_ROW){    
        throw std::runtime_error("用户名或密码错误，登陆失败！！！");
    }
}

void AccountDAO::auth(const std::string& name)
{
    SqStmt st = sqlite_.prepare("select * from user where USERNAME=?");
    st.bind(1,name);
    if(st.step() == SQLITE_ROW){    
        throw std::runtime_error("\n用户已存在！！！");
    }
}

void AccountDAO::log(const std::string&name, const std::string& ope, double sum)
{
     SqStmt st = sqlite_.prepare("insert into log(USERNAME,OPERATOR,MONEY) values(?,?,?)");
     st.bind(1,name);
     st.bind(2,ope);
     st.bind(3,sum);
     st.step();
     if(sqlite_.changes() == 0){
        throw std::runtime_error("log error");
     }
}

void AccountDAO::insert(const std::string& name,const std::string& pwd)
{
     SqStmt st = sqlite_.prepare("insert into user(USERNAME,PASSWORD) values(?,?)");
     st.bind(1,name);
     std::string tmp = sha256(pwd);
     st.bind(2,tmp);
     st.step();
     if(sqlite_.changes() == 0){
         throw std::runtime_error("开户失败！！！");
     }
}

void AccountDAO::deposit(const std::string& name,double sum)
{
    if(sum < 0){
        throw std::runtime_error("存款失败！！！"); 
    }
    try{
        sqlite_.exec("begin");
        SqStmt st = sqlite_.prepare("update user set BALANCE=BALANCE+? where USERNAME=?");
        st.bind(1,sum);
        st.bind(2,name);
        st.step();
        if(sqlite_.changes() == 0){
            throw std::runtime_error("存款失败！！！");
        }
        log(name,"deposit",sum);
        sqlite_.exec("commit");
    }
    catch(const std::runtime_error& e){    
        sqlite_.exec("rollback");
        throw std::runtime_error("存款失败！！！");
    }
}

void AccountDAO::deposit_(const std::string& name,double sum)
{
    if(sum < 0){
        throw std::runtime_error("存款失败！！！"); 
    }
    try{
        SqStmt st = sqlite_.prepare("update user set BALANCE=BALANCE+? where USERNAME=?");
        st.bind(1,sum);
        st.bind(2,name);
        st.step();
        if(sqlite_.changes() == 0){
            throw std::runtime_error("存款失败！！！");
        }
        log(name,"deposit",sum);
    }
    catch(const std::runtime_error& e){    
        throw std::runtime_error("存款失败！！！");
    }
}

void AccountDAO::withdraw(const std::string& name,double sum)
{
    if(sum < 0){
        throw std::runtime_error("取款失败！！！"); 
    }
    try{
        sqlite_.exec("begin");
        SqStmt st = sqlite_.prepare("update user set BALANCE=BALANCE-? where USERNAME=? and BALANCE>=?");
        st.bind(1,sum);
        st.bind(2,name);
        st.bind(3,sum);
        st.step();
        if(sqlite_.changes() == 0){
            throw std::runtime_error("取款失败！！！");
        }
        log(name,"withdraw",sum);
        sqlite_.exec("commit");
    }
    catch(const std::runtime_error& e){
        sqlite_.exec("rollback");
        throw std::runtime_error("取款失败！！！");
    }
}

void AccountDAO::withdraw_(const std::string& name,double sum)
{
    if(sum < 0){
        throw std::runtime_error("取款失败！！！"); 
    }
    try{
        SqStmt st = sqlite_.prepare("update user set BALANCE=BALANCE-? where USERNAME=? and BALANCE>=?");
        st.bind(1,sum);
        st.bind(2,name);
        st.bind(3,sum);
        st.step();
        if(sqlite_.changes() == 0){
            throw std::runtime_error("取款失败！！！");
        }
        log(name,"withdraw",sum);
    }
    catch(const std::runtime_error& e){
        throw std::runtime_error("取款失败！！！");
    }
}

void AccountDAO::transfer(const std::string& name1,const std::string& name2, double sum)
{
    try{
        sqlite_.exec("begin");
        withdraw_(name1,sum);
        deposit_(name2,sum);
        sqlite_.exec("commit");
    }
    catch(const std::runtime_error& e){
        sqlite_.exec("rollback");
        throw std::runtime_error("转账失败！！！");
    }
}

double AccountDAO::balance(const std::string& name)
{
    SqStmt st = sqlite_.prepare("select * from user where USERNAME=?");
    st.bind(1,name);
    if(st.step() != SQLITE_ROW){
        throw std::runtime_error("余额查询失败！！！");
    }
    double res = 0;
    st.column(3,res);
    return res;    
}
