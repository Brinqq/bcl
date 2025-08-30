#pragma once

//Note: Specified alignment must be a power of 2.
#define blAlign(_Size, _Alignment) (_Size + _Alignment - 1) & ~(_Alignment - 1)

namespace bl{
typedef char* byte;

 size_t AlignP2(const size_t size, const size_t align);
 size_t AlignedSize(const size_t size, const size_t align);

}

