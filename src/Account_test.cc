#include "sqlite.h"
//#include "function.cc"
#include <iostream>

int main(int argc, char *argv[])
{
    //DB_PATH = argv[1];
    extern std::string DB_PATH;
    DB_PATH = "../mfrp.db";
//   Sqlite A("../mfrp.db");
    AccountDAO A;
  // std::cout << A.auth("Kevin" ) << std::endl;
     
//   A.insert("Kevin","abc");
    
  // A.deposit("Kevin",999);

   // A.balance("Tony");
 //  std::cout << A.withdraw("Kevin",800) << std::endl;
    
   A.transfer("Kevin","Tony",9.76);
 //  A.exec("insert into user(USERNAME,PASSWORD) values('Albert','ABABABA')");   
   // std::cout << A.balance("Toy") << std::endl;    
    std::cout << A.balance("Kevin")<< std::endl;
    return 0;

}/*
int main()
{
    std::cout << sha256("hjkdsa") << std::endl;
    return 0;
}*/
