#pragma once
#include "../../src/include/bl/containers/tagptr.h"
#include "test.h"
#include <memory>
#include <bit>

namespace tagptr_test{

  enum struct Tag{
    High,
    Low,
  };

  template<typename _Type>
  void log_tags(bcl::tag_ptr<_Type>& ptr, const Tag t){

    if(t == Tag::High){
      printf("High bits.\n");
      for(int x = 48; x <= 63; ++x ){
        printf("bit: %i - %i\n",x, ptr.check_bit(x));
      }
    }

    if(t == Tag::Low){
      printf("High bits.\n");
      for(int x = 0; x <= 3; ++x ){
        printf("bit: %i - %i\n",x, ptr.check_bit(x));
      }
    }
  }

  static int* ip;

  
  static void check_bit_test(){

  }; 

  static void tag_bit_test(){
    bcl::tag_ptr<int> ptr(ip);
    ptr.tag_bit(0, 1);
    log_tags(ptr, Tag::Low);
    ptr.tag_bit(48, 1);
    log_tags(ptr, Tag::High);
  }; 

  static void check_range_test(){

  }; 

  static void tag_range_test(){

  }; 

  static void get_test(){

  }; 

  static void data_test(){

  }; 

  static void clear(){

  }

  static void clear_low(){

  }

  static void clear_high(){

  }

  static void clear_range(){

  }

  inline void Start(){
  ip = (int*)_aligned_malloc(16, 16);
  memset(ip, 0, 16);
  *ip = 69;
  printf("%i\n", *ip);
    
  bcl::tag_ptr<int> a(ip);
  a.tag_bit(48, 1);
  a.clear_high();
  log_tags(a, Tag::High);


  printf("%i\n",*((int*)a.get_raw()));
    
  }
}
