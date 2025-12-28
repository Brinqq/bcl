#include "bcl/memory/virtualallocator.h"
#include "bcl/memory/bkmemory.h"
#include "bcl/assert.h"

#include <stdio.h>

// #if defined(_WIN32)
//
// #include <windows.h>
//
// static uint32_t sysk_page_size(){
//   static uint32_t page_cached = 0;
//   if(page_cached == 0){
//     SYSTEM_INFO sys;
//     LPSYSTEM_INFO dat = &sys;
//     GetSystemInfo(dat);
//     page_cached = dat->dwPageSize;
//   }
//   return page_cached;
// }
//
// static uint32_t sysk_heap_size(){
//   static uint32_t heap_cached = 0;
//   if(heap_cached == 0){
//     SYSTEM_INFO sys;
//     LPSYSTEM_INFO dat = &sys;
//     GetSystemInfo(dat);
//     heap_cached = dat->dwAllocationGranularity;
//   }
//   return heap_cached;
//
// };
//
// static void* sysk_reserve(void* addr, const size_t pages){
//   return VirtualAlloc(addr, pages * sysk_page_size(), MEM_RESERVE, PAGE_NOACCESS);
// };
//
// static void* sysk_alloc_heaps(const uint32_t count){
//   size_t bytes = count * sysk_heap_size();
//   void* ret = VirtualAlloc(nullptr, bytes, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
//   memset(ret, 0, bytes);
//   return ret;
// };
//
// static int sysk_commit(const size_t pages){
//   return 0;
// };
//
//
// static int sysk_uncommit(void* addr, const size_t pages){
//   VirtualFree(addr, sysk_page_size() * pages, MEM_DECOMMIT);
//   return 0;
// };
//
// #endif
//
// #if defined(__APPLE__)
// #include <cstdlib>
// static uint32_t sysk_page_size(){
//   std::abort();
//   return 1;
// }
//
// static uint32_t sysk_heap_size(){
//   std::abort();
//   return 1;
// };
//
// static void* sysk_reserve(void* addr, const size_t pages){
//   std::abort();
//   return nullptr;
// };
//
// static void* sysk_alloc_heaps(const uint32_t count){
//   std::abort();
//   return nullptr;
// };
//
// static int sysk_commit(const size_t pages){
//   std::abort();
//   return 0;
// };
//
//
// static int sysk_uncommit(void* addr, const size_t pages){
//   std::abort();
//   return 0;
// };
//
//
// #endif
//
// #define _page_align(_size) ((_size % sysk_page_size()) + _size)
//
// struct header{
//   size_t size;
// };
//
// struct fnode{
//   fnode* next;
//   fnode* prev;
//   size_t size;
// };
//
//
// struct internal{
//   fnode* flist_start;
//   fnode* flist_end;
// };
//
//
// static internal dat;
//
// static void* construct_base(const uint32_t blocks){
//     size_t user_bytes = (blocks * sysk_page_size());
//     uint32_t start_heaps = (user_bytes / sysk_heap_size()) + 1;
//     size_t heap_bytes = (start_heaps * sysk_heap_size());
//
//     void* heap = sysk_alloc_heaps(start_heaps);
//     dat.flist_start = reinterpret_cast<fnode*>((bcl::byte)heap + user_bytes);
//     dat.flist_end = dat.flist_start;
//     dat.flist_start->size = heap_bytes - user_bytes;
//     sysk_uncommit(heap, blocks);
//     return heap;
// }
//
//
// static fnode* walk_find(const size_t bytes){
//   fnode* n = dat.flist_start;
//
//   if(n->size > bytes){
//     return n;
//   };
//
//   while(n->next != nullptr){
//     n = n->next;
//     if(n->size > bytes){
//       return n;
//     };
//   }
//
//   return nullptr;
// };
//
// static bool empty_fnode(){
//
// }
//
// static void destroy_fnode(fnode* node){
//   if(node->next != nullptr && node->prev != nullptr){
//     node->prev->next = node->next;
//     node->next->prev = node->prev;
//     return;
//   }
//   
//   if(node->next == nullptr && node->prev != nullptr){
//     node->prev->next = nullptr;
//     dat.flist_end = node->prev;
//     return;
//   }
//
//   if(node->next != nullptr && node->prev == nullptr){
//     node->next->prev = nullptr;
//     dat.flist_start = node->next;
//     return;;
//   }
//   
//   if(node->next == nullptr && node->prev == nullptr){
//     dat.flist_start = nullptr;
//     dat.flist_end = nullptr;
//   }
// }
//
// static void insert_fnode(fnode* node,const size_t bytes){
//   dat.flist_end->next = node;
//   node->size = bytes;
// }
//
// using namespace bcl;
//
// // blocks = page size:4096 commonly
// // free_block = c[node, freespace ...]
// // reserved_block = u[]
// // commited_block = c[header, userdata ...]
// // when we commit, we return a addr to contigues commited_blocks with the header being nPagesize.
//
//
// void virtual_allocator::commit(const void* addr, const size_t bytes){
//
// }
//
// void virtual_allocator::free(void* addr){
//
// }
//
// void* virtual_allocator::reserve_memory(const size_t bytes){
//   void* addr;
//   void* ret = nullptr;
//   size_t aligned_bytes = align_p2(bytes, sysk_page_size());
//
//   // on first alloc flist is always nullptr. so on init we construct_base()
//   if(dat.flist_start == nullptr){
//     uint32_t num_blocks = ((aligned_bytes / sysk_page_size()) + 1);
//     ret = construct_base(num_blocks - 1);
//     return ret;
//   }
//   
//   fnode* free_addr = walk_find(aligned_bytes);
//
//   if(free_addr == nullptr){
//     // sysk_alloc_heaps();
//   }
//   
//
//   fnode* split_node = (fnode*)((bcl::byte)free_addr +  aligned_bytes);
//   insert_fnode(split_node, free_addr->size - aligned_bytes);
//   destroy_fnode(reinterpret_cast<fnode*>(free_addr));
//   sysk_reserve(free_addr, aligned_bytes / sysk_page_size());
//   
//
//   return ret;
//
// };
