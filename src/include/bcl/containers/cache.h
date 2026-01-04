#pragma once

#include "bcl/defines.h"
#include "bcl/features.h"

#include <memory>

namespace bk{

/**
 * \class in_cache
 * \brief A inline fixed size key-value cache that uses linear probing
 * to find entries from a associative key.
 * \tparam _Key - Key type used for lookups.
 * \tparam _Entry - Type stored as entries.
 * \tparm _Max - Max cache size.
*/
template<typename _Key, typename _Entry, size_t _Max>
class in_cache{
private:
  // probably shouldnt be this high anyways tbh.
  static_assert(_Max < 256, "Max cache size is 256");

  _Key keys[_Max];
  _Entry entries[_Max];
  uint8_t age[_Max];

  uint8_t count;
  

  int x = sizeof(in_cache<int, int, 32>);
public:

/**
 * \fn size
 * \brief Get the number slots occupied in the cache.
 * \ret element count.
 */
size_t size() const{
  return count;
}

/**
 * \fn max_size
 * \brief Gets the max amount of elements that can fit inside of the cache.
 * \ret Max element count.
 */
size_t max_size() const{
  return _Max;
}

/**
 * \fn bytes
 * \brief Gets the total size of container in bytes.
 * \ret Byte count.
 */
size_t bytes() const{
  return sizeof(in_cache<_Key, _Entry, _Max>);
};

/**
 * \fn find
 * \brief Finds a entry using a key mapping.
 * \param _Key[in] - The Key used for probing the entry list.
 * \param _Entry*[out] - Entry copy dst.
 * \ret If a key was found.
 */
_bknodiscard bool find(const _Key& key, _Entry* entry){
  bool f = 0;
  int i = 0;
  //two pass here because branch/early return was preveting compiler
  //auto vectorization,This may end up being slower for smaller caches sizes due
  //to no early return.
  for(; i < count; ++i){
    if(key[i] == *key){
      f = true;
    }
  }
  if(f){
    *entry = entry[i];
    return true;
  }
  return false;
}

void insert(_Key& key, const _Entry& entry){
  if((count += 1) == _Max){
    return;
  }

  _Entry* itr = entries + count;
  new(itr) _Entry();
  *itr = entry;
  count++;
}


/**
 * \fn invalidate_all
 * \brief Invalidates just the key/entry cache, Then shifts entire cache
 * \param _Key[in] - the key mapping to invalidate.
 * \note If key is not found we do nothing.
 */
void invalidate_key(){

};

/**
 * \fn invalidate_all
 * \brief Invalidates entire cache.
 */
void invalidate_all(){
  _Entry* b = entries;
  _Entry* e = b + count;
  while(b != e){
    b->~_Entry();
    b++;
  }
  count = 0;
}

in_cache(){}
~in_cache(){}

// dont want these
in_cache(const in_cache& rhs) = delete;
in_cache& operator=(const in_cache& rhs) = delete;
in_cache(in_cache&& rhs) = delete;
in_cache& operator=(in_cache&& rhs) = delete;


};//class in_cache

}//namespace bk
