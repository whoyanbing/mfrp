#ifndef _ATM_H
#define _ATM_H

#include <string>
#include "sqlite.h"

class ATM{
public:
    void menu1();
    void menu2();
    void user_register(const std::string& name, const std::string& pwd);
    void user_login(const std::string& name, const std::string& pwd);
    void money_save(const std::string& name, double money);
    void money_draw(const std::string& name, double money);
    void money_query(const std::string& name);
    void money_trans(const std::string& name1, const std::string& name2,double money);

private:
    AccountDAO User;
};
#endif
