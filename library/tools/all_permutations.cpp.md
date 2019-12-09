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


# :warning: tools/all_permutations.cpp
* category: tools


[Back to top page](../../index.html)



## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
using Int = long long;
template<typename T1,typename T2> inline void chmin(T1 &a,T2 b){if(a>b) a=b;}
template<typename T1,typename T2> inline void chmax(T1 &a,T2 b){if(a<b) a=b;}
//BEGIN CUT HERE
template<typename F>
void all_permutations(int n,F f){
  vector<int> vs(n);
  iota(vs.begin(),vs.end(),0);
  do f(vs); while(next_permutation(vs.begin(),vs.end()));
}
//END CUT HERE
//INSERT ABOVE HERE
signed ABC054_C(){
  int n,m;
  cin>>n>>m;
  int es[10][10]={};
  for(int i=0;i<m;i++){
    int a,b;
    cin>>a>>b;
    a--;b--;
    es[a][b]=es[b][a]=1;
  }
  int ans=0;
  auto f=
    [&](const auto &vs){
      if(!es[0][vs[0]+1]) return;
      for(int i=0;i+1<n-1;i++)
        if(!es[vs[i]+1][vs[i+1]+1]) return;
      ans++;
    };
  all_permutations(n-1,f);
  cout<<ans<<endl;
  return 0;
}
/*
  verified on 2019/05/19
  https://atcoder.jp/contests/abc054/tasks/abc054_c
*/
signed main(){
  ABC054_C();
  return 0;
}

```

[Back to top page](../../index.html)
