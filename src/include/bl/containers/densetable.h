#pragma once

#include "bl/features.h"
#include "bl/containers/vector.h"
#include "bl/assert.h"

#include <type_traits>



namespace bcl{

template<typename _Type>
struct dense_table_traits{
  typedef size_t size_type ;
  static _BCLCONSTEXPR11 size_type block_size = 12;
  static _BCLCONSTEXPR11 size_type max_blocks = 3;
  static _BCLCONSTEXPR11 bool generation = false;

  static _BCLCONSTEXPR11 bool movable = std::is_move_assignable_v<_Type> && std::is_move_constructible_v<_Type>;
  static _BCLCONSTEXPR11 bool copyable = std::is_copy_constructible_v<_Type> && std::is_copy_assignable_v<_Type>;
  static _BCLCONSTEXPR11 bool assignable = std::is_assignable_v<_Type, _Type> || std::is_trivially_assignable_v<_Type, _Type>;
  static _BCLCONSTEXPR11 bool memcpyable = std::is_trivially_copyable_v<_Type>;

  static_assert(copyable == true);
};

template<typename _Type, dense_table_traits<_Type> _Traits = dense_table_traits<_Type>{}>
class dense_table{
private:

  typedef bcl::fixed_vector<_Type, _Traits.block_size> dense_array;
  typedef dense_array::iterator dense_array_iterator;

  
  struct table_node{
    dense_array_iterator data;
    bool active = false;
  };

  typedef bcl::fixed_vector<table_node, 50> lookup_table;

  struct block{
    dense_array data;
  };

public:
  typedef _Type value_type;
  typedef size_t size_type;
  typedef _Type& reference;
  typedef const _Type& const_reference;
  typedef table_node* iterator;
  typedef const  table_node*  const_iterator;
  typedef const _Type* const_type_iterator;
  typedef _Type* type_iterator;


private:
  bcl::fixed_vector<table_node, 50> table;
  iterator back_itr;
  block block;

  template<typename _Vec, typename _Iterator>
  inline size_t get_pos(_Vec& vec, _Iterator itr){
    return itr - vec.data();
  }

public:

  type_iterator begin(){
    return &*block.data.begin();
  }

  const_type_iterator begin()const{
    return &*block.data.begin();
  }

  type_iterator end(){
    type_iterator ret = &*(block.data.end() - 1);
    ret++;
    return ret;
  }

  const_type_iterator end()const{
    type_iterator ret = &*(block.data.end() - 1);
    ret++;
    return ret;
  }


  _Type& front(){
    return block.data.front;
  }

  _Type& back(){
    return block.data.back;
  }

  _Type* data(){
    return block.data.empty;
  }

  bool empty(){
    return block.data.empty();
  }

  void clear(){
    
  }

  size_t capacity(){}

  [[nodiscard]]iterator push_back(const _Type& val){
    table_node node{};
    node.active = true;
    block.data.push_back(val);
    node.data = block.data.begin() + (block.data.size() - 1 ) ;
    table.push_back(node);
    iterator ret = &table.back();
    back_itr = ret;
    return ret;
  }


  [[nodiscard]]iterator push_back(_Type&& val){
    table_node node{};
    node.active = true;
    block.data.push_back(val);
    node.data = block.data.begin() + (block.data.size() - 1 ) ;
    table.push_back(node);
    iterator ret = &table.back();
    back_itr = ret;
    return ret;
  }

  _Type& operator[](const_iterator it){
     return *it->data;
  }

  _Type& at(const_iterator it){
     return *it->data;
  }

  void erase(iterator it){
    if(it->data == block.data.begin() + (block.data.size() -1)){
      table.pop_back();
      block.data.pop_back();
      return;
    }

    back_itr->data = it->data; 
    block.data.erase_swap(it->data);
  }

  void insert(iterator it, const _Type& val){
      if _BCLCONSTEXPR17 (_Traits.movable){
    *it->data = std::move(val);

  }else if(_Traits.assignable){
    *it->data = val;
  }else{
    return;
  }

  };

  size_t size(){return block.data.size();}

  _BCLCONSTEXPR20 size_t max_size()const{
    return _Traits.block_size * _Traits.max_blocks;
  }

}; //class dense_table

}//namespace bcl
