#pragma once
#include "bcl/containers/pool.h"
#include "test.h"


namespace pool_test{
  inline void start(){

    // init
    {
      bcl::pool<int, 2> pool;
      sizeof(bcl::pool<int, 4>);
      int* h = pool.allocate();
      int* l = pool.allocate();
      int* k = pool.allocate();
      pool.release(&l);
      int* n = pool.allocate();
      pool.empty();

    }
  }
}
