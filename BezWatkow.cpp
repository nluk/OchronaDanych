#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>
#include <memory>
#include <vector>
using ull = unsigned long long;


static ull left;

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

bool lucas_lehmer(ull p){

    if (p <= 1uLL) return false;
    if (p == 2uLL) return true;

    ull M = (1<<p)-1uLL;
    ull s = 4uLL;
    for(ull i = 0; i < p-2uLL; ++i)
    {
        s = ((s*s) - 2uLL)%M;
    }
     
     return s==0 ? true : false;
}


bool isPrime(ull n) 
{ 
    // Corner cases 
    if (n <= 1)  return false; 
    if (n <= 3)  return true; 
  
    // This is checked so that we can skip  
    // middle five numbers in below loop 
    if (n%2 == 0 || n%3 == 0) return false; 
  
    for (ull i=5; i*i<=n; i=i+6) 
        if (n%i == 0 || n%(i+2) == 0) 
           return false; 
  
    return true; 
} 

void how_many_primes(ull start,ull end,ull& partial_count){
   
    for(ull current = start+1;current<end;current+=2){
        
        if(isPrime(current))++partial_count;
    }

}

int main(int argc,char* argv[]){
    //9-10mil
   // std::ios::sync_with_stdio(false);
   if(argc!=2){
       std::cout<<"--mers for mersenne primes\n--range for calculating primes in range\n";
        std::exit(-1);
   }
   std::string mode(argv[1]);
   if(mode=="--mers"){
       int cases;
    std::cin>>cases;
    for(int i = 1; i < cases; i++)
    {
        ull p;
        std::cin>>p;
        ull M = (1<<p)-1uLL;
        std::cout<<"-------------------------------------------------\n";
        std::cout<<"2^"<<p<<" -1\n";
        std::cout<<"[M] - "<<M<<'\n';
        if(trial_division(p)){
            std::cout<<"Trial division: PRIME\n";
        } else{
            std::cout<<"Trial division: COMPOSITE\n";
        }

        if(lucas_lehmer(p)){
            std::cout<<"Lucas-Lehmer: PRIME\n";
        } else{
            std::cout<<"Lucas-Lehmer: COMPOSITE\n";
        }

    }
   }
    else if(mode=="--range"){
    ull range_start = 11000000uLL;
    ull range_end = 12000000uLL;
    
    std::cin>>range_start>>range_end;
        std::chrono::high_resolution_clock::time_point time1 = std::chrono::high_resolution_clock::now();
    left=range_end-range_start;
    ull count = 0;
    how_many_primes(range_start,range_end,count);
    
    std::chrono::high_resolution_clock::time_point time2 = std::chrono::high_resolution_clock::now();
    
   
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( time2 - time1 ).count();
    
    std::cout<<"\nFound "<<count<<" primes, took: "<<duration<<" milliseconds";
    }


    


}