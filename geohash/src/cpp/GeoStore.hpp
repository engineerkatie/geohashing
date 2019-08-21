#pragma once

// Delete bits as needed

//#include <algorithm>
//#include <utility>
//#include <iostream>

#include <cstdint>
#include <cstddef>

class GeoStore
{
public:
  GeoStore(std::shared_ptr<BigTableLike> bt):bt(bt)
  {
  }
  virtual ~GeoStore()
  {
  }

  

  //friend std::ostream& operator<<(std::ostream& os, const GeoStore &output);
  //friend void swap(GeoStore &a, GeoStore &b);
protected:
  // int compare(const GeoStore &other) const { ... }
  // void copy(const GeoStore &other) { ... }
  // void clear(void) { ... }
  // bool empty(void) const { ... }
  // void swap(GeoStore &other) { ... }
private:
  GeoStore(const GeoStore &other) = delete;
  GeoStore &operator=(const GeoStore &other) = delete;
  bool operator==(const GeoStore &other) = delete;
  bool operator<(const GeoStore &other) = delete;

  std::shared_ptr<BigTableLike> bt

  //bool operator!=(const GeoStore &other) const { return compare(other)!=0; }
  //bool operator>(const GeoStore &other) const { return compare(other)==1; }
  //bool operator<=(const GeoStore &other) const { return compare(other)!=1; }
  //bool operator>=(const GeoStore &other) const { return compare(other)!=-1; }
};

//std::ostream& operator<<(std::ostream& os, const GeoStore &output) {}
//void swap(GeoStore& v1, GeoStore& v2);
