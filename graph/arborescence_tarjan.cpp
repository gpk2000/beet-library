#ifndef call_from_test
#include<bits/stdc++.h>
using namespace std;
#endif
//BEGIN CUT HERE
template<typename T>
struct Arborescence{
  struct SkewHeap{
    using P = pair<T, int>;
    const P INF;
    const T add_identity;
    SkewHeap(T inf):INF(inf,-1),add_identity(0){}

    struct Node{
      Node *l,*r;
      P val;
      T add;
      Node(P val,T add):val(val),add(add){l=r=nullptr;}
    };

    P reflect(P x,T y){return P(x.first+y,x.second);}

    void eval(Node *a){
      if(a==nullptr) return;
      if(a->add==add_identity) return;
      if(a->l) a->l->add+=a->add;
      if(a->r) a->r->add+=a->add;
      a->val=reflect(a->val,a->add);
      a->add=add_identity;
    }

    P top(Node *a){
      return a?reflect(a->val,a->add):INF;
    }

    P snd(Node *a){
      eval(a);
      return a?min(top(a->l),top(a->r)):INF;
    }

    Node* add(Node *a,T d){
      if(a) a->add+=d;
      return a;
    }

    Node* push(T v,int i){
      return new Node(P(v,i),add_identity);
    }

    Node* meld(Node *a,Node *b){
      if(!a||!b) return a?a:b;
      if(top(b)<top(a)) swap(a,b);
      eval(a);
      a->r=meld(a->r,b);
      swap(a->l,a->r);
      return a;
    }

    Node* pop(Node* a){
      eval(a);
      auto res=meld(a->l,a->r);
      delete a;
      return res;
    }
  };

  struct UnionFind{
    vector<int> r,p;
    UnionFind(){}
    UnionFind(int sz):r(sz,1),p(sz,0){iota(p.begin(),p.end(),0);}
    int find(int x){
      return (x==p[x]?x:p[x]=find(p[x]));
    }
    bool same(int x,int y){
      return find(x)==find(y);
    }
    void unite(int x,int y){
      x=find(x);y=find(y);
      if(x==y) return;
      r[x]+=r[y];
      p[y]=x;
    }
  };

  struct edge{
    int from,to;
    T cost;
    edge(){}
    edge(int from,int to,T cost):from(from),to(to),cost(cost){}
  };

  int n;
  vector<edge> es;

  Arborescence(int n):n(n){};

  void add_edge(int from,int to,T cost){
    es.emplace_back(from,to,cost);
  }

  T build(int r){
    UnionFind uf(n);
    const T INF = numeric_limits<T>::max()/2;
    SkewHeap hp(INF);
    vector<typename SkewHeap::Node*> come(n,nullptr);
    vector<int> used(n,0),from(n,-1);
    vector<T> cost(n,-1);

    used[r]=2;
    for(int i=0;i<(int)es.size();i++){
      edge &e=es[i];
      come[e.to]=hp.meld(come[e.to],hp.push(e.cost,i));
    }

    T res=0;
    for(int i=0;i<n;i++){
      if(used[i]) continue;
      int v=i;
      vector<int> l;
      while(used[v]!=2){
        used[v]=1;
        l.emplace_back(v);
        if(!come[v]) return T(-1);
        from[v]=uf.find(es[come[v]->val.second].from);
        cost[v]=hp.top(come[v]).first;
        come[v]=hp.pop(come[v]);
        if(from[v]==v) continue;

        res+=cost[v];
        if(used[from[v]]==1){
          int p=v;
          do{
            if(come[p]!=nullptr) hp.add(come[p],-cost[p]);
            if(p!=v){
              uf.unite(v,p);
              come[v]=hp.meld(come[v],come[p]);
            }
            p=uf.find(from[p]);
          }while(p!=v);
        }else{
          v=from[v];
        }
      }
      for(int u:l) used[u]=2;
    }
    return res;
  }
};
//END CUT HERE
#ifndef call_from_test
//INSERT ABOVE HERE
signed UVA_11183(){
  using ll = long long;
  int T;
  cin>>T;
  for(int t=1;t<=T;t++){
    int n,m;
    cin>>n>>m;
    Arborescence<ll> G(n);
    for(int i=0;i<m;i++){
      int s,t,w;
      cin>>s>>t>>w;
      G.add_edge(s,t,w);
    }
    ll ans=G.build(0);
    cout<<"Case #"<<t<<": ";
    if(ans<0) cout<<"Possums!"<<endl;
    else cout<<ans<<endl;
  }
  return 0;
}
/*
  verified on 2019/12/17
  https://vjudge.net/problem/UVA-11183
*/


signed main(){
  //UVA_11183();
  return 0;
}
#endif
