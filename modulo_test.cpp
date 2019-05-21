#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <bitset>
#include <limits>
#include <algorithm>
#include <map>

using ulolo = unsigned long long;


ulolo powermod_simple(ulolo a, ulolo b, ulolo n){
    ulolo total = a%n;
    ulolo current_exp = 1;
    while(current_exp!=b){
        total = ((total%n) * (a%n))%n;
        current_exp++;
    }

    return total;
    
}

ulolo powermod_fast(ulolo a, ulolo b,ulolo n) {
    ulolo rest=1uLL;
    while(b>0uLL) {
       if(b&1uLL) rest=(rest*a)%n;
       a=(a*a)%n;
       b>>=1uLL;
    }
    return rest%n;
}


int main(int argc, char** argv){

    if(argc!=2) {
        std::cout<<"\n--simple\n--fast\nThen number of cases, and A,B,N for every case \n";
        std::exit(0);
    }
    std::string mode(argv[1]);

    ulolo cases;
    std::cin>>cases;
    for(ulolo i = 0; i < cases; ++i)
    {
        ulolo A,B,N;
        std::cin>>A>>B>>N;
        if(mode=="--simple"){
        std::cout<<powermod_simple(A,B,N)<<'\n';
        }
        else if(mode=="--fast"){
        std::cout<<powermod_fast(A,B,N)<<'\n';
        }
    }
    
    

   
    
    

    return 0;
}