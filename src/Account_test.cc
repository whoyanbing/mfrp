#include "sqlite.h"
//#include "function.cc"
#include <iostream>

int main(int argc, char *argv[])
{
    //DB_PATH = argv[1];
    
//   Sqlite A("../mfrp.db");
    AccountDAO A;
 //   A.auth("Kevin" , "abc");
 
 //  A.insert("Tony","tony");
    
  A.deposit("Tony",15000);

 //  A.withdraw("Kevin",6000);
    
    A.transfer("Tony","Kevin",150);
 //  A.exec("insert into user(USERNAME,PASSWORD) values('Albert','ABABABA')");   
//    std::cout << A.balance("Tom") << std::endl;    
        
    return 0;

}/*
int main()
{
    std::cout << sha256("hjkdsa") << std::endl;
    return 0;
}*/
