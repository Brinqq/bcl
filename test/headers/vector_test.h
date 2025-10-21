#pragma once
#include "bl/containers/vector.h"
#include "test.h"


#include <array>
template class bcl::fixed_vector<int, 20>;


using namespace bcl;

namespace VectorTest{
  inline void custom_fix_vec(){
  printf("starting fixed vector test!\n");

    //init
    {
      fixed_vector<CtorCheckType, 5> ctor(5);
      check_eq( _ctor_t_def_count == 5);
      _ctor_t_reset_counter();
    }

    {// init with ilist
     fixed_vector<int, 5> vec{0, 2, 3, 4}; 
    }

    {//init with range
      std::array<int, 5> arr = {0, 2, 3, 4, 5};
      int* s = arr.data();
      int* e = s + arr.size();

      fixed_vector<int, 5> vec(s, e);
      for(int i = 0; i < 5; ++i){
        check_eq(arr[i] == vec[i]);
      }
    }



    { //push_back
      fixed_vector<int, 5> t;
      fixed_vector<SimpleType, 5> nt;
      SimpleType a{};
      nt.push_back(a);
      //check for no grow
      t.push_back(1);
      t.push_back(2);
      t.push_back(3);
      t.push_back(4);
      t.push_back(5);
      t.push_back(6);
      t.push_back(7);
      // for(int& i : t){
      //   printf("%i\n", i);
      // }
      check_eq(t.size() == 5)
      nt.clear();
      t.clear();
    }

    {

    // simple funcs
      fixed_vector<int, 10> ec;
      check_eq(ec.empty() == true);
      ec.push_back(1);
      check_eq(ec.front() == 1);
      check_eq(ec.back() == 1);
      check_eq(ec[0] == 1);
      check_eq(ec.at(0) == 1);
      check_eq(ec.max_size() == 10)
      check_eq(ec.capacity() == 10)
  }


  {//insert
    fixed_vector<int, 20> vec;
    fixed_vector<int, 20> vec1;
  }

  {// assign and insert/erase back extra etc.
    fixed_vector<int, 20> vec;
    int x = 2;
    vec.assign(19, x);
  }



  };

  inline void Start(){
    custom_fix_vec();
    // PushBackNoGrow();
    // FixedVectorClear();
    // FixedVectorBasic();
  }
}
