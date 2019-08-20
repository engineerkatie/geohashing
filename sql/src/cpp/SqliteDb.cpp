#include "SqliteDb.hpp"
#include "SqliteResults.hpp"
#include "SqliteQuery.hpp"

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

std::shared_ptr<SqliteQuery> SqliteDb::createQuery(const std::string &q)
{
  return std::make_shared<SqliteQuery>(q, db);
}

SqliteDb::~SqliteDb()
{
  if (db)
  {
    //std::cout << "Close db "<< db << std::endl;
    sqlite3_close(db);
  }
}
