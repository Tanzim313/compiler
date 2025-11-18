
#include <bits/stdc++.h>
using namespace std;
struct NFA{ int start; set<int> finals; map<int,map<char,set<int>>> t; map<int,set<int>> eps; };
set<int> eps_closure(const NFA &n,const set<int> &S){ set<int> res=S; stack<int> st; for(int x:S) st.push(x); while(!st.empty()){ int u=st.top(); st.pop(); if(n.eps.count(u)) for(int v:n.eps.at(u)) if(res.insert(v).second) st.push(v);} return res;}
set<int> moveN(const NFA &n,const set<int> &S,char a){ set<int> R; for(int p:S) if(n.t.count(p)&&n.t.at(p).count(a)) R.insert(n.t.at(p).at(a).begin(), n.t.at(p).at(a).end()); return R;}
int main(){
    NFA n; n.start=0;
    // left (a*): 0->1 eps, 1->2 eps, 2 -a-> 3, 3->2 eps, 2 ->4 eps (final merge)
    n.eps[0].insert(1); n.eps[1].insert(2); n.t[2]['a']={3}; n.eps[3].insert(2); n.eps[2].insert(4);
    // right b(a|b): 0->5 eps, 5 -b->6, 6->7 eps, 7 -a->8, 7 -b->8, 8->4 eps
    n.eps[0].insert(5); n.t[5]['b']={6}; n.eps[6].insert(7); n.t[7]['a']={8}; n.t[7]['b']={8}; n.eps[8].insert(4);
    n.finals.insert(4);
    vector<set<int>> D; map<set<int>,int> id; queue<set<int>> q;
    set<int> s0 = eps_closure(n, {n.start}); id[s0]=0; D.push_back(s0); q.push(s0);
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
    vector<string> tests = {"", "a", "aaaa", "ba", "bb", "bab", "ab"};
    for(auto &t: tests) cout<< (t==""? string("ε"):t) <<" -> "<<(simulate(t)?"ACCEPT":"REJECT")<<"\n";
    return 0;
}
