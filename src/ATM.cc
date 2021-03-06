#include "ATM.h"
#include <iostream>

void ATM::menu1()
{
    system("clear");
    std::cout << "欢迎来到钱多多银行！！！" << std::endl;
    std::cout << "请选择您需要办理的业务：" << std::endl;
    std::cout << "1: 开户" << std::endl;
    std::cout << "2：登录" << std::endl;
    std::cout << "q: 退出" << std::endl;
}

void ATM::menu2()
{
    system("clear");
    std::cout << "请选择您需要进行的操作！！！" << std::endl;
    std::cout << "1：查询余额" << std::endl;
    std::cout << "2: 存入金额" << std::endl;
    std::cout << "3：取出金额" << std::endl;
    std::cout << "4：转账汇款" << std::endl;
    std::cout << "q: 退出" << std::endl;
}

void ATM::user_register(const std::string& name,const std::string& pwd){

    if(name != "" && pwd != ""){

        try{

            User.auth(name);
            User.insert(name,pwd);
            std::cout << "恭喜您" << name << "，开户成功！！！" << std::endl;

        }catch(const std::runtime_error& e){

            std::cout << e.what() << std::endl;

        }

    }else{

        std::cout << "\n用户名或者密码不能为空！！！" << std::endl;

    }
}

void ATM::user_login(const std::string& name,const std::string& pwd)
{
    if(name != "" && pwd != ""){

        try{

            User.auth(name,pwd);

        }catch(const std::runtime_error& e){

            throw e;
        }

    }else{

        std::cout << "\n用户名或密码不能为空！！！！" << std::endl;

    }
}

void ATM::money_save(const std::string& name, double money)
{
    try{
        system("date");

        User.deposit(name,money);

        std::cout << name << ",您已经成功存入 " << money << " 元!!!" << std::endl;

        std::cout << "目前您的余额是 " << User.balance(name) << " 元!!!" << std::endl;

    }catch(const std::runtime_error& e){

        std::cout << e.what() << std::endl;

    }
}

void ATM::money_draw(const std::string& name, double money)
{
    try{
        system("date");

        User.withdraw(name,money);

        std::cout << name <<",您已经成功取出 " << money << " 元!!!" << std::endl;

        std::cout << "目前你的余额是 " << User.balance(name) << " 元!!!" << std::endl;

    }catch(const std::runtime_error& e){

        std::cout << e.what() << std::endl;
    }
}

void ATM::money_query(const std::string& name)
{
    try{
        system("date");
        
        std::cout << name << ",目前您的余额是："<< User.balance(name) << " 元!!!" << std::endl;

    }catch(const std::runtime_error& e){

        std::cout << e.what() << std::endl;
    }
}

void ATM::money_trans(const std::string& name1,const std::string& name2, double money)
{
    try{
        system("date");

        User.transfer(name1,name2,money);

        std::cout << name1 << ",您已经成功转给 " << name2 << " " << money << " 元!!!" << std::endl;

        std::cout << "目前你的余额是 " << User.balance(name1) << " 元!!!" << std::endl;

    }catch(const std::runtime_error& e){

        std::cout << e.what() << std::endl;

    }
}
