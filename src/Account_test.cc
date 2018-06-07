#include "sqlite.h"
#include <iostream>

int main()
{
    
    AccountDAO A;
 //   A.auth("Jack" , "hjka123");
    
 //   A.insert("Jessie","abcabc");
    
//    A.deposit("Jessie",500);

  //  A.withdraw("Tom",512);
    
    A.transfer("Jessie","Tom",500);
    
    return 0;

}
