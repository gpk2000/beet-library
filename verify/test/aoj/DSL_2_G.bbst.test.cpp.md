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


# :heavy_check_mark: test/aoj/DSL_2_G.bbst.test.cpp


[Back to top page](../../../index.html)

* see: [http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_G](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_G)


## Dependencies
* :heavy_check_mark: [bbst/basic/base.cpp](../../../library/bbst/basic/base.cpp.html)
* :heavy_check_mark: [bbst/basic/lazy.cpp](../../../library/bbst/basic/lazy.cpp.html)
* :heavy_check_mark: [tools/fastio.cpp](../../../library/tools/fastio.cpp.html)


## Code
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_G"

#include<bits/stdc++.h>
using namespace std;

#define call_from_test
#include "../../tools/fastio.cpp"
#include "../../bbst/basic/base.cpp"
#include "../../bbst/basic/lazy.cpp"
#undef call_from_test

signed main(){
  using ll = long long;
  int n,q;
  cin>>n>>q;

  using P = pair<ll, ll>;
  auto f=[](P a,P b){return P(a.first+b.first,a.second+b.second);};
  auto g=[](P a,ll b){return P(a.first+b*a.second,a.second);};
  auto h=[](ll a,ll b){return a+b;};

  using Node = NodeBase<P, ll>;
  constexpr size_t LIM = 1e6;
  Lazy<Node, LIM> G(f,g,h,P(0,0),0);
  auto rt=G.build(vector<Node>(n,Node(P(0,1),0)));

  for(int i=0;i<q;i++){
    int c;
    cin>>c;
    if(c==0){
      int s,t,x;
      cin>>s>>t>>x;
      s--;
      rt=G.update(rt,s,t,x);
    }
    if(c==1){
      int s,t;
      cin>>s>>t;
      s--;
      cout<<G.query(rt,s,t).first<<"\n";
    }
  }
  cout<<flush;
  return 0;
}

```

[Back to top page](../../../index.html)
