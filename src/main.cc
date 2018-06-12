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

    int user_choice;
    double money;
    std::string user_name;
    std::string user_pwd;
    std::string user_repwd;
    std::string user_name2;

        atm.menu1();
        std::cin >> user_choice;
        switch(user_choice){
            case 0:
                exit(0);
                break;
            case 1:
                system("reset");
                std::cout << "请设置用户名：";
                std::cin >>  user_name;
                std::cout << "请设置密码：";
                std::cin >> user_pwd;
                std::cout << "请确认密码：";
                std::cin >> user_repwd;
                if(user_pwd != user_repwd){
                    std::cout << "两次密码不一致，请重新输入！！！！" << std::endl;
                    exit(1);
                }
                atm.user_register(user_name,user_pwd);
                break;
            case 2:
                system("reset");
                std::cout << "请输入用户名：";
                std::cin >> user_name;
                std::cout << "请输入密码：";
                std::cin >> user_pwd;
                atm.user_login(user_name,user_pwd);
                break;
            default:
                break;
       }
    system("reset");
    atm.menu2();
    
    std::cin >>  user_choice;
    
    switch(user_choice){
        case 0:
            exit(0);
            break;
        case 1:
            system("reset");
            atm.money_query(user_name);
            break;
        case 2:
            system("reset");
            std::cout << "请输入您要存入的金额：" << std::endl;
            std::cin >> money;
            atm.money_save(user_name,money);
            break;
        case 3:
            system("reset");
            std::cout << "请输入您要取出的金额：" << std::endl;
            std::cin >> money;
            atm.money_draw(user_name,money);
            break;
        case 4:
            system("reset");
            std::cout << "请输入您要转账的用户名：" << std::endl;
            std::cin >> user_name2;
            std::cout << "请输入您要转账的金额：" << std::endl;
            std::cin >> money;
            atm.money_trans(user_name,user_name2,money);
        default:
            break;    
    } 
    return 0;
}
