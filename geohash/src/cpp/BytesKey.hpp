#pragma once

// Delete bits as needed

//#include <algorithm>
#include <string>
//#include <iostream>
#include <cstdint>
#include <cstddef>
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

class BytesKey
{
public:
  using byte = uint8_t;

  BytesKey()
  {
    bytes = 0;
    sz = 0;
  }

  BytesKey(const char *p)
  {
    sz = strlen(p)/2;
    bytes = new byte[sz];
    for(int i=0;i<sz;i++)
    {
      byte b = 0;
      b |= hexCharToVal(p[i*2]);
      b <<= 4;
      b |= hexCharToVal(p[i*2+1]);
      write(i, b);
    }
  }

  BytesKey(std::size_t sz)
    : sz(sz)
  {
    bytes = new byte[sz];
    memset(bytes, 0, sz);
  }
  BytesKey(const void *contents, std::size_t sz)
    : sz(sz)
  {
    bytes = new byte[sz];
    memcpy(bytes, contents, sz);
  }
  BytesKey(const BytesKey &other)
  {
    sz = 0;
    bytes = 0;
    copy(other);
  }
  BytesKey &operator=(const BytesKey &other) { copy(other); return *this; }

  virtual ~BytesKey()
  {
    clear();
  }

  void clear(void) {
    if (bytes)
    {
      delete [] bytes;
    }
    bytes = 0;
    sz = 0;
  }

  bool empty(void) const { return sz>0; }

  void swap(BytesKey &other) {
    std::swap(bytes, other.bytes);
    std::swap(sz, other.sz);
  }

  int compare(const BytesKey &other) const {
    if (bytes == 0 && other.bytes == 0) { return 0; }
    if (bytes == 0) { return -1; }
    if (other.bytes == 0) { return 1; }

    for(int i = 0; i< sz; i++)
    {
      if (i > other.sz) { return 1; }
      if (bytes[i] < other.bytes[i]) { return -1; }
      if (bytes[i] > other.bytes[i]) { return 1; }
    }
    if (other.sz > sz) { return -1; }
    return 0;
  }

  bool operator==(const BytesKey &other) const { return compare(other)==0; }
  bool operator<(const BytesKey &other) const { return compare(other)==-1; }
  bool operator!=(const BytesKey &other) const { return compare(other)!=0; }
  bool operator>(const BytesKey &other) const { return compare(other)==1; }
  bool operator<=(const BytesKey &other) const { return compare(other)!=1; }
  bool operator>=(const BytesKey &other) const { return compare(other)!=-1; }

  const void *data() const { return bytes; }
  std::size_t size() const { return sz; }

  BytesKey &write(std::size_t pos, const std::string &hex)
  {
    for(int i=0;i<hex.length()/2;i++)
    {
      byte b = 0;
      b |= hexCharToVal(hex[i*2]);
      b <<= 4;
      b |= hexCharToVal(hex[i*2+1]);
      write(pos+i, b);
    }
    return *this;
  }

  BytesKey &write(std::size_t pos, unsigned int i)
  {
    byte b = 0;
    b = ((i)&0xFF);
    write(pos+3, b);
    b = ((i>>8)&0xFF);
    write(pos+2, b);
    b = ((i>>16)&0xFF);
    write(pos+1, b);
    b = ((i>>24)&0xFF);
    write(pos+0, b);
    return *this;
  }

  BytesKey &write(std::size_t pos, byte b)
  {
    if (pos < sz)
    {
      bytes[pos] = b;
    }
    return *this;
  }

  //friend std::ostream& operator<<(std::ostream& os, const BytesKey &output);
  //friend void swap(BytesKey &a, BytesKey &b);
protected:
  void copy(const BytesKey &other) {
    clear();
    sz = other.sz;
    bytes = new byte[sz];
    memcpy(bytes, other.bytes, sz);
  }

private:
  byte hexCharToVal(char s);

  byte *bytes;
  std::size_t sz;

};

//std::ostream& operator<<(std::ostream& os, const BytesKey &output) {}
//void swap(BytesKey& v1, BytesKey& v2);
