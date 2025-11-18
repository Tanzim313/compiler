#include <bits/stdc++.h>
using namespace std;
struct NFA{ int start; set<int> finals; map<int,map<char,set<int>>> t; map<int,set<int>> eps; };
set<int> eps_closure(const NFA &n, const set<int> &S){
    set<int> res=S; stack<int> st; for(int s:S) st.push(s);
    while(!st.empty()){
        int u=st.top(); st.pop();
        auto it=n.eps.find(u);
        if(it==n.eps.end()) continue;
        for(int v: it->second) if(res.insert(v).second) st.push(v);
    }
    return res;
}
set<int> moveN(const NFA &n,const set<int> &S,char a){
    set<int> R;
    for(int p:S){ auto it=n.t.find(p); if(it!=n.t.end()){ auto it2=it->second.find(a); if(it2!=it->second.end()) R.insert(it2->second.begin(), it2->second.end()); } }
    return R;
}
int main(){
    NFA n; n.start=0; n.eps[0].insert(1); n.t[1]['a']={1}; n.t[1]['b']={2}; n.finals.insert(2);
    vector<set<int>> D; map<set<int>,int> id; queue<set<int>> q;
    set<int> start = eps_closure(n, {n.start});
    id[start]=0; D.push_back(start); q.push(start);
    while(!q.empty()){
        auto cur=q.front(); q.pop();
        for(char a: {'a','b'}){
            set<int> mv = moveN(n, cur, a);
            set<int> cls = eps_closure(n, mv);
            if(!cls.empty() && !id.count(cls)){ id[cls]=D.size(); D.push_back(cls); q.push(cls); }
        }
    }
    cout<<"DFA states:\n";
    for(size_t i=0;i<D.size();++i){
        cout<<"D"<<i<<"={"; bool f=false; for(int x:D[i]){ if(f) cout<<","; cout<<x; f=true;} cout<<"}";
        for(int x:D[i]) if(n.finals.count(x)){ cout<<" (final)"; break; }
        cout<<"\n";
    }
    auto simulate=[&](const string &w){
        set<int> cur = start;
        for(char c: w){ cur = eps_closure(n, moveN(n, cur, c)); if(cur.empty()) break; }
        for(int x: cur) if(n.finals.count(x)) return true; return false;
    };
    vector<string> tests={"","a","aaab","b","ab","aab"};
    cout<<"\nTests:\n"; for(auto &t: tests) cout<<t<<" -> "<<(simulate(t)?"ACCEPT":"REJECT")<<"\n";
    return 0;
}
