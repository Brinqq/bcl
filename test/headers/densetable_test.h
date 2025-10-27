#pragma once

#include "bcl/containers/densetable.h"
#include "test.h"

#include "doctest/doctest.h"

#include <random>

template class bcl::dense_table<int>;

namespace densetable_test{

  TEST_CASE("max_size"){
      bcl::dense_table<int> def;
      bcl::dense_table<int, bcl::dense_table_traits<int, uint32_t, false>> x32;
      bcl::dense_table<int, bcl::dense_table_traits<int, uint64_t, false>> x64;
      size_t def_f = std::numeric_limits<uint16_t>::max();
      size_t x32_f = std::numeric_limits<uint32_t>::max();
      size_t x64_f = std::numeric_limits<uint64_t>::max();
      CHECK(def.max_size() == def_f);
      CHECK(x32.max_size() == x32_f);
      CHECK(x64.max_size() == x64_f);
  }

  TEST_CASE("insert"){
    bcl::dense_table<int> x;
    for(int i = 0; i < 67; ++i){
      x.insert(rand());
    }
  }
  
  TEST_CASE("get and friends"){
    bcl::dense_table<int> a;
    bcl::dense_table<int>::handle h = a.insert(2);
    bcl::dense_table<int>::handle l = a.insert(3);
    CHECK(a.get(h) == 2);
    CHECK(a.get(l) == 3);
    CHECK(a[h] == 2);
    CHECK(a[l] == 3);
  }

  TEST_CASE("erase"){
    bcl::dense_table<int> e;
    typedef bcl::dense_table<int>::handle h;
    h h1 = e.insert(2);
    h h2 = e.insert(22);
    h h3 = e.insert(920);
    h h4 = e.insert(892);
    h h5 = e.insert(2);

    e.erase(h2);
    e.erase(h1);
    CHECK(e[h5] == 2);
    CHECK(e[h4] == 892);
  }


  TEST_CASE("dev"){
    bcl::dense_table<int> x;
      // x.insert(2);
      // x.insert(2);

  }

}
