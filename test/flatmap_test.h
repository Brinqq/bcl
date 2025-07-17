#pragma once
#include "global.h"
#include "../src/include/bl/containers/flatmap.h"

#include "cstdlib"

namespace flatmap_test{

inline void T(){
  bl::FlatMap<int, int> a;
  a.Reserve(5);
  int v;
  for(int i = 0; i < 30; i++){
    v = rand();
    a.Insert(rand(), v);
  }
  
}

}
