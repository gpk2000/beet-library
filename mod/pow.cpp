#ifndef call_from_test
#include<bits/stdc++.h>
using namespace std;
#endif
//BEGIN CUT HERE
template<typename T>
T mod_pow(T a,long long n,T mod){
  using ll = long long;
  T res(1);
  while(n){
    if(n&1) res=(ll)res*a%mod;
    a=(ll)a*a%mod;
    n>>=1;
  }
  return res;
}
//END CUT HERE
#ifndef call_from_test
//INSERT ABOVE HERE
signed main(){
  return 0;
}
#endif
