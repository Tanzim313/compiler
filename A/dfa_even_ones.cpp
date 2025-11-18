
#include <bits/stdc++.h>
using namespace std;
bool accepts(const string &s){
    int state=0; // 0 even, 1 odd
    for(char c: s){
        if(c!='0' && c!='1') return false;
        if(c=='1') state ^= 1;
    }
    return state==0;
}
int main(){
    vector<string> tests = {"1110","10101","1100111"};
    for(auto &t: tests) cout<<t<<" -> "<<(accepts(t)?"ACCEPT":"REJECT")<<"\n";
    // interactive
    cout<<"\nEnter a binary string (empty to stop):\n";
    string s;
    while(cin>>s) cout<<s<<" -> "<<(accepts(s)?"ACCEPT":"REJECT")<<"\n";
    return 0;
}
