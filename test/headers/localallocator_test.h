#pragma once


#include "doctest/doctest.h"
#include "bcl/memory/localallocator.h"

static inline bcl::local_allocator<200> lccheck;

TEST_CASE("start"){
  bcl::local_allocator<100> a;
}

