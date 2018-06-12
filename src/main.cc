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

	std::string user_choice = "";
    double money = 0;
    std::string user_name = "";
    std::string user_pwd = "";
    std::string user_repwd = "";
    std::string user_name2 = "";

    while(user_choice != "q"){
		atm.menu1();
		std::cin >> user_choice;
        if(user_choice == "1"){
        	system("reset");
            std::cout << "请设置用户名：";
            std::cin >>  user_name;
            std::cout << "请设置密码：";
            std::cin >> user_pwd;
            std::cout << "请确认密码：";
            std::cin >> user_repwd;
            if(user_pwd != user_repwd){
            	std::cout << "两次密码不一致，请重新输入！！！！" << std::endl;
				do{
            		std::cout << "请重新设置密码：";
            		std::cin >> user_pwd;
            		std::cout << "请确认密码：";
            		std::cin >> user_repwd;
				}while(user_pwd != user_repwd);
            }
            if(user_pwd == user_repwd){	
            	atm.user_register(user_name,user_pwd);
			}
		}
        if(user_choice =="2"){
        	system("reset");
        	std::cout << "请输入用户名：";
            std::cin >> user_name;
            std::cout << "请输入密码：";
            std::cin >> user_pwd;
            atm.user_login(user_name,user_pwd);
        }
		break;
	}

	user_choice = "";
	while(user_choice != "q"){
    system("reset");
    atm.menu2();   
    std::cin >> user_choice;
    	if(user_choice == "1"){
    		system("reset");
        	atm.money_query(user_name);
		}
    	if(user_choice == "2"){
        	system("reset");
        	std::cout << "请输入您要存入的金额：" << std::endl;
        	std::cin >> money;
        	atm.money_save(user_name,money);
		}
    	if(user_choice == "3"){
        	system("reset");
        	std::cout << "请输入您要取出的金额：" << std::endl;
        	std::cin >> money;
        	atm.money_draw(user_name,money);
		}
    	if(user_choice == "4"){
        	system("reset");
        	std::cout << "请输入您要转账的用户名：" << std::endl;
        	std::cin >> user_name2;
        	std::cout << "请输入您要转账的金额：" << std::endl;
        	std::cin >> money;
        	atm.money_trans(user_name,user_name2,money);
    	}	
	}
    return 0;
}
