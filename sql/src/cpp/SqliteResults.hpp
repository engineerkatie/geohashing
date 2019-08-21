#pragma once

#include <string>
#include "src/sqlite3.h"
#include <memory>
#include <utility>

class SqliteQuery;

class SqliteResults
{
public:
  SqliteResults(std::shared_ptr<SqliteQuery> query, sqlite3_stmt *q);


  std::string summarise() const
  {
    switch(state)
    {
      case PREPARE:
        return "prep";
      case   EXEC_NO_RESULTS:
        return "no res";
      case   EXEC_DATA:
        return "data";
      case   EXEC_EOF:
        return "eof";
      case   ERRORED:
        return "err";
    }
  }

  void nuke(void);
  bool next(void);

  std::pair<const void*, std::size_t> getBytes(int col);
  std::string getString(int col);

  ~SqliteResults()
  {
    nuke();
  }
private:
  friend class SqliteQuery;
  std::shared_ptr<SqliteQuery> query;
  sqlite3_stmt *q;

  enum {
    PREPARE,
    EXEC_NO_RESULTS,
    EXEC_DATA,
    EXEC_EOF,
    ERRORED,
  } state;

  int step()
  {
    return sqlite3_step(q);
  }
};
