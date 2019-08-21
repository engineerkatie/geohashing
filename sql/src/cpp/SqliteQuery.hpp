#pragma once

#include <string>
#include "src/sqlite3.h"
#include <memory>

class SqliteResults;

class SqliteQuery:public std::enable_shared_from_this<SqliteQuery>
{
public:

  std::shared_ptr<SqliteResults> run();

  std::string getLastErrorMessage(void) const;

  ~SqliteQuery()
  {
    nuke();
  }

  void nuke(void);

  SqliteQuery *bind(std::size_t index, const void *data, std::size_t size);
  SqliteQuery *bind(std::size_t index, const std::string &v);

  SqliteQuery(const std::string &q, sqlite3 *db);
protected:
private:
  sqlite3 *db;
  sqlite3_stmt *q;
};
