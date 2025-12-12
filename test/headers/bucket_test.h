#pragma once

#include "bcl/containers/bucket.h"
#include "doctest/doctest.h"

inline bk::bucket<uint64_t, 20> kBucketCatch;

TEST_CASE("bucket"){
  bk::bucket<uint64_t, 20> x;
  uint64_t& a = x.construct();
}
