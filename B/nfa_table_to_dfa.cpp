
#include <bits/stdc++.h>
using namespace std;
// Simple NFA struct and subset construction for alphabet {'0','1'}
struct NFA {
    int start;
    set<int> finals;
    map<int, map<char, set<int>>> trans;
};
set<int> moveN(const NFA &n, const set<int> &S, char a){
    set<int> R;
    for(int p: S){
        auto it = n.trans.find(p);
        if(it!=n.trans.end()){
            auto it2 = it->second.find(a);
            if(it2!=it->second.end()) R.insert(it2->second.begin(), it2->second.end());
        }
    }
    return R;
}
int main(){
    NFA n;
    // map A=0,B=1,C=2; start A
    n.start=0;
    n.trans[0]['0'] = {0,1}; n.trans[0]['1'] = {0};
    n.trans[1]['0'] = {2}; n.trans[1]['1'] = {1};
    n.trans[2]['0'] = {2}; n.trans[2]['1'] = {2};
    n.finals.insert(2);

    vector<set<int>> D;
    map<set<int>, int> id;
    queue<set<int>> q;
    set<int> s0 = {n.start};
    D.push_back(s0); id[s0]=0; q.push(s0);
    while(!q.empty()){
        auto cur = q.front(); q.pop();
        int curid = id[cur];
        set<int> r0 = moveN(n, cur, '0');
        set<int> r1 = moveN(n, cur, '1');
        if(!r0.empty() && !id.count(r0)){ id[r0]=D.size(); D.push_back(r0); q.push(r0); }
        if(!r1.empty() && !id.count(r1)){ id[r1]=D.size(); D.push_back(r1); q.push(r1); }
    }
    cout<<"DFA states (sets):\n";
    for(size_t i=0;i<D.size();++i){
        cout<<"D"<<i<<" = {";
        bool f=false;
        for(int x: D[i]) { if(f) cout<<","; cout<<x; f=true; }
        cout<<"}";
        for(int x: D[i]) if(n.finals.count(x)){ cout<<" (final)"; break; }
        cout<<"\n";
    }
    // test function
    auto simulate = [&](const string &w){
        set<int> cur = s0;
        for(char c: w){
            cur = moveN(n, cur, c);
            if(cur.empty()) break;
        }
        for(int x: cur) if(n.finals.count(x)) return true;
        return false;
    };
    vector<string> tests = {"0","1","01","001","1101"};
    cout<<"\nTests:\n";
    for(auto &t: tests) cout<<t<<" -> "<<(simulate(t)?"ACCEPT":"REJECT")<<"\n";
    return 0;
}
