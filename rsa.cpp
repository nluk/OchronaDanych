#include <iostream>
#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>
#include <memory>
#include <vector>
#include <random>


using ll = long long;


template <typename T>
void print(const std::string& message,T t){
    std::cout<<message<<t<<'\n';
}

class InvModCalculator{
    inline static ll NOT_USED = 0LL;
    struct InvTableRow{
        ll i,q,r,s;
        explicit InvTableRow(ll i=0, ll q=0, ll r=0,ll s=0)
                :i(i),q(q),r(r),s(s){}
    };


    InvTableRow row_min2,row_min1;
    ll a,b;

public:
    InvModCalculator(ll a, ll b):a(a),b(b){
        ll bigger = a > b ? a : b;
        ll bigger_s = bigger == a ? 1LL : 0LL;
        ll smaller = a > b ? b : a;
        ll smaller_s = bigger == a ? 0LL : 1LL;
        row_min2= InvTableRow(1,NOT_USED,bigger,bigger_s);
        row_min1 = InvTableRow(2,NOT_USED,smaller,smaller_s);
    }

    ll calculate_result() {
        while (true) {
            ll i, q, r, s;
            i = row_min1.i + 1LL;
            q = row_min2.r / row_min1.r;
            r = row_min2.r - (q * row_min1.r);
            s = row_min2.s - (q * row_min1.s);
            row_min2 = row_min1;
            row_min1 = InvTableRow(i, q, r, s);
            if (row_min1.r == 0) {
                if (row_min2.r != 1) return -1;
                else return row_min2.s > 0 ? row_min2.s : row_min2.s + b;
            }

        }
    }

};


ll powermod_simple(ll x, ll y, ll p){
    ll res = 1;      // Initialize result

    x = x % p;  // Update x if it is more than or
    // equal to p

    while (y > 0)
    {
        // If y is odd, multiply x with result
        if (y & 1)
            res = (res*x) % p;

        // y must be even now
        y = y>>1; // y = y/2
        x = (x*x) % p;
    }
    return res;
}




bool trial_division(ll p)
{

    if (p <= 1LL) return false;
    if (p == 2LL) return false;

    //ll M = (1LL<<p)-1LL;


    for (ll i = 2LL; i < p; ++i){
        if (p % i == 0LL)
            return false;
    }
    return true;
}

ll findE(ll start = 2LL,ll fi=0LL){
    ll e = start;
    while(e<fi){
        e++;
        if(trial_division(e)) return e;
    }
}

std::vector<ll> rsa_encode(std::string to_encode,ll n,ll e){

    int encode_count;
    if(n>16777216) encode_count = 3;
    else if(n< 16777216 && n> 65536) encode_count = 2;
    else encode_count = 1;

    ll encoded_message_length = to_encode.length()/encode_count;
    if(to_encode.length()%encode_count != 0LL)encoded_message_length++;

    std::vector<ll> encoded(encoded_message_length);
    int currently_encoded_pos = 0;
    int currently_saved_pos = 0;
    while(currently_saved_pos<encoded_message_length){


        ll encoded_total = 0LL;

        for (int i = 0; (i < encode_count) && (currently_encoded_pos< to_encode.length()); ++i) {
            ll m = (ll)to_encode[currently_encoded_pos];
            encoded_total |= m;
            currently_encoded_pos++;
            if(i+1<encode_count) encoded_total<<=8;
        }
        encoded[currently_saved_pos] = powermod_simple(encoded_total,e,n);
        currently_saved_pos++;


    }

    return encoded;
}

std::string rsa_decode(std::vector<ll> encoded,ll n,ll d){

    int encode_count;
    if(n>16777216) encode_count = 3;
    else if(n< 16777216 && n> 65536) encode_count = 2;
    else encode_count = 1;

    ll decoded_message_length = encoded.size()*encode_count;


    std::string decoded;
    decoded.reserve(decoded_message_length);
    int currently_decoded = 0;
    for (int i = 0; i < encoded.size(); ++i) {
        ll encoded_number = encoded[i];
        ll packed_characters = powermod_simple(encoded_number,d,n);
        std::string temp="";
        for (int j = 0; j < encode_count; ++j) {
            ll eight_bits = 255;
            char character = (char)(packed_characters&eight_bits);
            temp = character+temp;
            currently_decoded++;
            packed_characters>>=8;
        }
        decoded+=temp;
    }

    return decoded;
}



ll gcd(ll a, ll b)
{
    if (b == 0LL)
        return a;
    return gcd(b, a % b);

}

int main(int argc, char** argv){
    std::string mode = argv[1];
    if(mode=="--generate"){
        ll p,q;
        while(true){
            std::cin>>p>>q;
            bool p_prime = trial_division(p);
            bool q_prime = trial_division(q);
            if(!p_prime) std::cout<<"P is not  prime\n";
            if(!q_prime) std::cout<<"Q is not prime\n";
            if(q_prime && p_prime) break;
        }

        ll n = p*q;
        ll fi = (p-1LL)*(q-1LL);
        ll e =2LL;
        do{e = findE(e,fi);}while(gcd(e,fi)!=1L);
        ll d = InvModCalculator(e,fi).calculate_result();
        print("fi: ",fi);
        print("n: ",n);
        print("e: ",e);
        print("d: ",d);
    }
    else if(mode=="--encode"){

        ll n,e;
        std::cin>>n>>e;

        std::string line;
        std::cin.ignore();
        std::string file;

        while(std::getline(std::cin,line)){
            if(line.empty())break;
            file+=line;
        }
        auto encoded = rsa_encode(file,n,e);
        std::cout<<encoded.size()<<'\n';
        for(auto& code : encoded)std::cout<<code<<'\n';

    }
    else if(mode=="--decode"){

        ll n,d;
        std::cin>>n>>d;

        ll encoded_size;
        std::cin>>encoded_size;
        std::vector<ll> encoded(encoded_size);
        ll input;
        for (int i = 0; i < encoded_size; ++i) {
            std::cin>>input;
            encoded[i]=input;
        }
        auto decoded = rsa_decode(encoded,n,d);
        std::cout<<"\""<<decoded<<"\"";
    }


}