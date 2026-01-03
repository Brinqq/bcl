#pragma once

namespace bk{

template<int _Size>
class in_string{
private:
  char dat[_Size];
  int size;
public:

  in_string(){size = 0;}
  ~in_string(){}

  in_string(const in_string& rhs){}
  in_string& operator=(const in_string& rhs){}

  in_string(in_string&& rhs) = delete;
  in_string& operator=(in_string&& rhs) = delete;

};//class in_string
}//namespace bk
