#include <iostream>
#include <string>

struct TYPE_1
{
   std::string result{"type_1"};
   std::string get_result() const
   {
      return result;
   }
};


struct TYPE_2
{
   std::string result{"type_2"};
   std::string get_the_result() const
   {
      return result;
   }
};


struct Trait
{
   typedef TYPE_1 type1;
   typedef TYPE_2 type2;
};


template<typename T>
struct ToString
{
   T inner;
   ToString(const T& t) : inner(t){}
   operator std::string() const;
};


template<>
ToString<TYPE_1>::operator std::string() const
{
      return inner.get_result();
}


template<>
ToString<TYPE_2>::operator std::string() const
{
      return inner.get_the_result();
}


template<typename T>
class OUTTER
{
   typedef OUTTER This;

   template<typename U>
   void printf(U u)
   {
      std::cout << static_cast<const std::string&>(ToString<U>(u)) << std::endl;
   }

public:
   void run_me()
   {
      printf(typename T::type1());
      printf(typename T::type2());
   }
};


int main(){
   OUTTER<Trait> outter;
   outter.run_me();
}
