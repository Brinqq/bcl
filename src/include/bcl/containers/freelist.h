#pragma once

#include <stack>
#include <optional>

#include <vector>
#include <array>


#if defined(x86_64)
#include <immintrin.h>
#endif

#include "bcl/assert.h"
#include "bcl/features.h"


#if defined(__clang__) || defined (__GNUC__)
  inline uint32_t _bitscan64(uint64_t v){return __builtin_ffsl(v);};
#elif defined(_MSVC_VER_)
inline uint32_t _bitscan64(uint64_t v){
    uint64_t ret = 0;
  _bitscanforward64(ret, v);
  return ret;
}
#else
#error //unsupported compiler.
#endif

#define _FREELIST_INLINE_BITVECTOR_MAX 512



namespace bl{
template<typename _Type>
class skFreelist{
    std::stack<_Type, std::vector<_Type>> stack;

public:
  bool Empty(){ return stack.empty();};

  void New(_Type ptr){
    stack.push(ptr);
  }

  std::optional<_Type> Get(){
    std::optional<_Type> ret;
    if(Empty()){ return ret; };
    ret = stack.top();
    stack.pop();
    return ret;
  };
};

}

namespace bcl{


struct _freelist_traits{
  struct _stack{};
  struct _bitvector{};
  struct _linkedlist{};

  bool fixed = false;
  bool force_heap = false;
};

template<size_t _Size, typename _Tag = _freelist_traits::_linkedlist, _freelist_traits _Traits = _freelist_traits{}>
class freelist;

template<size_t _Size, _freelist_traits _Traits>
class freelist<_Size, _freelist_traits::_linkedlist, _Traits>{
private:
public:
  void test(){
    printf("this is a linked list freelist, fixed: %s, node_size: %i\n", _Traits.fixed ? "yes": "no", _Size);
  };

};

template<size_t _Size, _freelist_traits _Traits>
class freelist<_Size, _freelist_traits::_bitvector, _Traits>{
public: 
  typedef uint64_t storage_type;  //maybe support uint32, uint16, uint8, for now hardcode 64 bit int.
  typedef storage_type push_type;
  typedef size_t handle_type;
private:

  struct _index_pair{
      uint32_t word;
      uint32_t index;
  };

  static constexpr bool _inline_storage = ((_Size <= _FREELIST_INLINE_BITVECTOR_MAX) && (_Traits.fixed == true) && (_Traits.force_heap != true));
  static constexpr uint32_t _bit_width = sizeof(storage_type) * 8;

  typedef std::conditional_t<_inline_storage,
          std::array<storage_type, (_Size / _bit_width) + 1>,
          std::vector<storage_type>> 
          _storage;

          _storage _container;
          size_t _size; //switch to std::conditional_t<bool std::monostate, size_t>;

  _BCLCONSTEXPR20 void _set_word(storage_type& word, storage_type pos, storage_type val){
      storage_type mask = val << pos;
      word |= mask;
  }
  
      _BCLCONSTEXPR20 _index_pair _find_free(){
        uint32_t word = 0;
        for(const storage_type& w : _container){
          
          uint32_t index = _bitscan64(~w);

          if(index != 0){
            return {word, index};
          }
          word++;
        }

        return {0, 0};
      }

public:


  // TODO: implement this asap
  void resize(const size_t size){
    
  }

  
  /** 
   * @brief lol
   * \return Returns index of first free index with 1 based indexing, if no free slots returns 0. 
   * user can adjust from there, ex: ret - 1 is the correct index. \note if freelist is not fixed freelist will continue to grow
   * never returning 0.
  */
  handle_type get(){
  //simd?
  
    if constexpr (_inline_storage){
     _index_pair res =  _find_free();
     size_t ret = (res.word * _bit_width) + res.index;
     if(res.index == 0 || ret > _Size){
        return 0;
     }
      _set_word(_container[res.word], res.index - 1, 1);
      return ret;
    }

   if constexpr (!(_inline_storage)){
    _index_pair res = _find_free();
     if(res.index == 0){
      _container.push_back(0);
      _set_word(_container[_container.size() - 1], 0, 1);
      return ((_container.size() - 1) * _bit_width ) + 1;
     }
      _set_word(_container[res.word], res.index - 1, 1);
      return (res.word * _bit_width) + res.index;
   }
  }



  // contrary to get() which returns a 1 index, we expect 0 index here.
   void push(push_type pos){
    uint64_t word =  pos/_bit_width;
    uint64_t normal = pos % _bit_width;
    storage_type mask = (storage_type)1 << normal;
    _container[word] &= (~mask);
  }


  bool empty(){
    // uint32_t c = _container.size();
    // __m256i mask = _mm256_setzero_si256();
    // for(int i = 0; i < c; ++i){
    //   __m256i reg = _mm256_maskz_loadu_epi64(1, &_container[i]);
    //   __m256 l = _mm256_cmpeq_epi64(reg, mask);
    // }
    //
    //
  }

  bool full(){

  }

  _BCLCONSTEXPR20 freelist(){
    if constexpr (!_inline_storage){
      _container.push_back(0);
    }
  }

}; //freelist<specialized bitvector>



template<size_t _Size, _freelist_traits _Traits>
class freelist<_Size, _freelist_traits::_stack, _Traits>{
  void test(){

  };

};

} //bcl
