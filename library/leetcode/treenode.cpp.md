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


# :warning: leetcode/treenode.cpp
* category: leetcode


[Back to top page](../../index.html)



## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
using Int = long long;
template<typename T1,typename T2> inline void chmin(T1 &a,T2 b){if(a>b) a=b;}
template<typename T1,typename T2> inline void chmax(T1 &a,T2 b){if(a<b) a=b;}
//BEGIN CUT HERE

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

int dfs(TreeNode* v,int &k,vector<vector<int> > &G,vector<int> &x){
  if(!v) return -1;
  int s=k++;
  x.emplace_back(v->val);
  G.emplace_back(vector<int>());
  int a=dfs(v->left,k,G,x);
  int b=dfs(v->right,k,G,x);    
  if(~a){
    G[s].emplace_back(a);
    G[a].emplace_back(s);
  }
  if(~b){
    G[s].emplace_back(b);
    G[b].emplace_back(s);
  } 
  return s;
}

void build(TreeNode* v,vector<vector<int> > &G,vector<int> &x){
  assert(G.empty());
  int k=0;
  dfs(v,k,G,x);
}

//END CUT HERE

//INSERT ABOVE HERE
signed main(){
  return 0;
}

```

[Back to top page](../../index.html)
