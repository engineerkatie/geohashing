#include "BytesKey.hpp"

//std::ostream& operator<<(std::ostream& os, const BytesKey &output) {}

//void swap(BytesKey& v1, BytesKey& v2) {
//    v1.swap(v2);
//}
BytesKey::byte BytesKey::hexCharToVal(char s)
  {
    switch(s)
    {
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
      return byte(s - '0');

    case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
      return byte(s - 'A' + 10);
    case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
      return byte(s - 'a' + 10);
    default:
      exit(77);
      // not a hex
    }
  }
