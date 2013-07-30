template<typename T>
struct Base
{
   void ha(T t);

   Base(){
      T();
   }
};


struct Derived : Base<Derived>
{
   int _a;
   Derived() : _a(10) {
   }
};

int main(){

   Derived *derived = new Derived;

}
