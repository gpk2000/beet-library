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


# :heavy_check_mark: test/yosupo/vertex_add_subtree_sum.test.cpp


[Back to top page](../../../index.html)

* see: [https://judge.yosupo.jp/problem/vertex_add_subtree_sum](https://judge.yosupo.jp/problem/vertex_add_subtree_sum)


## Dependencies
* :heavy_check_mark: [datastructure/binaryindexedtree.cpp](../../../library/datastructure/binaryindexedtree.cpp.html)
* :heavy_check_mark: [tools/fastio.cpp](../../../library/tools/fastio.cpp.html)
* :heavy_check_mark: [tree/eulertourforvertex.cpp](../../../library/tree/eulertourforvertex.cpp.html)


## Code
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"

#include<bits/stdc++.h>
using namespace std;

#define call_from_test
#include "../../tools/fastio.cpp"
#include "../../tree/eulertourforvertex.cpp"
#include "../../datastructure/binaryindexedtree.cpp"
#undef call_from_test

signed main(){
  int n,q;
  cin>>n>>q;
  vector<int> as(n);
  for(int i=0;i<n;i++) cin>>as[i];

  EulerTourForVertex G(n);
  for(int i=1;i<n;i++){
    int p;
    cin>>p;
    G.add_edge(p,i);
  }
  G.build(0);

  BIT<long long> bit(n);
  for(int i=0;i<n;i++)
    bit.add0(G.idx(i),as[i]);

  for(int i=0;i<q;i++){
    int t;
    cin>>t;
    if(t==0){
      int u,x;
      cin>>u>>x;
      bit.add0(G.idx(u),x);
    }
    if(t==1){
      int u;
      cin>>u;
      G.exec(u,[&](int l,int r){cout<<bit.query0(l,r)<<"\n";});
    }
  }
  cout<<flush;
  return 0;
}

```

[Back to top page](../../../index.html)
