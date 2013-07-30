#include <iostream>
#include <typeinfo>

template<typename T>
struct GetTypeN;

template<typename T, int N>
struct GetTypeN<T[N]>
{
   void Get_N()
   {
      std::cout << N << std::endl;
   }
};

template<int>
struct GetInt
{};


template<template<int>class ARG = GetInt, int N>
void func(ARG<N>){
   std::cout << N << std::endl;
}

int main(){

   int a[10];

//   GetType<decltype(&a)> gettype;
   func<GetInt>((GetInt<10>()));

}
