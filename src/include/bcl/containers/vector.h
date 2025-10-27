#pragma once

#include "bcl/features.h"
#include "bcl/assert.h"

#include <initializer_list>
#include <algorithm>


namespace bcl{

template<typename _Type, uint32_t _Capacity, typename _Allocator = std::allocator<_Type>>
class fixed_vector : public _Allocator{
private:
  _Type* _dat;
  uint32_t _size;

  //constants
  static constexpr bool _trivial = std::is_trivial_v<_Type>;
  
  //internal helpers
  void construct(_Type* addr){
    new(addr) _Type();
  }

  _BCLCONSTEXPR20 void construct(_Type* start, _Type*  end){
    _Type* cur = start;
    while(cur != end){
      new(cur) _Type(); 
      cur++;
    }
  }


  template<typename ..._Val>
  _BCLCONSTEXPR20 void _construct_back(_Val&& ...val){
    new(end()) _Type(std::forward<_Val>(val)...);
    _size++;
  }

  void deconstruct(_Type* addr){
    addr->~_Type();
  }

  void deconstruct(_Type* start, _Type* end){
    _Type* cur = start;
    while(cur < end){
      cur->~_Type();
      cur++;
    } 
  }

  void copy(_Type* addr, const _Type& val){
    *addr = val;
  };

  void copy(_Type* start, _Type* end, const _Type& val){
    _Type* cur = start;
    while(cur != end){
      *cur = val;
      cur++;
    }
  };

  void alloc(){
    _dat = static_cast<_Allocator*>(this)->allocate(_Capacity);
    _bclassert_msg(_dat != nullptr,  "fixed vector failed to allocate memory");
    memset(_dat, 0, sizeof(_Type) * _Capacity);
  }

  void dealloc(){
    static_cast<_Allocator*>(this)->deallocate(_dat, _Capacity);
  }

public:
  typedef _Type type_value;
  typedef size_t size_type;
  typedef  _Type& reference;
  typedef const _Type& const_reference;
  typedef _Type* iterator;
  typedef const _Type* const_iterator;
  typedef _Type* reverse_iterator;
  typedef const _Type* const_reverse_iterator;

  
  //start of public interface

  _BCLCONSTEXPR20 _Type& at(size_t pos){
    if(_size == 0 || pos > _size - 1){std::abort();}
    return _dat[pos];
  }

   _BCLCONSTEXPR20 const _Type& at(size_t pos) const{
    if(_size == 0 || pos > _size - 1){std::abort();}
    return _dat[pos];
  }

  _BCLCONSTEXPR20 _Type& operator[](size_t pos){return _dat[pos];}
  _BCLCONSTEXPR20 _Type& front(){return _dat[0];}
  _BCLCONSTEXPR20 _Type& back(){return _dat[_size - 1];}
  _BCLCONSTEXPR20 _Type* data(){return _dat;};

  _BCLCONSTEXPR20 const _Type& operator[](size_t pos)const{return _dat[pos];}
  _BCLCONSTEXPR20 const _Type& front()const{return _dat[0];}
  _BCLCONSTEXPR20 const _Type& back()const{return _dat[_size - 1];}
  _BCLCONSTEXPR20 const _Type* data()const{return _dat;};

  _BCLCONSTEXPR20 bool empty()const{return _size == 0;}
  _BCLCONSTEXPR20 size_t size()const{return static_cast<size_t>(_size);}
  _BCLCONSTEXPR20 size_t max_size()const{return static_cast<size_t>(_Capacity);}
  _BCLCONSTEXPR20 size_t capacity()const{return static_cast<size_t>(_Capacity);}

  _BCLCONSTEXPR20 _Type* begin()const{return _dat;}
  _BCLCONSTEXPR20 _Type* end()const{return _dat + (_size);}

  _BCLCONSTEXPR20 const _Type* cbegin()const{return _dat;}
  _BCLCONSTEXPR20 const _Type* cend()const{return _dat + (_size);}


  // standard vector functions(insert, erase, emplace, etc...) return iterators to combat vector growing and invalidating the immediate iterator,
  // while we dont need to handle this, for api completeness we will mimic this and return iterators also.

  // in situations where a std::vector is expected to grow, we do nothing and let the program leak(continue in invalid state). ie no bounds checking in release.
  // subject to change.

  // for single element insertions if size < (_Capacity - 1) == false, we do not insert val. TLDR if full does nothing!
  // for multi element insertions we insert from pos intell we reach max size;


  _BCLCONSTEXPR20 void clear(){
    deconstruct(begin(), end());
    _size = 0;
  };

  _BCLCONSTEXPR20 _Type* insert(_Type* pos, const _Type& val){
    if(_size == _Capacity){return nullptr;}
    construct(end());
    std::move_backward(pos, end()-1, end());
    *pos = val;
    _size++;
    return pos;
  }

 _BCLCONSTEXPR20 _Type* insert(_Type* pos, _Type&& val){
    if(_size == _Capacity){return nullptr;}
    construct(end());
    std::move_backward(pos, end()-1, end());
    *pos = val;
    _size++;
    return pos;
  }

  _BCLCONSTEXPR20 void assign(size_t count, _Type& val){
    _Type* rs = begin();
    _Type* re = begin() + (count + 1);
    construct(rs, re);
    copy(rs, re, val);
    _size = count;
  }

  template<class ..._Args>
 _BCLCONSTEXPR20 void emplace_back(_Args&&... args){
    if(_size == _Capacity){return;}
    _construct_back(args...);
  }

 _BCLCONSTEXPR20 void push_back(const _Type& val){
    if(_size == _Capacity){return;}
    _construct_back(val);
  }

 _BCLCONSTEXPR20 void push_back(_Type&& val){
    if(_size == _Capacity){return;}
    _construct_back(std::move(val));
  }


  _BCLCONSTEXPR20 void resize(size_t size){
    if(size >= _Capacity){return;}
    _Type* s;
    _Type* e;

    if(size < _size){
      s = _dat + size;
      e = end();
      deconstruct(s, e);
      _size = size;
      return;
    }


    if(size > _size){
      s = _dat + _size;
      e = _dat + size;
      construct(s, e); 
      _size = size;
    }
  }


 _BCLCONSTEXPR20 void pop_back(){
    if(_size == 0){return;}
    deconstruct(end() - 1);
    _size--;
  }

  // non stl methods
  _BCLCONSTEXPR20 bool full()const{return _size == _Capacity;}
    void erase_swap(_Type* pos){
    std::swap(*pos, *(end() - 1));
    pop_back();
  }

  // extension of erase_swap, inserts at end then swaps with pos iterator.
 _BCLCONSTEXPR20 void insert_swap(_Type* pos, const _Type& val){
    _bclassert_msg(_size  + 1 > _Capacity, "Vector at max capacity.");
    _construct_back(val);
    std::swap(*pos, *(end() - 1));
  }

  iterator it(size_t pos){
    return begin() + pos;
  };




  //constructers
 _BCLCONSTEXPR20 fixed_vector():_dat(0), _size(0){
    alloc();
  }

   explicit _BCLCONSTEXPR20 fixed_vector(uint32_t count):_size(count){
     _bclassert_msg(count <= _Capacity, "fixed vector inistantiated with a size greater than fixed capacity");
     alloc();
     construct(begin(), end());
   }

   explicit _BCLCONSTEXPR20 fixed_vector(uint32_t count, const _Type& cpy):_size(count){
      alloc();
      construct(begin(), end());
      copy(begin(), end(), cpy);
   }

   explicit _BCLCONSTEXPR20 fixed_vector( _Type* rs,  _Type* re){
    _bclassert_msg((re - rs) <= _Capacity, "range extendes past the max capacity of fixed vector.");
    alloc();
    _Type* cur = begin();
    while(rs != re){
      construct(cur);
      copy(cur, *rs);
      rs++;
      cur++;
    }

    _size  = re - rs;
   }

   explicit _BCLCONSTEXPR20 fixed_vector(std::initializer_list<_Type> ilist){
    _bclassert_msg(ilist.size() <= _Capacity, "initializer list size is greater than max capacity.");
    alloc();
    _Type* cur = begin();
    for(const _Type& v : ilist){
      construct(cur);
      copy(cur, v);
      cur++;
    }
    _size = ilist.size();
   }


  _BCLCONSTEXPR20 fixed_vector(fixed_vector&& other){
    this->_dat = other._dat;
    this->_size = other._size;
    other._dat = nullptr;
    other._size = 0;
  }

  _BCLCONSTEXPR20 ~fixed_vector(){dealloc();}

  // TODO: implement these
  //explicit _BCLCONSTEXPR20 fixed_vector(uint32_t count, _Type&& mv):_size(count){} - impl
  // _BCLCONSTEXPR20 fixed_vector(const fixed_vector& other){}
  // _Type* insert(_Type* pos, size_t count, const _Type& val){} -- impl
  // _Type* insert(_Type* pos, std::initializer_list<_Type> ilist){} -- impl
  // template<typename _Ittype> _Type* insert(_Type* pos, _Ittype start, _Ittype last){} -- impl
  // void swap(fixed_vector vec){} --impl
  //void resize(size_t size, const _Type& cpy){} --impl
  // void erase(size_t pos){} --impl
  // void erase(_Type* itr){} --impl
  // _Type* emplace(){} --impl
  // assign

protected:
  // this sets internal buffer to a ptr w/ preallocated memory. used mainly for a inline vector subclass.
  // if a object is constructed with this, insure the base classes deconstructer is never called or it will try to free a random pointer.
  _BCLCONSTEXPR20 fixed_vector(_Type* dat):_dat(dat), _size(0){}

}; //fixed_vector

template<typename _Type, size_t _Size>
class inline_vector : public fixed_vector<_Type, _Size>{
  
  _Type _dat[_Size] = {};
  
public:
  inline_vector():fixed_vector<_Type, _Size>(_dat){}

}; //inline_vector


class page_vector{

}; //page_vector


} // bcl


