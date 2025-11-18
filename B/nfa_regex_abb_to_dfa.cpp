
#include <bits/stdc++.h>
using namespace std;
// Build an NFA for (a|b)*abb using simple construction and subset-convert
struct NFA{ int start; set<int> finals; map<int,map<char,set<int>>> t; };
set<int> moveN(const NFA &n, const set<int> &S, char a){
    set<int> R;
    for(int p: S){ auto it=n.t.find(p); if(it!=n.t.end()){ auto it2=it->second.find(a); if(it2!=it->second.end()) R.insert(it2->second.begin(), it2->second.end()); } }
    return R;
}
int main(){
    NFA n;
    // We'll build a tiny NFA:
    // 0 --loop--> 0 on a,b (representing (a|b)*)
    // 0 --a-->1; 1--b-->2; 2--b-->3(final)
    n.start=0;
    n.t[0]['a']={0}; n.t[0]['b']={0};
    n.t[0]['a'].insert(1);
    n.t[1]['b']={2};
    n.t[2]['b']={3};
    n.finals.insert(3);
    // subset construction (no epsilons)
    vector<set<int>> D; map<set<int>,int> id; queue<set<int>> q;
    set<int> s0 = {n.start}; D.push_back(s0); id[s0]=0; q.push(s0);
    while(!q.empty()){
        auto cur = q.front(); q.pop();
        for(char a: {'a','b'}){
            set<int> nxt = moveN(n, cur, a);
            if(!nxt.empty() && !id.count(nxt)){ id[nxt]=D.size(); D.push_back(nxt); q.push(nxt); }
        }
    }
    cout<<"DFA states:\n";
    for(size_t i=0;i<D.size();++i){
        cout<<"D"<<i<<"={";
        bool k=false; for(int x: D[i]){ if(k) cout<<","; cout<<x; k=true; } cout<<"}";
        for(int x: D[i]) if(n.finals.count(x)){ cout<<" (final)"; break; }
        cout<<"\n";
    }
    auto simulate=[&](const string &w){
        set<int> cur=s0;
        for(char c: w) cur = moveN(n, cur, c);
        for(int x: cur) if(n.finals.count(x)) return true;
        return false;
    };
    vector<string> tests = {"abb","aabb","abababb","ab","babb"};
    cout<<"\nTests:\n";
    for(auto &t: tests) cout<<t<<" -> "<<(simulate(t)?"ACCEPT":"REJECT")<<"\n";
    return 0;
}
