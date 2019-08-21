#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <memory>

#include "sql/src/cpp/SqliteDb.hpp"
#include "sql/src/cpp/SqliteQuery.hpp"
#include "sql/src/cpp/SqliteResults.hpp"

#include "geohash/src/cpp/BigTableLike.hpp"

int main(int argc, char *argv[])
{
  auto db = std::make_shared<SqliteDb>("test.db");

  if (!db -> isOk())
  {
    std::cerr << db -> getStatus() << std::endl;
  }
  else
  {

    /*    {
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
    */
    BigTableLike bt(db, "geo");
    bt.insert(BytesKey("6162636469"), "r1");
    bt.insert(BytesKey("6162636465"), "r2");

    bt.insert(BytesKey("6162636466"), "r3");
    bt.insert(BytesKey("6162636467"), "r4");
    bt.insert(BytesKey("6162636468"), "r5");

    BytesKey limit("6162636467");

    bt.iterate(BytesKey("61626364"), [limit](const BytesKey &key, const std::string &data){

        if (key >= limit) {
          return false;
        }
        std::cout << "data:" << data << std::endl;
        return true;
      });
  }
}
