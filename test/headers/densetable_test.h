#pragma once

#include "bl/containers/densetable.h"

#include <random>

class Entity{
private:
  struct Vec2{
    float x, y;
  };

  size_t id;
  Vec2 pos;
public:
  
  
};


template<typename _Table>
static void log(_Table& t){
  int i = 0;
  for(int v : t){
    printf("index %i: %i\n",i, v);
    i++;
  }
};

namespace densetable_test{

  inline void Start(){
    // Entity e1;
    int i = 2;

    sizeof(bcl::dense_table<int>);

    bcl::dense_table<int> podTable;
    // bcl::dense_table<Entity> table;
    // table.push_back(e1);
    bcl::dense_table<int>::iterator itr = podTable.push_back(i);
    int x = podTable.at(itr);

    podTable.insert(itr, 69);
    bcl::dense_table<int>::iterator a = podTable.push_back(1);
    bcl::dense_table<int>::iterator b = podTable.push_back(2);
    bcl::dense_table<int>::iterator c = podTable.push_back(3);
    bcl::dense_table<int>::iterator d = podTable.push_back(4);
    log(podTable);   
    podTable.erase(d);
    log(podTable);   


  }
}


