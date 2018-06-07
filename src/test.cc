#include "sqlite.h"
#include <iostream>

int main()
{
	Sqlite sq("mfrp.db");
	SqStmt st = sq.prepare("select * from user");
	while(st.step() == SQLITE_ROW){
		int id = st.column_int(0);
		std::string name = st.column_txt(1);
		std::cout << id << "|"
				  << name << std::endl;
	}
	return 0;
}
