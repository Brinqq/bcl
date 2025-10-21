#include <stdio.h>

// oprhan headers so clangd doesnt complain about missing compilation data base info on header only libs.
#include "bl/containers/densetable.h"
#include "bl/containers/tagptr.h"
#include "bl/containers/vector.h"
#include "bl/containers/freelist.h"
#include "bl/containers/pool.h"
#include "bl/containers/vector.h"
#include "bl/containers/pool.h"
#include "bl/memory/virtualallocator.h"

#include "headers/pool_test.h"
#include "headers/vector_test.h"


#include <array>

int main(){
  pool_test::start();
  printf("exit complete!");
  return 0;
}
