<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :warning: mod/order.cpp
* category: mod


[Back to top page](../../index.html)



## Dependencies
* :heavy_check_mark: [math/factorize.cpp](../math/factorize.cpp.html)
* :heavy_check_mark: [mod/pow.cpp](pow.cpp.html)
* :heavy_check_mark: [tools/fastio.cpp](../tools/fastio.cpp.html)


## Verified
* :heavy_check_mark: [test/aoj/3062.test.cpp](../../verify/test/aoj/3062.test.cpp.html)


## Code
```cpp
#ifndef call_from_test
#include<bits/stdc++.h>
using namespace std;

#define call_from_test
#include "../tools/fastio.cpp"
#include "../math/factorize.cpp"
#include "pow.cpp"
#undef call_from_test

#endif
//BEGIN CUT HERE
template<typename T>
T order(T x,T MOD){
  static map<T, vector<T>> dp;
  vector<T> &ps=dp[MOD];
  if(ps.empty()){
    auto fs=factorize(MOD-1);
    for(auto p:fs) ps.emplace_back(p.first);
  }
  T res=MOD-1;
  for(T p:ps){
    while(res%p==0){
      if(mod_pow(x,res/p,MOD)!=1) break;
      res/=p;
    }
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

```

[Back to top page](../../index.html)
