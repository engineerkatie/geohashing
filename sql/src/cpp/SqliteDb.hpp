#pragma once

#include <string>
#include "src/sqlite3.h"
#include <memory>

class SqliteQuery;

class SqliteDb
{
public:
  std::shared_ptr<SqliteQuery> createQuery(const std::string &q);

  SqliteDb(const std::string &name)
  {
    db = 0;
    auto rc = sqlite3_open("test.db", &db);
    if (rc)
    {
      status = sqlite3_errmsg(db);
      sqlite3_close(db);
      db = 0;
    }
  }

  virtual ~SqliteDb();

  bool isOk() const
  {
    return db != 0;
  }

  const std::string &getStatus() const { return status; }

protected:
  sqlite3 *db;
  std::string status;

};
