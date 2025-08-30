#pragma once
#include "stdint.h"

// similar to std::array but allocates a fixed amount of objects in a separate heap buffer instead of inline.

namespace bl{

template<typename _Type, int _Size, int _Align = 16>
class HeapArray{
private:
  _Type* pObjects;
public:
  HeapArray(){ pObjects = new _Type[_Size];}
  ~HeapArray(){delete[] pObjects;}

  inline _Type& operator[](const uint32_t index){return pObjects[index];}
  inline uint32_t Size(){return _Size;}
  inline _Type& At(const uint32_t index){ return pObjects[index];}
  inline _Type* Data(){return pObjects;};
};

}
