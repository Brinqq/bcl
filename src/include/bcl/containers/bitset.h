#pragma once
#include <stdint.h>
#include "bcl/features.h"
#include "bcl/sys/intrinw.h"

namespace bk{

class bitset{
private:
  static constexpr uint64_t MAX_MASK = ~0ULL;
  static constexpr uint64_t CLEAR_MASK = 0;
  uint64_t con;
public:

/**
 *  \fn first_zero
 *  \brief Gets the index of the first zero bit.
 *
 *  \param int*[out] - Index of the bit if found.
 *  \ret if a zero bit was found
**/
  _bknodiscard bool first_zero(int* idx) const{
    int r = bk::BSF64(~con); 
    if(r == 0) return false;
    *idx = r - 1;
    return true;
  }

/**
 *  \fn first_set
 *  \brief Gets the index of the first set bit.
 *
 *  \param int*[out] - Index of the bit if found.
 *  \ret if a set bit was found.
**/
  _bknodiscard bool first_set(int* idx) const{
    int r = bk::BSF64(con); 
    if(r == 0) return false;
    *idx = r - 1;
    return true;
  }

  // void flip(uint32_t idx){
  //   // uint64_t mask = 1 << idx;
  // }

  /**
   * \fn flip_all
   * \brief Flips all bits.
   *
  **/
  void flip_all(){
      con = ~con;
  }
  
  
  /**
   * \fn set
   * \brief Sets a bit
   *
   * \param uint32_t - Index of the bit to be set.
  **/
  void set(uint32_t idx){
    uint64_t mask = 1ULL << idx;
    con |= mask;
  }

  /**
   *  \fn set_all
   *  \brief Sets all bits in set to 1.
  **/
  void set_all(){
    con = MAX_MASK;
  }


  /**
   *  \fn is_set
   *  \brief Sets all bits in set to 1.
   *
   *  \param uint32_t - Index of to check.
   *  \ret If the bit was set.
  **/
  bool is_set(uint32_t idx) const{
    uint64_t mask = 1ULL << idx;
    return (con & mask) != 0;
  }


  /**
   * \fn set
   * \brief clears a bit
   *
   * \param uint32_t - Index of the bit to be cleared.
  **/
  void clear(int idx){
    uint64_t mask = ~(1ULL << idx);
    con &= mask;
  }

  /**
   *  \fn clear_all
   *  \brief Sets all bits in set to 0.
   **/
  void clear_all(){
    con = CLEAR_MASK;
  }


  /**
   *  \fn is_clear
   *  \brief Sets all bits in set to 0.
   *
   *  \param uint32_t - Index of to check.
   *  \ret If the bit was 0.
  **/
  bool is_clear(int idx) const{
    uint64_t mask = con >> idx;
    return (mask & 1) == 0; 
  }

  /**
   *  \fn are_all_set
   *  \brief Gets if alteast one bit is set.
   *
   *  \ret If a bit was set;
  **/
  bool are_any_set() const{
    return con != CLEAR_MASK;
  }


  /**
   *  \fn are_all_set
   *  \brief Gets if all bits are set.
   *
   *  \ret If All the bits are set to 1.
  **/
  bool are_all_set() const{
    return con == MAX_MASK;
  }


  // int zero_count() const{}
  // int one_count() const{}
  // void flip_range(){}
  // void set_range(){}
  // void clear_range(){}

  bitset():con(0){}
  ~bitset(){}

  bitset(const bitset& rhs) noexcept{
    this->con = rhs.con;
  }

  bitset(bitset&& rhs) noexcept{
    this->con = rhs.con;
    rhs.con = CLEAR_MASK;
  }

  bitset& operator=(const bitset& rhs){
    this->con = rhs.con;
    return *this;
  }

  bitset& operator=(bitset&& rhs){
    if(this == &rhs) return *this;
    this->con = rhs.con;
    rhs.con = CLEAR_MASK;
    return *this;
  }

  bool operator==(const bitset& rhs){
    return this->con == rhs.con;
  }

  bool operator!=(const bitset& rhs){
    return this->con != rhs.con;
  }

};//class bitset
}//namespace bk
