#pragma once
#include <limits>
#include <stddef.h>
#include <stdint.h>
#include "bcl/features.h"

namespace bcl{

template<size_t _size>
class bitset{
  public:
  typedef uint64_t intergral_type;
  private:
  static _BCLCONSTEXPR11 size_t set_count = (_size / 64) + 1;
  uint64_t set[set_count];

  private:

  public:
  bool operator[](size_t pos){}
  bool check(){};

  size_t max(){return _size;}

  void set_bit(size_t pos, bool val){}

  void reset_all(bool val){
    for(int i = 0; i < set_count; ++i ){ set[i] = 0;}
  }

  void set_all(bool val){
    if(val){
      for(int i = 0; i < set_count; ++i ){ set[i] = std::numeric_limits<intergral_type>();}
      return;
    }
      reset_all();
    
  }

  void reset(size_t pos){}
  void flip(size_t pos){}

  int first_index(bool val){}
  int last_index(bool val){}

  bool all(bool val){}
  bool any(bool val){}
  bool none(bool val){}

  bitset(){}
  bitset(const bitset& other){}
  bitset(bitset&& other){}
  ~bitset(){}
};

}
