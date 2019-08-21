#include "BigTableLike.hpp"

//std::ostream& operator<<(std::ostream& os, const BigTableLike &output) {}

//void swap(BigTableLike& v1, BigTableLike& v2) {
//    v1.swap(v2);
//}


BigTableLike::BigTableLike(std::shared_ptr<SqliteDb> db, const std::string &tname)
  : db(db)
  , tname(tname)
{
  std::string sql =
        "CREATE TABLE " + tname +
        "  ( name BLOB PRIMARY KEY"
        "  , data TEXT"
        ");";
  db -> createQuery(sql) -> run();
}

BigTableLike::~BigTableLike()
{
}

void BigTableLike::insert(const BytesKey &key, const std::string &data)
{
  std::string sql = "INSERT INTO " + tname + "(name, data) VALUES(?,?);";
  db -> createQuery(sql) -> bind(1, key.data(), key.size()) ->  bind(2, data) -> run();
}

void BigTableLike::iterate(const BytesKey &key, ITER func)
{
  std::string sql =
    "SELECT name, data "
    " FROM " + tname +
    " WHERE name >= ?"
    " ORDER BY name"
    ";";
  auto results = db -> createQuery(sql)
    -> bind(1, key.data(), key.size())
    -> run();
  do
  {
    auto key_data = results -> getBytes(0);
    auto key = BytesKey(key_data.first, key_data.second);
    auto data = results -> getString(1);

    if (!func(key, data))
    {
      break;
    }

  } while(results -> next());
}

void BigTableLike::iterate(const BytesKey &key, ITER func, const BytesKey &limit)
{
  std::string sql =
    "SELECT name, data "
    " FROM " + tname +
    " WHERE name >= ?"
    " ORDER BY name"
    ";";
  auto results = db -> createQuery(sql)
    -> bind(1, key.data(), key.size())
    -> run();
  do
  {
    auto key_data = results -> getBytes(0);
    auto key = BytesKey(key_data.first, key_data.second);
    auto data = results -> getString(1);

    if (key >= limit)
    {
      break;
    }

    if (!func(key, data))
    {
      break;
    }

  } while(results -> next());
}
