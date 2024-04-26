/*
 Prob statement: https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/C

 Author: B Yaswanth

Input:
5 5  // n,m
3 4 3 5 2   // a_i
2 0 3
1 1 2
2 0 3
1 0 2
2 0 5

Output:
3 2
2 1
2 3


*/

#include<bits/stdc++.h>
using namespace std;

struct item {
  int val;    // mininum value 
  int count;  // no of occurences of minimum value
};

struct segtree {
  int size;
  vector<item> counts;

  void init(int n){
    size = 1;
    while(size < n) size*= 2;
    item start;
    start.val = INT_MAX;
    start.count = 0;
    counts.assign(2*size, start);
  }

  void set(int i, int v, int x, int lx, int rx){
    if(rx-lx == 1){
      item it;
      it.val = v;
      it.count = 1;
      counts[x] = it;
      return;
    }

    int m = (lx + rx)/2;

    if(i < m) set(i,v,2*x+1, lx, m);
    else set(i,v,2*x+2, m, rx);

    item c1 = counts[2*x+1];
    item c2 = counts[2*x+2];
    item c;
    if(c1.val < c2.val){
      c = c1;
    }else if(c1.val > c2.val){
      c = c2;
    }else if(c1.val == c2.val){
      c = c1;
      c.count = c1.count + c2.count;
    }

    counts[x] = c;
  }

  void set(int index, int val){
    set(index, val, 0, 0, size);
  }

  item getCount(int l, int r, int x, int lx, int rx){
    item start;
    start.val = INT_MAX;
    start.count = 1;
    if(lx >= r || l >= rx) return start;
    if(lx >= l && rx <= r) return counts[x];

    int m = (lx + rx) / 2;
    item c1 = getCount(l, r, 2*x + 1, lx, m);
    item c2 = getCount(l, r, 2*x + 2, m, rx);
    item c;
    if(c1.val < c2.val){
      c = c1;
    }else if(c1.val > c2.val){
      c = c2;
    }else if(c1.val == c2.val){
      c = c1;
      c.count = c1.count + c2.count;
    }

    return c;
  }

  item getCount(int l, int r){
    return getCount(l,r, 0, 0, size);
  }
};

int main(){
  ios_base::sync_with_stdio(false);
  int n,m;
  cin>>n>>m;
  vector<int> a(n);
  segtree st;
  st.init(n);
  for(int i=0; i<n; i++){
    cin>>a[i];
    st.set(i, a[i]);
  }

  // for(int i=0; i<2*st.size; i++) cout<<st.counts[i].val << " => "<<st.counts[i].count<<endl;

  while(m--){
    int op;cin>>op;
    if(op == 1){
      int i,v;
      cin>>i>>v;
      st.set(i,v);
    }else if(op == 2){
      int l,r;
      cin>>l>>r;
      item res = st.getCount(l,r);
      cout<<res.val <<" "<<res.count<<endl;
    }
  }
  return 0;
}
