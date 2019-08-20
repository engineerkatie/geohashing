#include "SqliteDb.hpp"
#include "SqliteResults.hpp"
#include "SqliteQuery.hpp"

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

SqliteResults::SqliteResults(std::shared_ptr<SqliteQuery> query, sqlite3_stmt *q)
{
  this -> query = query;
  this -> q = q;
  state = PREPARE;
}

void SqliteResults::nuke()
{
  query . reset();
  q = 0;
}

bool SqliteResults::next()
{
  int stepresult;

  if (state == EXEC_NO_RESULTS)
  {
    return false;
  }
  if (state == ERRORED)
  {
    return false;
  }
  if (state == EXEC_EOF)
  {
    return false;
  }

  stepresult = step();

  switch(stepresult)
  {
  case SQLITE_DONE:
    if (state == PREPARE)
    {
      state = EXEC_NO_RESULTS;
      return true;
    }
    state = EXEC_EOF;
    return false;
  case SQLITE_ROW:
    state = EXEC_DATA;
    return true;
    break;
  case SQLITE_BUSY:
  case SQLITE_ERROR:
  case SQLITE_MISUSE:
  default:
    state = ERRORED;
    std::cerr << "Error: " << stepresult << " - "<< this -> query -> getLastErrorMessage() << std::endl;
    return false;
  }
}
