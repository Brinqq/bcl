#pragma once

template<typename _Type, size_t _Size>
class ring_buffer{
private:
  _Type* front;
  _Type* cur;
  _Type* end;

  inline void construct(const _Type* pos, const _Type& val){
    new(pos) _Type(val);
  }

  inline void Deconstruct(const _Type* pos){
  ~*pos();
  }

  void init(){
    front = (_Type*)malloc(_Size * sizeof(_Type));
    cur = front;
    end = front + (sizeof(_Type) * (_Size + 1));
  };

public:
  void push(const _Type& val){
    if(front == nullptr){init();}
    cur += 1;
    construct(cur, val);
  }

  void push(_Type&& val){
    if(front == nullptr){init();}
  }
};
