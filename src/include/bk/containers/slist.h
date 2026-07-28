#pragma once
#include "bk/memory/system_allocator.h"

namespace bk{

// template<typename _Type, typename _Allocator = SystemAllocator >
// class slist{};




template<typename _Type = monostate>
class in_slist{
  class node{
    _bkemptyaddress _Type val;
    void* next;
  };

  node* head;
private:

};

}
