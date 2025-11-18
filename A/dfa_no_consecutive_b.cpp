
#include <bits/stdc++.h>
using namespace std;
bool accepts(const string &s){
    int state=0; // 0: last not b, 1: last was b, 2: dead
    for(char c: s){
        if(c!='a' && c!='b') return false;
        if(state==0) state = (c=='b'?1:0);
        else if(state==1) state = (c=='b'?2:0);
        else state = 2;
    }
    return state!=2;
}
int main(){
    vector<string> tests = {"abba","ababab","abbba","baaab"};
    for(auto &t: tests) cout<<t<<" -> "<<(accepts(t)?"ACCEPT":"REJECT")<<"\n";
    cout<<"\nTry your own (a/b strings):\n";
    string s;
    while(cin>>s) cout<<s<<" -> "<<(accepts(s)?"ACCEPT":"REJECT")<<"\n";
    return 0;
}
