---
layout: default
---

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


# :heavy_check_mark: test/yosupo/dynamic_tree_vertex_set_path_composite.toptree.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#0b58406058f6619a0f31a172defc0230">test/yosupo</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yosupo/dynamic_tree_vertex_set_path_composite.toptree.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-01 17:45:41+09:00


* see: <a href="https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite">https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/math/linearfunction.cpp.html">math/linearfunction.cpp</a>
* :heavy_check_mark: <a href="../../../library/math/twoway.cpp.html">math/twoway.cpp</a>
* :heavy_check_mark: <a href="../../../library/mod/mint.cpp.html">mod/mint.cpp</a>
* :heavy_check_mark: <a href="../../../library/toptree/toptree.cpp.html">toptree/toptree.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite"

#include <bits/stdc++.h>
using namespace std;

#define call_from_test
#include "../../mod/mint.cpp"
#include "../../math/linearfunction.cpp"
#include "../../math/twoway.cpp"
#include "../../toptree/toptree.cpp"
#undef call_from_test

using M = Mint<int, 998244353>;
using L = LinearFunction<M>;
using P = TwoWay<L>;

struct Vertex{
  void* handle;
  L val;
  Vertex(L val=L()):handle(nullptr),val(val){}
};

struct Cluster{
  P res;
  Cluster(){}
  Cluster(L val):res(val){}
  Cluster(P res):res(res){}
  void toggle(){swap(res.x,res.y);}
  static Cluster compress(Cluster x,Vertex* v,Cluster y){
    return Cluster(x.res*P(v->val)*y.res);
  }
  static Cluster rake(Cluster x,Cluster){
    return x;
  }
};

signed main(){
  cin.tie(0);
  ios::sync_with_stdio(0);
  const char newl = '\n';

  const size_t LIM = 1e6;
  TopTree<Vertex, Cluster, LIM> G(Cluster(L(1,0)));

  int n,q;
  cin>>n>>q;
  vector<int> as(n),bs(n);
  for(int i=0;i<n;i++) cin>>as[i]>>bs[i];

  vector<Vertex*> vs(n);
  for(int i=0;i<n;i++)
    vs[i]=G.create(Vertex(L(as[i],bs[i])));

  for(int i=1;i<n;i++){
    int u,v;
    cin>>u>>v;
    G.link(vs[u],Cluster(L(1,0)),vs[v]);
  }

  for(int i=0;i<q;i++){
    int t;
    cin>>t;

    if(t==0){
      int u,v,w,x;
      cin>>u>>v>>w>>x;

      G.cut(vs[u],vs[v]);
      G.link(vs[w],Cluster(L(1,0)),vs[x]);
    }

    if(t==1){
      int p,c,d;
      cin>>p>>c>>d;
      G.set_vertex(vs[p],Vertex(L(c,d)));
    }

    if(t==2){
      int u,v,x;
      cin>>u>>v>>x;
      if(u==v){
        auto res=vs[u]->val;
        cout<<res(x)<<newl;
      }else{
        auto res=G.get_path(vs[u],vs[v]).res.x;
        res=vs[u]->val*res*vs[v]->val;
        cout<<res(x)<<newl;
      }
    }
  }
  return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yosupo/dynamic_tree_vertex_set_path_composite.toptree.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite"

#include <bits/stdc++.h>
using namespace std;

#define call_from_test
#line 2 "mod/mint.cpp"

#ifndef call_from_test
#line 5 "mod/mint.cpp"
using namespace std;
#endif

//BEGIN CUT HERE
template<typename T,T MOD = 1000000007>
struct Mint{
  static constexpr T mod = MOD;
  T v;
  Mint():v(0){}
  Mint(signed v):v(v){}
  Mint(long long t){v=t%MOD;if(v<0) v+=MOD;}

  Mint pow(long long k){
    Mint res(1),tmp(v);
    while(k){
      if(k&1) res*=tmp;
      tmp*=tmp;
      k>>=1;
    }
    return res;
  }

  static Mint add_identity(){return Mint(0);}
  static Mint mul_identity(){return Mint(1);}

  Mint inv(){return pow(MOD-2);}

  Mint& operator+=(Mint a){v+=a.v;if(v>=MOD)v-=MOD;return *this;}
  Mint& operator-=(Mint a){v+=MOD-a.v;if(v>=MOD)v-=MOD;return *this;}
  Mint& operator*=(Mint a){v=1LL*v*a.v%MOD;return *this;}
  Mint& operator/=(Mint a){return (*this)*=a.inv();}

  Mint operator+(Mint a) const{return Mint(v)+=a;}
  Mint operator-(Mint a) const{return Mint(v)-=a;}
  Mint operator*(Mint a) const{return Mint(v)*=a;}
  Mint operator/(Mint a) const{return Mint(v)/=a;}

  Mint operator-() const{return v?Mint(MOD-v):Mint(v);}

  bool operator==(const Mint a)const{return v==a.v;}
  bool operator!=(const Mint a)const{return v!=a.v;}
  bool operator <(const Mint a)const{return v <a.v;}

  static Mint comb(long long n,int k){
    Mint num(1),dom(1);
    for(int i=0;i<k;i++){
      num*=Mint(n-i);
      dom*=Mint(i+1);
    }
    return num/dom;
  }
};
template<typename T,T MOD> constexpr T Mint<T, MOD>::mod;
template<typename T,T MOD>
ostream& operator<<(ostream &os,Mint<T, MOD> m){os<<m.v;return os;}
//END CUT HERE
#ifndef call_from_test

//INSERT ABOVE HERE
signed ABC127_E(){
  cin.tie(0);
  ios::sync_with_stdio(0);

  int h,w,k;
  cin>>h>>w>>k;
  using M = Mint<int>;

  M ans{0};
  for(int d=1;d<h;d++)
    ans+=M(d)*M(h-d)*M(w)*M(w);

  for(int d=1;d<w;d++)
    ans+=M(d)*M(w-d)*M(h)*M(h);

  ans*=M::comb(h*w-2,k-2);
  cout<<ans<<endl;
  return 0;
}
/*
  verified on 2019/06/12
  https://atcoder.jp/contests/abc127/tasks/abc127_e
*/

signed main(){
  //ABC127_E();
  return 0;
}
#endif
#line 2 "math/linearfunction.cpp"

#ifndef call_from_test
#line 5 "math/linearfunction.cpp"
using namespace std;
#endif
//BEGIN CUT HERE
// a * x + b
template<typename T>
struct LinearFunction{
  T a,b;
  LinearFunction():a(0),b(0){}
  LinearFunction(T a,T b):a(a),b(b){}

  using LF = LinearFunction;
  static LF add_identity(){return LF(T(0),T(0));}
  static LF mul_identity(){return LF(T(1),T(0));}
  LF& operator+=(const LF &o){
    a+=o.a;b+=o.b;
    return *this;
  }
  LF& operator*=(const LF &o){
    a=a*o.a;
    b=b*o.a+o.b;
    return *this;
  }
  LF operator+(const LF &o)const{return LF(*this)+=o;}
  LF operator*(const LF &o)const{return LF(*this)*=o;}

  T operator()(T x) const{return a*x+b;}
};
//END CUT HERE
#ifndef call_from_test
//INSERT ABOVE HERE
signed main(){
  return 0;
}
#endif
#line 2 "math/twoway.cpp"

#ifndef call_from_test
#line 5 "math/twoway.cpp"
using namespace std;
#endif
//BEGIN CUT HERE
template<typename T>
struct TwoWay{
  T x,y;
  TwoWay(T z=T()):x(z),y(z){}
  TwoWay(T x,T y):x(x),y(y){}
  TwoWay operator+(const TwoWay &o)const{return TwoWay(x+o.x,o.y+y);}
  TwoWay operator*(const TwoWay &o)const{return TwoWay(x*o.x,o.y*y);}
};
//END CUT HERE
#ifndef call_from_test
//INSERT ABOVE HERE
signed main(){
  return 0;
}
#endif
#line 2 "toptree/toptree.cpp"

#ifndef call_from_test
#line 5 "toptree/toptree.cpp"
using namespace std;
#endif
//BEGIN CUT HERE
template<typename Vertex, typename Cluster, size_t LIM>
struct TopTree{
  enum Type { Compress, Rake, Edge };
  struct Node{
    Vertex* vs[2];
    Cluster dat;
    Node* p;
    Node* q;
    Node* ch[2];
    bool rev,guard;
    Type type;
    Node():p(nullptr),q(nullptr),rev(false),guard(false){}
  };

  static array<Vertex, LIM> pool_v;
  static array<Node, LIM> pool_c;
  size_t ptr_v,ptr_c;

  Cluster id;
  TopTree(Cluster id=Cluster()):ptr_v(0),ptr_c(0),id(id){}

  inline Vertex* create(Vertex v=Vertex()){
    auto t=&pool_v[ptr_v++];
    auto dummy=&pool_v[ptr_v++];
    *t=v;
    link(t,id,dummy);
    return t;
  }

  inline Node* edge(Vertex* u,Cluster w,Vertex* v){
    auto t=&(pool_c[ptr_c++]);
    t->vs[0]=u;t->vs[1]=v;t->dat=w;t->type=Type::Edge;
    return pushup(t);
  }

  inline Node* compress(Node* l,Node* r){
    auto t=&(pool_c[ptr_c++]);
    t->ch[0]=l;t->ch[1]=r;t->type=Type::Compress;
    return pushup(t);
  }

  inline Node* rake(Node* l,Node* r){
    auto t=&(pool_c[ptr_c++]);
    t->ch[0]=l;t->ch[1]=r;t->type=Type::Rake;
    return pushup(t);
  }

  int parent_dir(Node* t){
    Node* p=t->p;
    if(!p) return -1;
    if(p->guard) return -1;
    if(p->ch[0]==t) return 0;
    if(p->ch[1]==t) return 1;
    return -1;
  }

  int parent_dir_ignore_guard(Node* t){
    Node* p=t->p;
    if(!p) return -1;
    if(p->ch[0]==t) return 0;
    if(p->ch[1]==t) return 1;
    return -1;
  }

  inline Node* pushup(Node* const t){
    Node* const l=t->ch[0];
    Node* const r=t->ch[1];

    if(t->type==Type::Compress){
      assert(l->vs[1]==r->vs[0]);
      t->vs[0]=l->vs[0];
      t->vs[1]=r->vs[1];

      Cluster lf=l->dat;
      if(t->q){
        assert(l->vs[1]==t->q->vs[1]);
        lf=Cluster::rake(l->dat,t->q->dat);
      }
      t->dat=Cluster::compress(lf,r->vs[0],r->dat);

      l->vs[1]->handle=t;
    }

    if(t->type==Type::Rake){
      propagate(t);
      assert(l->vs[1]==r->vs[1]);
      t->vs[0]=l->vs[0];
      t->vs[1]=l->vs[1];
      t->dat=Cluster::rake(l->dat,r->dat);
    }else{
      if(!t->p){
        t->vs[0]->handle=t;
        t->vs[1]->handle=t;
      }else if(t->p->type==Type::Compress){
        if(parent_dir(t)==-1)
          t->vs[0]->handle=t;
      }else if(t->p->type==Type::Rake){
        t->vs[0]->handle=t;
      }
    }
    return t;
  }

  inline void toggle(Node* t){
    if(t->type==Type::Edge){
      swap(t->vs[0],t->vs[1]);
      t->dat.toggle();
    }else if(t->type==Type::Compress){
      swap(t->vs[0],t->vs[1]);
      t->dat.toggle();
      t->rev^=true;
    }else if(t->type==Type::Rake){
    }else abort();
  }

  inline void propagate(Node* t){
    if(t->type==Type::Compress){
      if(t->rev){
        assert(t->ch[0] and t->ch[1]);
        swap(t->ch[0],t->ch[1]);
        toggle(t->ch[0]);
        toggle(t->ch[1]);
        t->rev=false;
      }
    }
  }

  void set_toggle(Node* v){
    toggle(v);propagate(v);
  }

  void pushdown(Node* t){
    if(!t) return;
    pushdown(t->p);
    propagate(t);
  }

  void rotate(Node* t,Node* x,size_t dir){
    Node* y=x->p;
    int par=parent_dir_ignore_guard(x);
    propagate(t->ch[dir]);
    x->ch[dir^1]=t->ch[dir];
    t->ch[dir]->p=x;
    t->ch[dir]=x;
    x->p=t;
    t->p=y;
    if(~par) y->ch[par]=t;
    else if(y and y->type==Type::Compress) y->q=t;
    pushup(x);pushup(t);
    if(y and !y->guard) pushup(y);
  }

  void splay(Node* t){
    assert(t->type!=Type::Edge);
    propagate(t);

    while(~parent_dir(t)){
      Node* q=t->p;
      if(q->type!=t->type) break;
      if(~parent_dir(q) and q->p and q->p->type==q->type){
        Node* r=q->p;
        if(r->p) propagate(r->p);
        propagate(r);propagate(q);propagate(t);
        int qt_dir=parent_dir(t);
        int rq_dir=parent_dir(q);
        if(rq_dir==qt_dir){
          rotate(q,r,rq_dir^1);
          rotate(t,q,qt_dir^1);
        }else{
          rotate(t,q,qt_dir^1);
          rotate(t,r,rq_dir^1);
        }
      }else{
        if(q->p) propagate(q->p);
        propagate(q);propagate(t);
        int qt_dir=parent_dir(t);
        rotate(t,q,qt_dir^1);
      }
    }
  }

  Node* expose(Node* t){
    pushdown(t);
    while(true){
      assert(t->type!=Type::Rake);
      if(t->type==Type::Compress) splay(t);
      Node* n=nullptr;
      {
        Node* p=t->p;
        if(!p) break;
        if(p->type==Type::Rake){
          propagate(p);
          splay(p);
          n=p->p;
        }
        if(p->type==Type::Compress){
          propagate(p);
          if(p->guard and ~parent_dir_ignore_guard(t)) break;
          n=p;
        }
      }
      splay(n);
      int dir=parent_dir_ignore_guard(n);
      if(dir==-1 or n->p->type==Type::Rake) dir=0;

      Node* const c=n->ch[dir];
      if(dir==1){
        set_toggle(c);
        set_toggle(t);
      }
      int n_dir=parent_dir(t);
      if(~n_dir){
        Node* const r=t->p;
        propagate(c);
        propagate(r);
        r->ch[n_dir]=c;
        c->p=r;
        n->ch[dir]=t;
        t->p=n;
        pushup(c);pushup(r);pushup(t);pushup(n);
        splay(r);
      }else{
        propagate(c);
        n->q=c;
        c->p=n;
        n->ch[dir]=t;
        t->p=n;
        pushup(c);pushup(t);pushup(n);
      }
      if(t->type==Type::Edge) t=n;
    }
    return t;
  }

  Node* expose(Vertex* v){
    return expose((Node*)(v->handle));
  }

  void soft_expose(Vertex* u,Vertex* v){
    pushdown((Node*)u->handle);
    pushdown((Node*)v->handle);
    Node* rt=expose(u);

    if(u->handle==v->handle){
      if(rt->vs[1]==u or rt->vs[0]==v)
        set_toggle(rt);
      return;
    }

    rt->guard=true;
    Node* soft=expose(v);
    rt->guard=false;

    pushup(rt);
    if(parent_dir(soft)==0) set_toggle(rt);
  }

  void bring(Node* rt){
    Node* rk=rt->q;
    if(!rk){
      Node* ll=rt->ch[0];
      ll->p=nullptr;
      pushup(ll);
    }else if(rk->type==Type::Compress or rk->type==Type::Edge){
      propagate(rk);

      Node* nr=rk;
      set_toggle(nr);
      rt->ch[1]=nr;
      nr->p=rt;
      rt->q=nullptr;

      pushup(nr);pushup(rt);
    }else if(rk->type==Type::Rake){
      propagate(rk);
      while(rk->ch[1]->type==Type::Rake){
        propagate(rk->ch[1]);
        rk=rk->ch[1];
      }
      pushdown(rk);

      rt->guard=true;
      splay(rk);
      rt->guard=false;

      Node* ll=rk->ch[0];
      Node* rr=rk->ch[1];
      propagate(ll);
      set_toggle(rr);

      rt->ch[1]=rr;
      rr->p=rt;

      rt->q=ll;
      ll->p=rt;

      pushup(ll);pushup(rr);pushup(rt);
    }
  }

  Node* link(Vertex* u,Cluster w,Vertex* v){
    if(!u->handle and !v->handle) return edge(u,w,v);

    Node* nnu=(Node*)u->handle;
    Node* nnv=(Node*)v->handle;
    Node* ee=edge(u,w,v);
    Node* ll=nullptr;

    if(!nnv) ll=ee;
    else{
      Node* vv=expose(nnv);
      propagate(vv);
      if(vv->vs[1]==v) set_toggle(vv);
      if(vv->vs[0]==v){
        Node* nv=compress(ee,vv);
        ee->p=nv;
        pushup(ee);
        vv->p=nv;
        pushup(vv);pushup(nv);
        ll=nv;
      }else{
        Node* nv=vv;
        Node* ch=nv->ch[0];
        propagate(ch);
        nv->ch[0]=ee;
        ee->p=nv;
        pushup(ee);

        Node* bt=nv->q;
        Node* rk=nullptr;
        if(bt){
          propagate(bt);
          rk=rake(bt,ch);
          bt->p=rk;
          ch->p=rk;
          pushup(bt);pushup(ch);
        }else{
          rk=ch;
        }
        nv->q=rk;
        rk->p=nv;
        pushup(rk);pushup(nv);
        ll=nv;
      }
    }

    if(nnu){
      Node* uu=expose(nnu);
      propagate(uu);
      if(uu->vs[0]==u) set_toggle(uu);
      if(uu->vs[1]==u){
        Node* tp=compress(uu,ll);
        uu->p=tp;
        ll->p=tp;
        pushup(uu);pushup(ll);pushup(tp);
      }else{
        Node* nu=uu;
        Node* ch=nu->ch[1];
        toggle(ch);
        propagate(ch);

        nu->ch[1]=ll;
        ll->p=nu;
        pushup(ll);

        Node* al=nu->q;
        Node* rk=nullptr;
        if(al){
          propagate(al);
          rk=rake(al,ch);
          al->p=rk;
          ch->p=rk;
          pushup(al);pushup(ch);
        }else{
          rk=ch;
        }
        nu->q=rk;
        rk->p=nu;
        pushup(rk);pushup(nu);
      }
    }
    return ee;
  }

  void cut(Vertex* u,Vertex *v){
    soft_expose(u,v);
    Node* rt=(Node*)u->handle;
    propagate(rt);
    Node* rr=rt->ch[1];
    rr->p=nullptr;
    set_toggle(rr);
    bring(rr);bring(rt);
  }

  Node* path(Vertex* u,Vertex* v){
    assert(u!=v);
    soft_expose(u,v);
    Node* rt=(Node*)u->handle;
    propagate(rt);
    propagate(rt->ch[1]);
    return rt->ch[1]->ch[0];
  }

  void set_vertex(Vertex* u,Vertex v){
    auto t=expose(u);
    *u=v;
    pushup(t);
  }

  void set_edge(Vertex* u,Vertex* v,const Cluster &w){
    auto t=path(u,v);
    assert(t->type==Type::Edge);
    t->dat=w;
    while(t) pushup(t),t=t->p;
  }

  Cluster get_path(Vertex* u,Vertex* v){
    return path(u,v)->dat;
  }

  Cluster get_subtree(Vertex* v){
    return expose(v)->dat;
  }

  // subtree of v when p is root
  Cluster get_subtree(Vertex* p,Vertex* v){
    Node* t=path(p,v);
    Cluster res=t->p->ch[1]->dat;
    res.toggle();
    Node* rk=t->p->q;
    if(t->p->q){
      assert(rk->vs[1]==t->p->ch[1]->vs[0]);
      res=Cluster::rake(res,rk->dat);
    }
    return res;
  }
};
template<typename Vertex, typename Cluster, size_t LIM>
array<Vertex, LIM> TopTree<Vertex, Cluster, LIM>::pool_v;
template<typename Vertex, typename Cluster, size_t LIM>
array<typename TopTree<Vertex, Cluster, LIM>::Node, LIM>
TopTree<Vertex, Cluster, LIM>::pool_c;
//END CUT HERE
#ifndef call_from_test
//INSERT ABOVE HERE
signed main(){
  return 0;
}
#endif
#line 11 "test/yosupo/dynamic_tree_vertex_set_path_composite.toptree.test.cpp"
#undef call_from_test

using M = Mint<int, 998244353>;
using L = LinearFunction<M>;
using P = TwoWay<L>;

struct Vertex{
  void* handle;
  L val;
  Vertex(L val=L()):handle(nullptr),val(val){}
};

struct Cluster{
  P res;
  Cluster(){}
  Cluster(L val):res(val){}
  Cluster(P res):res(res){}
  void toggle(){swap(res.x,res.y);}
  static Cluster compress(Cluster x,Vertex* v,Cluster y){
    return Cluster(x.res*P(v->val)*y.res);
  }
  static Cluster rake(Cluster x,Cluster){
    return x;
  }
};

signed main(){
  cin.tie(0);
  ios::sync_with_stdio(0);
  const char newl = '\n';

  const size_t LIM = 1e6;
  TopTree<Vertex, Cluster, LIM> G(Cluster(L(1,0)));

  int n,q;
  cin>>n>>q;
  vector<int> as(n),bs(n);
  for(int i=0;i<n;i++) cin>>as[i]>>bs[i];

  vector<Vertex*> vs(n);
  for(int i=0;i<n;i++)
    vs[i]=G.create(Vertex(L(as[i],bs[i])));

  for(int i=1;i<n;i++){
    int u,v;
    cin>>u>>v;
    G.link(vs[u],Cluster(L(1,0)),vs[v]);
  }

  for(int i=0;i<q;i++){
    int t;
    cin>>t;

    if(t==0){
      int u,v,w,x;
      cin>>u>>v>>w>>x;

      G.cut(vs[u],vs[v]);
      G.link(vs[w],Cluster(L(1,0)),vs[x]);
    }

    if(t==1){
      int p,c,d;
      cin>>p>>c>>d;
      G.set_vertex(vs[p],Vertex(L(c,d)));
    }

    if(t==2){
      int u,v,x;
      cin>>u>>v>>x;
      if(u==v){
        auto res=vs[u]->val;
        cout<<res(x)<<newl;
      }else{
        auto res=G.get_path(vs[u],vs[v]).res.x;
        res=vs[u]->val*res*vs[v]->val;
        cout<<res(x)<<newl;
      }
    }
  }
  return 0;
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>
