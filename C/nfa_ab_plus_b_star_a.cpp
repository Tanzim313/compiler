
#include <bits/stdc++.h>
using namespace std;
struct NFA{ int start; set<int> finals; map<int,map<char,set<int>>> t; map<int,set<int>> eps; };
set<int> eps_closure(const NFA &n, const set<int> &S){ set<int> res=S; stack<int> st; for(int s:S) st.push(s); while(!st.empty()){ int u=st.top(); st.pop(); if(n.eps.count(u)) for(int v:n.eps.at(u)) if(res.insert(v).second) st.push(v);} return res; }
set<int> moveN(const NFA &n,const set<int> &S,char a){ set<int> R; for(int p:S) if(n.t.count(p)&&n.t.at(p).count(a)) R.insert(n.t.at(p).at(a).begin(), n.t.at(p).at(a).end()); return R; }
int main(){
    NFA n; // manual structure for (ab + b)* a
    n.start=0;
    n.eps[0].insert(1);
    // loop options from 1: option ab or b, and an epsilon to exit to concat
    n.eps[1].insert(2);
    // ab path: 2 -a-> 3 -b-> 4 -> eps back to 1
    n.t[2]['a']={3}; n.t[3]['b']={4}; n.eps[4].insert(1);
    // b path: 2 -b-> 5 -> eps back 1
    n.t[2]['b']={5}; n.eps[5].insert(1);
    // exit from loop to concat a
    n.eps[1].insert(6);
    n.t[6]['a']={7}; n.finals.insert(7);
    // subset construction over {a,b}
    vector<set<int>> D; map<set<int>,int> id; queue<set<int>> q;
    set<int> s0 = eps_closure(n,{n.start}); id[s0]=0; D.push_back(s0); q.push(s0);
    while(!q.empty()){
        auto cur=q.front(); q.pop();
        for(char a: {'a','b'}){
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
    vector<string> tests = {"a","ba","bba","abba","bbba","ababba","ab"};
    for(auto &t: tests) cout<<t<<" -> "<<(simulate(t)?"ACCEPT":"REJECT")<<"\n";
    return 0;
}
