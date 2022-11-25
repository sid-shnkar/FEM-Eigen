#ifndef NUMERICAL_H
#define NUMERICAL_H
#include <cstdio>
#include <iostream>
  
//#pragma once
/**
 * Domain class containing variables : P, N, A0, L, E
**/

template <typename T>
class Domain {
private:
	T P;
    T A0;
    T L;
    T E;
	int N;

public:
    //constructor function
	Domain(T P_arg, T A0_arg, T L_arg, T E_arg, int N_arg){
     P=P_arg;
    A0=A0_arg;
    L=L_arg;
    E=E_arg;
    N=N_arg;
    }
    // getter functions to return required private variables
    T getP(){
    return P;
    }
    T getA0(){
     return A0;
    } 
    T getL(){
     return L;
    }
    T getE(){
    return E;
    }
    T getN(){
    return N;
    }
    // method to print all the private variables
    void print(){
    std::cout <<"P value: "<<P<<std::endl;
    std::cout <<"A0 value: "<<A0<<std::endl;
    std::cout <<"L value: "<<L<<std::endl;
    std::cout <<"E value: "<<E<<std::endl;
    std::cout <<"N value: "<<N<<std::endl;
    }
};
  
#endif
