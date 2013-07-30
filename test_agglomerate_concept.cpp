#include <iostream>
#include <string>
#include <typeinfo>


namespace VS_TEST_SUITE
{

//not necessary in C++11
struct empty
{
};

template<typename T1, typename T2>
struct type_pair
{
   using head_t = T1;
   using tail_t = T2;
};

template<typename... Ts>
struct type_array
{
};

template<typename T, T VALUE>
struct static_parameter
{
};

template<typename T, T VALUE>
struct static_value : static_parameter<T, VALUE>
{
   static const T value = VALUE;
};

//-------------

template<typename... Ts>
struct front;

template<>
struct front<>;

template<typename T1, typename... Ts>
struct front<T1, Ts...>
{
   using type = T1;
};


template<typename... Ts>
struct back;

template<>
struct back<>;

template<typename T>
struct back<T>
{
   using type = T;
};

template<typename T1, typename... Ts>
struct back<T1, Ts... > : back<Ts...>
{
};

//----------

template<unsigned int N, typename... Ts>
struct type_at
{
      using type = empty;
};

template<typename T, typename... Ts>
struct type_at<0, T, Ts...>
{
   using type = T;
};

template<unsigned int N, typename T, typename... Ts>
struct type_at<N, T, Ts...>
{
   using type = typename type_at<N-1, Ts...>::type;
};

// <int, double>
// at 3

//----------

template<typename... Ts>
struct depth;

template<>
struct depth<> : static_value<unsigned int, 0>
{
};

template<typename T, typename... Ts>
struct depth<T, Ts...> : static_value<unsigned int, depth<Ts...>::value+1>
{
};

//<int,double>

//----------

template<typename T, typename... Ts>
struct type_index : static_value<int, -1>
{
};


template<typename T, typename... Ts>
struct type_index<T, T, Ts...> : static_value<int, 0>
{
};

template<typename T, typename T1, typename... Ts>
struct type_index<T, T1, Ts...> : static_value<int, (type_index<T, Ts...>::value == -1) ? -1 :
type_index<T, Ts...>::value + 1 >
{
};


//<int, double>

//----------

template<typename... Ts>
struct Vector;


template<>
struct Vector<>
{
};


template<typename T, typename... Ts>
struct Vector<T, Ts...> : Vector<Ts...>
{
   using value_type = T;
   value_type member;
};

//---------


template<typename T, typename... Ts>
T& ref(Vector<T, Ts...>& a_)
{
   return a_.member;
}


//---------

template<unsigned int N, template<typename...> class AGG, typename... Ts>
struct ref_traits;

template<template<typename...> class AGG, typename T, typename... Ts>
struct ref_traits<0, AGG, T, Ts...>
{
   using value_type = typename AGG<T, Ts...>::value_type;

   static value_type& ref(AGG<T, Ts...>& agg)
   {
      return agg.member;
   }
};


template<unsigned int N, template<typename...> class AGG, typename T, typename... Ts>
struct ref_traits<N, AGG, T, Ts...>
{
   using next_t = ref_traits<N-1, AGG, Ts...>;
   using value_type = typename next_t::value_type;

   static value_type& ref(AGG<T, Ts...>& agg)
   {
      return next_t::ref(agg);
   }
};


template<unsigned int N, template<typename...> class AGG, typename... Ts>
inline typename ref_traits<N, AGG, Ts...>::value_type&
ref(AGG<Ts...>& agg)
{
   return ref_traits<N, AGG, Ts...>::ref(agg);
}


} //end of namespace VS_TEST_SUITE

int main(){

   using namespace std;
   using namespace VS_TEST_SUITE;

   cout << typeid(back<int, double, std::string>::type).name() << endl; //print string
   cout << typeid(front<int, double, std::string>::type).name() << endl; //print int

   cout << typeid(type_at<2, double, double, std::string>::type).name() << endl; //print string
   cout << typeid(type_at<12, int, double, std::string>::type).name() << endl; //print empty

   cout << depth<int, int, int>::value << endl; //print 3
   cout << depth<>::value << endl; //print 0

   cout << type_index<float, int, double, std::string>::value << endl; //print -1
   cout << type_index<double, int, double, std::string>::value << endl; //print 1

   Vector<std::string, double> derived;
   Vector<double>& base = derived;

   Vector<int,std::string, double> agg_1;
   ref<int>(agg_1) = 7;
   ref<std::string>(agg_1) = "i am a string!";
   ref<double>(agg_1) = 20.3;
   cout << ref<std::string>(agg_1) << endl;
   cout << ref<int>(agg_1) << endl;
   cout << ref<double>(agg_1) << endl;

   Vector<int, double, std::string> agg_2;
   ref<0>(agg_2) = 10;
   ref<1>(agg_2) = 3.14;
   ref<2>(agg_2) = "i am a string, again!!";
   cout << ref<0>(agg_2) << endl;
   cout << ref<1>(agg_2) << endl;
   cout << ref<2>(agg_2) << endl;

}
