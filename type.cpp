#include <iostream>
#include <typeinfo>

struct base{
typedef int type;
};

struct derived : base{
typedef double type;
};

int main(){

   derived d;
   std::cout << typeid(base::type).name() << std::endl;
}
