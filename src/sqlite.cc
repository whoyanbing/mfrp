#include <string>

SqStmt::SqStmt() = default;

void SqStmt::bind(const int& m, const int& n)
{
	sqlite3_bind_int(stmt_, m, n);
}

void SqStmt::bind(const int&m, const std::string& c, const int& n);
{
	sqlite3_bind_text(stmt_, m, c, n, void(*)(void*));
}

int SqStmt::step()
{
	return sqlite3_step(stmt_);
}

void SqStmt::column()
{

}

SqStmt::~SqStmt()
{
	sqlite3_finalize(stmt_);
}

Sqlite::Sqlite(const std::string& dbname)
{
	sqlite3_open(dbname, &db_);
}

SqStmt Sqlite::prepare(const std::string& sql)
{
	SqStmt stmt;
	sqlite3_prepare_v2(db_, sql, -1, &stmt.stmt_, NULL);
	return stmt;
}

void Sqlite::exec(const std::string& sql)
{
	sqlite3_exec(db_, sql, callback, 0, 0);
}

Sqlite::~Sqlite()
{
	sqlite3_close(db_);
}
