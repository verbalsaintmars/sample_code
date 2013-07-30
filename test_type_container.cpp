#include <set>


struct Error_Undefined_Type;

template<typename T1, typename T2>
struct type_pair
{
   typedef T1 head_t;
   typedef T2 tail_t;
};

struct empty
{};

template
<
   typename T1 = empty,
   typename T2 = empty,
   typename T3 = empty,
   typename T4 = empty
>
struct type_array{};

template<typename CONTAINER>
struct front;

template<typename CONTAINER>
struct back;

template<>
struct back<empty>
{};

template<>
struct front<empty>
{};

template<typename T1, typename T2>
struct front<type_pair<T1, T2> >
{
   typedef T1 type;
};

template<typename T1>
struct back<type_pair<T1, empty> >
{
   typedef T1 type;
};

template<typename T1, typename T2>
struct back<type_pair<T1, T2> >
{
   typedef typename back<T2>::type type;
};


int main(){

   std::set<int> t;
   t.insert(2);

}
