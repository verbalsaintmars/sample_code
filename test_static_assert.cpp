#include <iostream>

#define ASSERTA(state) sizeof(state)

struct H3{};
struct H2{

};

struct H1{
   typedef int type;
   H1(H2){}
};


template<typename T1, typename T2>
struct CHK{

   typedef int type;

   static typename T1::type check(){
      T1 t( (T2()) );
   }

   CHK(){
//      void (*f)() = check;
   }

};

template<typename T1, typename T2>
struct base : CHK<T1, T2>
{


};

int ha(){
   CHK<H1,H3>::type dum;
}

int main(){
//   base<H1,H2> b;


}
