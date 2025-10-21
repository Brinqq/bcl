#pragma once

#include "stdio.h"
#include <random>

#define check_eq(_expr) if(!(_expr)){printf("check failed: (%s) - %s:%i\n", #_expr, __FILE__, __LINE__);}



// Dummy structs
class SimpleType{
  int id;
public:
  SimpleType(){
    id = rand();
    printf("constructor called on simple type - ID: %i\n", id);
  };

  SimpleType(const uint32_t id){
    printf("ID constructor called on simple type - ID: %i\n", id);
  };

  SimpleType(const SimpleType& other){
    this->id = other.id;
    id = rand();
    printf("copy ctor called on simple Type Old ID: %i - New ID: %i\n", other.id, id);
  };

  SimpleType(SimpleType&& other){
    this->id = other.id;
    this->id = -1;
    printf("copy ctor called on simple Type - ID: %i\n", id);
  };

  ~SimpleType(){
    printf("decontructor called on simple Type - ID: %i\n", id);
  };
};


class CtorCheckType{
public:
  static inline size_t def = 0;
  static inline size_t basic = 0;
  static inline size_t advance = 0;
  static void Reset(){def = 0; basic = 0;};

  CtorCheckType(){def++;};
  CtorCheckType(int x){basic++;};
}; 
#define _ctor_t_reset_counter() CtorCheckType::Reset()
#define _ctor_t_def_count CtorCheckType::def
#define _ctor_t_basic_count CtorCheckType::basic

class CopyCheckType{
  uint32_t* ref;
public:
  void reset(){*ref = 0;};
  CopyCheckType() =  delete;
  CopyCheckType(uint32_t* const pCounter): ref(pCounter){}
  CopyCheckType(const CopyCheckType& other){
    this->ref = other.ref;
    *ref += 1;
  }
};
