#ifndef call_from_test
#include<bits/stdc++.h>
using namespace std;
#endif
//BEGIN CUT HERE
template <typename T>
struct SegmentTree{
  using F = function<T(T,T)>;
  F f;
  T ti;
  SegmentTree(F f,T ti):f(f),ti(ti){}

  struct Node{
    Node *l,*r;
    T dat;
    Node(T dat):dat(dat){l=r=nullptr;}
  };

  Node* clone(Node *a){
    return new Node(*a);
  }

  Node* reflect(Node *a){
    a->dat=f(a->l->dat,a->r->dat);
    return a;
  }

  int n,height;
  Node* build(const vector<T> &v){
    int n_=v.size();
    n=1;height=0;
    while(n<n_) n<<=1,height++;
    vector<Node*> vs(n<<1);
    for(int i=0;i<n_;i++) vs[n+i]=new Node(v[i]);
    for(int i=n_;i<n;i++) vs[n+i]=new Node(ti);
    for(int i=n-1;i;i--){
      vs[i]=new Node(ti);
      vs[i]->l=vs[(i<<1)|0];
      vs[i]->r=vs[(i<<1)|1];
      reflect(vs[i]);
    }
    return vs[1];
  }

  Node* set_val(Node* t,int k,T x,int h){
    t=clone(t);
    if(h<0){
      t->dat=x;
      return t;
    }
    if((k>>h)&1) t->r=set_val(t->r,k,x,h-1);
    else t->l=set_val(t->l,k,x,h-1);
    return reflect(t);
  }

  T query(Node* t,int l,int r,int lb,int ub){
    if(r<=lb||ub<=l) return ti;
    if(l<=lb&&ub<=r) return t->dat;
    int m=(lb+ub)>>1;
    return f(query(t->l,l,r,lb,m),query(t->r,l,r,m,ub));
  }

  Node* set_val(Node* t,int k,T x){
    return set_val(t,k,x,height-1);
  }

  T query(Node* t,int l,int r){
    return query(t,l,r,0,n);
  }
};
//END CUT HERE
#ifndef call_from_test
//INSERT ABOVE HERE
signed HAPPYQUERY_B(){
  cin.tie(0);
  ios::sync_with_stdio(0);

  int n;
  cin>>n;
  vector<int> as(n);
  for(int i=0;i<n;i++) cin>>as[i];

  auto f=[](int a,int b){return min(a,b);};
  int ti=INT_MAX;
  SegmentTree<int> seg(f,ti);
  auto rt=seg.build(as);

  int q1;
  cin>>q1;

  vector<decltype(rt)> rts;
  rts.reserve(q1+1);
  rts.emplace_back(rt);

  for(int i=0;i<q1;i++){
    int p,x;
    cin>>p>>x;
    p--;
    rt=seg.set_val(rt,p,x);
    rts.emplace_back(rt);
  }

  int q2;
  cin>>q2;
  int x=0;
  for(int i=0;i<q2;i++){
    int a,b,c;
    cin>>a>>b>>c;
    int k=a^x;
    int l=(b^x)-1;
    int r=(c^x);
    assert(l<r);
    x=seg.query(rts[k],l,r);
    cout<<x<<"\n";
  }
  cout<<flush;
  return 0;
}
/*
  verified on 2019/06/22
  https://www.hackerrank.com/contests/happy-query-contest/challenges/minimum-history-query
*/
signed main(){
  HAPPYQUERY_B();
  return 0;
}
#endif
