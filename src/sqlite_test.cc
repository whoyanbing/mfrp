#include "sqlite.h"
#include <iostream>

int main()
{
    Sqlite sq("mfrp.db");
    SqStmt st = sq.prepare("select * from user"); 
    while(st.step() == SQLITE_ROW)
    {
        int id = st.column_int(0);
        std::string name = st.column_txt(1);
        std::string password = st.column_txt(2);
        int balance = st.column_int(3);
                 
        std::cout << id << " | "
                  << name << " | "
                  << password << " | "
                  << balance 
                  << std::endl;
    }
    return 0;
}
