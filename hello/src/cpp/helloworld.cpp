#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <memory>

#include "sql/src/cpp/SqliteDb.hpp"
#include "sql/src/cpp/SqliteQuery.hpp"
#include "sql/src/cpp/SqliteResults.hpp"

int main(int argc, char *argv[])
{
  auto db = std::make_shared<SqliteDb>("test.db");

  if (!db -> isOk())
  {
    std::cerr << db -> getStatus() << std::endl;
  }
  else
  {

    {
      std::string sql =
        "CREATE TABLE wibble"
        "  ( name TEXT"
        "  , wobble TEXT"
        ");";
      db -> createQuery(sql) -> run();
    }
    {
      std::string sql =
        "CREATE TABLE COMPANY("  \
      "ID INT PRIMARY KEY     NOT NULL," \
      "NAME           TEXT    NOT NULL," \
      "AGE            INT     NOT NULL," \
      "ADDRESS        CHAR(50)," \
      "SALARY         REAL );";
      db -> createQuery(sql) -> run();
    }
    {
      std::string sql = "INSERT INTO wibble(name, wobble) VALUES('a', 'aa');";
      db -> createQuery(sql) -> run();
    }
    {
      std::string sql = "INSERT INTO wibble(name, wobble) VALUES('b', 'bb');";
      db -> createQuery(sql) -> run();
    }
    {
      std::string sql = "INSERT INTO wibble(name, wobble) VALUES('c', 'aa');";
      db -> createQuery(sql) -> run();
    }
    {
      std::string sql = "SELECT name FROM wibble WHERE wobble = 'aa';";
      auto results = db -> createQuery(sql) -> run();

      do
      {
        std::cout << "data" << std::endl;
      } while(results -> next());
    }
  }
}
