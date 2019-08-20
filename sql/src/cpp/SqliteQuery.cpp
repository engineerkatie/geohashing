#include "SqliteDb.hpp"
#include "SqliteResults.hpp"
#include "SqliteQuery.hpp"

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

void SqliteQuery::nuke(void)
{
    if (q)
    {
      sqlite3_finalize(q);
      //std::cerr << "Finalize Query " << q << std::endl;
    }
}

SqliteQuery::SqliteQuery(const std::string &sql, sqlite3 *db)
{
  this -> db = db;
  auto r = sqlite3_prepare_v2(
                              this -> db,      /* Database handle */
                              sql.c_str(),       /* SQL statement, UTF-8 encoded */
                              -1,              /* Maximum length of zSql in bytes, -1 means null terminated */
                              &(this -> q),    /* OUT: Statement handle */
                              NULL             /* OUT: Pointer to unused portion of zSql */
                              );

  if (r != SQLITE_OK)
  {
    std::cerr << "Error: " << r << " - "<< sqlite3_errmsg(this -> db) << std::endl;
    nuke();
    return;
  }
}

std::shared_ptr<SqliteResults> SqliteQuery::run()
{
  auto r = std::make_shared<SqliteResults>(shared_from_this(), q);
  r -> next();
  return r;
}

std::string SqliteQuery::getLastErrorMessage(void) const
{
  return std::string(sqlite3_errmsg(db));
}
