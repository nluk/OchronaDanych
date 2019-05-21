#include <iostream>
#include <vector>

using ll = long long;

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


int main(){

    ll a,b;
    get(a,"Enter a: ");
    get(b,"Enter b: ");
    InvModCalculator invmod(a,b);
    ll result = invmod.calculate_result();
    std::cout<<result;


return 0;

}