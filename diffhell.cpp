#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>
#include <memory>
#include <vector>
using ull = unsigned long long;


ull powermod_fast(ull a, ull b,ull n) {
    ull total = a%n;
    ull current_exp = 1uLL;
    while(current_exp!=b){
        total = ((total%n) * (a%n))%n;
        current_exp++;
    }

    return total%n;
}

bool trial_division(ull p)
{

    if (p <= 1uLL) return false;
    if (p == 2uLL) return true;

    ull M = (1<<p)-1uLL;


    for (ull i = 2; i <= sqrt(M)+1uLL; ++i){
        if (M % i == 0)
            return false;
    }
    return true;
}


template <typename T>
void get(T& t,const char* message){
    printf(message);
    std::cin>>t;
}
template <typename T>
void put(T& t,const char* message){
    printf(message);
    std::cout<<t<<'\n';
}



int main(){
    ull p,g,a,B;
    do{
        
        get(p,"p: ");
        if(trial_division(p)) break;
        else std::cout<<"p is not prime\n";
    
    }while(true);
    
    get(g,"g: ");
    get(a,"a: ");

    ull A = powermod_fast(g,a,p);
    put(A,"A: ");

    
    get(B,"B: ");
    ull secret = powermod_fast(B,a,p);
    put(secret,"Secret: ");
   

    
}