#include "sqlite.h"
#include "ATM.h"
#include <iostream>

int main(int argc, char *argv[])
{
    if(argc !=2 ){

        exit(1);

    }

    extern std::string DB_PATH;

    DB_PATH = argv[1];

    ATM atm;

    std::string money;

    std::string user_choice;

    std::string user_name;

    std::string user_pwd;

    std::string user_repwd;

    std::string user_name2;

    while(true){

    atm.menu1();

    getline(std::cin,user_choice);

    if(user_choice == "1"){

        system("clear");

        std::cout << "请设置用户名：";
        std::getline(std::cin,user_name);
        std::cout << "请设置密码：";
        system("stty -echo");
        std::getline(std::cin,user_pwd);
        std::cout <<"\n请确认密码：";
        getline(std::cin,user_repwd);
        system("stty echo");

        if(user_pwd == user_repwd){

            atm.user_register(user_name,user_pwd);
            std::cout << "\n开户成功！！" << std::endl;

        }
        else{

            std::cout << "\n两次密码不一致！";
            std::cout << "\n请重新设置密码：";
            system("stty -echo");
            std::getline(std::cin,user_pwd);
            std::cout << "\n请确认密码：";
            std::getline(std::cin,user_repwd);
            system("stty echo");
            atm.user_register(user_name,user_pwd);
            std::cout << "\n开户成功！！" << std::endl;

        }
    }

    if(user_choice == "2"){

        system("clear");

        std::cout << "请输入用户名：";
        std::getline(std::cin, user_name);
        system("stty -echo");
        std::cout << "请输入密码：";
        std::getline(std::cin, user_pwd);
        system("stty echo");
        
        try{

            atm.user_login(user_name,user_pwd);

            user_choice = "";
            while (true) {
                atm.menu2();
                getline(std::cin ,user_choice);

            if(user_choice == "1"){
                system("clear");
                atm.money_query(user_name);
            }

            if(user_choice == "2"){
                system("clear");
                std::cout << "请输入您要存入的金额：" << std::endl;
                std::getline(std::cin,money);
                try{
                    atm.money_save(user_name, stod(money));
                }
                catch(const std::invalid_argument& e){
                    std::cout << "money input error"  << std::endl;
                }
            }

            if(user_choice == "3"){
                system("clear");
                std::cout << "请输入您要取出的金额：" << std::endl;
                std::getline(std::cin ,money);
                try{
                    atm.money_draw(user_name, stod(money));
                }
                catch(const std::invalid_argument& e){
                    std::cout << "money inpout error" << std::endl;
                }
            }

            if(user_choice == "4"){
                system("clear");
                std::cout << "请输入您要转账的用户名：" << std::endl;
                std::getline(std::cin,user_name2);
                std::cout << "请输入您要转账的金额：" << std::endl;
                std::getline(std::cin,money);
                try{
                    atm.money_trans(user_name,user_name2, stod(money));
                }
                catch(const std::invalid_argument& e){
                    std::cout << "money input error" << std::endl;
                }   
            }

            if(user_choice == "q"){
                break;
            }

            std::cout << "press any key to continue...." << std::endl;
            std::getline(std::cin,user_choice);
        }

        }
        catch(const std::runtime_error& e){
            std::cout << "\n" << e.what() << std::endl;
        }
    }

    if(user_choice == "q"){
        exit(0);
    }

        std::cout << "\npress any key to continue...." << std::endl;
        std::getline(std::cin,user_choice);

    }

    return 0;

}
