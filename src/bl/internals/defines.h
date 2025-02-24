#pragma once
#include "cinttypes"
#include "assert.h"

#define _BASSERT_ENABLE 1

#if __cplusplus < 20 
#error Minimum required c++ standard 20!
#endif

#if _BASSERT_ENABLE
#define bassert(x) assert(x)
#else
#define bassert(x)
#endif 
