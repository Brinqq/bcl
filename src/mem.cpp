#include "bl/memory/memory.h"

namespace bl{
typedef char* byte;

size_t AlignP2(const size_t size, const size_t align){return (size + align - 1) & ~(align - 1);}
size_t AlignedSize(const size_t size, const size_t align){ return (size + align) - (size % align);}

}
