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
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :heavy_check_mark: test/aoj/ALDS1_14_B.test.cpp


[Back to top page](../../../index.html)

* see: [http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B)


## Dependencies
* :heavy_check_mark: [string/rollinghash.cpp](../../../library/string/rollinghash.cpp.html)


## Code
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B"

#include<bits/stdc++.h>
using namespace std;

#define call_from_test
#include "../../string/rollinghash.cpp"
#undef call_from_test

signed main(){
  cin.tie(0);
  ios::sync_with_stdio(0);

  string t,p;
  cin>>t>>p;
  using ll = long long;
  const ll MOD = 1e9+7;
  const ll B = 1777771;
  using RH = RollingHash<ll, MOD, B>;

  RH rt(t),rp(p);
  for(int i=0;i<(int)t.size()-(int)p.size()+1;i++)
    if(rt.find(i,i+p.size())==rp.find(0,p.size())) cout<<i<<"\n";

  cout<<flush;
  return 0;
}

```

[Back to top page](../../../index.html)
