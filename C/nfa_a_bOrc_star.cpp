
#include <bits/stdc++.h>
using namespace std;
struct NFA{ int start; set<int> finals; map<int,map<char,set<int>>> t; map<int,set<int>> eps; };
set<int> eps_closure(const NFA &n, const set<int> &S){
    set<int> res=S; stack<int> st; for(int s:S) st.push(s);
    while(!st.empty()){ int u=st.top(); st.pop(); if(n.eps.count(u)) for(int v: n.eps.at(u)) if(res.insert(v).second) st.push(v); }
    return res;
}
set<int> moveN(const NFA &n, const set<int> &S, char a){
    set<int> R;
    for(int p: S) if(n.t.count(p) && n.t.at(p).count(a)) R.insert(n.t.at(p).at(a).begin(), n.t.at(p).at(a).end());
    return R;
}
int main(){
    NFA n; // build a(b|c)*
    // states indices chosen arbitrarily
    n.start=0;
    n.t[0]['a']={1};
    n.eps[1].insert(2);
    n.t[2]['b']={3}; n.t[2]['c']={3};
    n.eps[3].insert(2);
    n.eps[2].insert(4); // 4 final
    n.finals.insert(4);
    // subset construction over alphabet {a,b,c}
    vector<set<int>> D; map<set<int>,int> id; queue<set<int>> q;
    set<int> s0 = eps_closure(n, {n.start});
    id[s0]=0; D.push_back(s0); q.push(s0);
    while(!q.empty()){
        auto cur=q.front(); q.pop();
        for(char a: {'a','b','c'}){
            set<int> mv = moveN(n, cur, a);
            set<int> cls = eps_closure(n, mv);
            if(!cls.empty() && !id.count(cls)){ id[cls]=D.size(); D.push_back(cls); q.push(cls); }
        }
    }
    auto simulate=[&](const string &w){
        set<int> cur = s0;
        for(char c: w){ cur = eps_closure(n, moveN(n, cur, c)); if(cur.empty()) break; }
        for(int x: cur) if(n.finals.count(x)) return true; return false;
    };
    vector<string> tests = {"a","ab","acb","abcbcc","", "b"};
    for(auto &t: tests) cout<<t<<" -> "<<(simulate(t)?"ACCEPT":"REJECT")<<"\n";
    return 0;
}
