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


# :heavy_check_mark: test/yosupo/exp_of_formal_power_series.test.cpp


[Back to top page](../../../index.html)

* see: [https://judge.yosupo.jp/problem/exp_of_formal_power_series](https://judge.yosupo.jp/problem/exp_of_formal_power_series)


## Dependencies
* :heavy_check_mark: [convolution/numbertheoretictransform.cpp](../../../library/convolution/numbertheoretictransform.cpp.html)
* :heavy_check_mark: [mod/mint.cpp](../../../library/mod/mint.cpp.html)
* :heavy_check_mark: [polynomial/formalpowerseries.cpp](../../../library/polynomial/formalpowerseries.cpp.html)
* :heavy_check_mark: [tools/fastio.cpp](../../../library/tools/fastio.cpp.html)


## Code
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_formal_power_series"

#include<bits/stdc++.h>
using namespace std;

#define call_from_test
#include "../../tools/fastio.cpp"
#include "../../mod/mint.cpp"
#include "../../convolution/numbertheoretictransform.cpp"
#include "../../polynomial/formalpowerseries.cpp"
#undef call_from_test

signed main(){
  int n;
  cin>>n;

  NTT<2> ntt;
  using M = NTT<2>::M;
  auto conv=[&](auto as,auto bs){return ntt.multiply(as,bs);};
  FormalPowerSeries<M> FPS(conv);

  vector<M> as(n);
  for(int i=0;i<n;i++) cin>>as[i].v;

  auto bs=FPS.exp(as,n);
  for(int i=0;i<n;i++){
    if(i) cout<<" ";
    cout<<bs[i];
  }
  cout<<endl;
  return 0;
}

```

[Back to top page](../../../index.html)
