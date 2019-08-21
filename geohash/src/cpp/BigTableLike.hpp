#pragma once

// Delete bits as needed

//#include <algorithm>
//#include <utility>
//#include <iostream>

#include "BytesKey.hpp"
#include <cstdint>
#include <cstddef>
#include <functional>
#include "sql/src/cpp/SqliteDb.hpp"
#include "sql/src/cpp/SqliteQuery.hpp"
#include "sql/src/cpp/SqliteResults.hpp"

class BigTableLike
{
public:
  BigTableLike(std::shared_ptr<SqliteDb> db, const std::string &tname);
  virtual ~BigTableLike();

  using ITER = std::function<bool (const BytesKey &key, const std::string &data)>;

  void insert(const BytesKey &key, const std::string &data);
  void iterate(const BytesKey &key, ITER func);

  //friend std::ostream& operator<<(std::ostream& os, const BigTableLike &output);
  //friend void swap(BigTableLike &a, BigTableLike &b);
protected:
  // int compare(const BigTableLike &other) const { ... }
  // void copy(const BigTableLike &other) { ... }
  // void clear(void) { ... }
  // bool empty(void) const { ... }
  // void swap(BigTableLike &other) { ... }
private:
  BigTableLike(const BigTableLike &other) = delete; // { copy(other); }
  BigTableLike &operator=(const BigTableLike &other) = delete; // { copy(other); return *this; }
  bool operator==(const BigTableLike &other) = delete; // const { return compare(other)==0; }
  bool operator<(const BigTableLike &other) = delete; // const { return compare(other)==-1; }

  std::shared_ptr<SqliteDb> db;
  std::string tname;

  //bool operator!=(const BigTableLike &other) const { return compare(other)!=0; }
  //bool operator>(const BigTableLike &other) const { return compare(other)==1; }
  //bool operator<=(const BigTableLike &other) const { return compare(other)!=1; }
  //bool operator>=(const BigTableLike &other) const { return compare(other)!=-1; }
};

//std::ostream& operator<<(std::ostream& os, const BigTableLike &output) {}
//void swap(BigTableLike& v1, BigTableLike& v2);
