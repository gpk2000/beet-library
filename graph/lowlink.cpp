#pragma once

#ifndef call_from_test
#include <bits/stdc++.h>
using namespace std;
#endif
//BEGIN CUT HERE
struct LowLink{
  int n,pos;
  vector<int> ord,low,par,blg,num;
  vector<vector<int> > G,C,T;
  vector<vector<pair<int, int> > > E;

  vector<int> ap;
  vector<pair<int, int> > bs,cand;

  LowLink(int n):n(n),pos(0),ord(n,-1),low(n),
                 par(n,-1),blg(n,-1),num(n,1),G(n){}

  void add_edge(int u,int v){
    G[u].emplace_back(v);
    G[v].emplace_back(u);
  }

  bool is_bridge(int u,int v){
    if(ord[u]>ord[v]) swap(u,v);
    return ord[u]<low[v];
  }

  void dfs(int v){
    ord[v]=low[v]=pos++;
    int dup=0;
    for(int u:G[v]){
      if(u==par[v]){
        if(dup) low[v]=min(low[v],ord[u]);
        dup=1;
        continue;
      }
      if(ord[u]<ord[v])
        cand.emplace_back(min(u,v),max(u,v));
      if(~ord[u]){
        low[v]=min(low[v],ord[u]);
        continue;
      }
      par[u]=v;
      dfs(u);
      num[v]+=num[u];
      low[v]=min(low[v],low[u]);
      if(is_bridge(u,v)) bs.emplace_back(u,v);
      if(low[u]>=ord[v]){
        E.emplace_back();
        while(1){
          auto e=cand.back();
          cand.pop_back();
          E.back().emplace_back(e);
          if(make_pair(min(u,v),max(u,v))==e) break;
        }
      }
    }
  }

  void fill_component(int v){
    C[blg[v]].emplace_back(v);
    for(int u:G[v]){
      if(~blg[u]||is_bridge(u,v)) continue;
      blg[u]=blg[v];
      fill_component(u);
    }
  }

  void add_component(int v,int &k){
    if(~blg[v]) return;
    blg[v]=k++;
    C.emplace_back();
    fill_component(v);
  }

  int build(){
    for(int i=0;i<n;i++)
      if(ord[i]<0) dfs(i);

    vector<int> cnt(n,0);
    for(int i=0;i<n;i++){
      int p=par[i];
      if(p<0) continue;
      if(par[p]<0) cnt[p]++;
      else if(ord[p]<=low[i]) ap.emplace_back(p);
    }

    for(int i=0;i<n;i++)
      if(cnt[i]>1) ap.emplace_back(i);

    sort(ap.begin(),ap.end());
    ap.erase(unique(ap.begin(),ap.end()),ap.end());

    int k=0;
    for(int i=0;i<n;i++) add_component(i,k);

    T.assign(k,vector<int>());
    for(auto e:bs){
      int u=blg[e.first],v=blg[e.second];
      T[u].emplace_back(v);
      T[v].emplace_back(u);
    }
    return k;
  }
};
//END CUT HERE
#ifndef call_from_test

#define call_from_test
#include "../datastructure/unionfind.cpp"
#include "../mod/mint.cpp"
#include "../combinatorics/enumeration.cpp"
#undef call_from_test


//INSERT ABOVE HERE
// test num
signed ARC045_D(){
  cin.tie(0);
  ios::sync_with_stdio(0);

  int n;
  cin>>n;
  vector<int> xs(2*n+1),ys(2*n+1);
  for(int i=0;i<2*n+1;i++) cin>>xs[i]>>ys[i];

  vector<vector<int> > R(2*n+2),C(2*n+2);
  for(int i=0;i<2*n+1;i++) R[xs[i]].emplace_back(i);
  for(int i=0;i<2*n+1;i++) C[ys[i]].emplace_back(i);

  UnionFind uf(2*n+1);
  for(auto &v:R)
    for(auto u:v) uf.unite(v[0],u);
  for(auto &v:C)
    for(auto u:v) uf.unite(v[0],u);

  vector<int> vs;
  for(int i=0;i<2*n+1;i++){
    if(uf.find(i)!=i) continue;
    if(uf.size(i)&1) vs.emplace_back(i);
  }
  assert(!vs.empty());

  if(vs.size()>1u){
    for(int i=0;i<2*n+1;i++) cout<<"NG\n";
    cout<<flush;
    return 0;
  }

  LowLink G(2*n+1);
  auto add_edge=
    [&](auto &V)->void{
      for(auto &v:V){
        if(v.empty()) continue;
        if(!uf.same(vs[0],v[0])) continue;
        if(v.size()>0u) for(auto u:v) G.add_edge(v[0],u);
        if(v.size()>1u) for(auto u:v) G.add_edge(v[1],u);
      }
    };
  add_edge(R);
  add_edge(C);

  G.build();
  auto ap=G.ap;

  vector<int> ans(2*n+1,0);
  for(int i=0;i<2*n+1;i++)
    if(uf.same(vs[0],i)) ans[i]=1;

  for(int v:ap){
    if(!uf.same(vs[0],v)) continue;
    for(int u:G.G[v]){
      if(G.par[u]!=v) continue;
      if(~G.par[v]&&G.ord[v]>G.low[u]) continue;
      if(G.num[u]&1) ans[v]=0;
    }
  }

  for(int i=0;i<2*n+1;i++) cout<<(ans[i]?"OK\n":"NG\n");
  cout<<flush;
  return 0;
}
/*
  verified on 2019/10/25
  https://atcoder.jp/contests/arc045/tasks/arc045_d
*/


signed ARC062_F(){
  cin.tie(0);
  ios::sync_with_stdio(0);

  int n,m,k;
  cin>>n>>m>>k;

  using P = pair<int, int>;
  map<P, int> idx;

  LowLink G(n);
  for(int i=0;i<m;i++){
    int a,b;
    cin>>a>>b;
    a--;b--;
    G.add_edge(a,b);
    idx[P(a,b)]=idx[P(b,a)]=i;
  }

  G.build();

  UnionFind uf(m);
  for(auto vs:G.E)
    for(auto p:vs) uf.unite(idx[p],idx[vs[0]]);

  vector<set<int>> cnt(m);
  for(auto vs:G.E){
    for(auto p:vs){
      cnt[uf.find(idx[p])].emplace(p.first);
      cnt[uf.find(idx[p])].emplace(p.second);
    }
  }

  using M = Mint<int>;
  using E = Enumeration<M>;
  E::init(1000);

  auto calc1=
    [&](int x)->M{
      M res{0};

      for(int i=0;i<x;i++)
        res+=M(k).pow(__gcd(i,x));

      res*=E::Invs(x);
      return res;
    };

  M ans{1};
  for(int i=0;i<m;i++){
    if(uf.find(i)!=i) continue;
    if(uf.size(i)< (int)cnt[i].size()) ans*=M(k).pow(uf.size(i));
    if(uf.size(i)==(int)cnt[i].size()) ans*=calc1(uf.size(i));
    if(uf.size(i)> (int)cnt[i].size()) ans*=E::H(uf.size(i),k);
  }
  cout<<ans.v<<endl;
  return 0;
}
/*
  verified on 2020/02/19
  https://atcoder.jp/contests/arc062/tasks/arc062_d
*/


signed main(){
  //ARC045_D();
  //ARC062_F();
  return 0;
}
#endif
