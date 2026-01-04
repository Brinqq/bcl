#pragma once

#include "bcl/defines.h"
#include "bcl/features.h"

#include <memory>
#include <algorithm>


namespace bk{

//FUTURE: Descide if we want to update ages on find() hits.

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

  static_assert(
    _Max < 64 &&
    std::is_copy_constructible_v<_Entry> &&
    std::is_copy_assignable_v<_Entry> &&
    std::is_trivially_destructible_v<_Key>
  ,"Error");

  typedef uint8_t _OffsetType;

  _Key keys[_Max];
  _Entry entries[_Max];
  _OffsetType age[_Max]; //sorted by age new -> old, hold 0 based indices
  _OffsetType count = 0;
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
  int idx = -1;

  //two pass here because branch/early-return was preveting the compiler from
  //auto vectorizating the prob seqence, This may end up being slower for smaller caches sizes due
  //to the no early return.
  for(int i = 0; i < count; ++i){
    if(keys[i] == key){
      idx = i;
    }
  }

  if(idx != -1){
    *entry = entries[idx];
    return true;
  }

  return false;
}

/**
 * \fn insert
 * \brief Inserts a new entry/key into the cache.
 * \param _Key[in] - The Key used for mapping.
 * \param _Entry*[in] - Entry copy src.
 */
void insert(const _Key& key, const _Entry& entry){
  if(count == _Max){
    int idx = age[_Max - 1];
    entries[idx].~_Entry();
    std::move_backward(age, age + (_Max - 1), age + (_Max));

    new(entries + idx) _Entry(entry);
    keys[idx] = key;
    *age = idx;
    return;
  }

  if(count > 0){
    std::move_backward(age, age + count , age + (count + 1));
  }

  _Entry* itr = entries + count;
  new(itr) _Entry(entry);
  keys[count] = key;
  age[0] = count;
  count++;
}

/**
 * \fn modify_entry
 * \brief Modifies the entry mapped by _Key
 * \param _Key[in] - The key mapping.
 * \param _Entry&[in] - Entry src we copy into cache.
 * \note If key is not in cache already we insert a new entry,
 *  this will invalidate the LRU entry.
 */
void modify_entry(const _Key& key, const _Entry& entry){
  int idx = -1;

  for(int i = 0 ;i < count; ++i){
    if (keys[i] == key){
      idx =  i;
    };
  }

  if(idx != -1){
    entries[idx] = entry;
    return;
  }

  insert(key, entry);
}


/**
 * \fn invalidate_key
 * \brief Invalidates just the key/entry in cache, Then shifts entire cache
 * \param _Key[in] - the key mapping to invalidate.
 * \note If key is not found we do nothing. Since this is worse case O(n),
 *  it is recommend _Entry is moveable.
 */
// void invalidate_key(){
// };

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


~in_cache(){
  _Entry* s = entries;
  _Entry* e = s + count;
  while(s != e){
    s->~_Entry();
    s++;
  }
}

in_cache(const in_cache& rhs) = delete;
in_cache& operator=(const in_cache& rhs) = delete;
in_cache(in_cache&& rhs) = delete;
in_cache& operator=(in_cache&& rhs) = delete;

};//class in_cache

}//namespace bk
 //
