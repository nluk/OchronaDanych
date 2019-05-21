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
  
    if (n == 1) {
        return false;
    }

    int i = 2;
    
    while (i*i <= n) {
        if (n % i == 0) return false;
        ++i;
    }
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
    ull hardware_threads = std::thread::hardware_concurrency();
   
    left = range_end-range_start;
    ull per_thread_block = (range_end-range_start)/hardware_threads;
    left/=2;
    ull start = range_start;
    ull end = start  + per_thread_block;
    std::vector<unsigned long long> partial_count{0,0,0,0};
    std::vector<std::thread> thread_pool(hardware_threads-1);
    for(int i = 0; i < thread_pool.size();++i){
        thread_pool[i]=std::thread{how_many_primes,start,end,std::ref<ull>(partial_count[i])};
        start+=per_thread_block;
        end+=per_thread_block;
    }
    how_many_primes(start,end,partial_count[hardware_threads-1]);
    for(auto& t : thread_pool) t.join();
    std::chrono::high_resolution_clock::time_point time2 = std::chrono::high_resolution_clock::now();
    
    ull total_count = 0uLL;
    for(auto count : partial_count) total_count+=count;
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( time2 - time1 ).count();
    
    std::cout<<"\nFound "<<total_count<<" primes, took: "<<duration<<" milliseconds";
    }



    


}