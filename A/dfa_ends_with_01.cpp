
#include <bits/stdc++.h>
using namespace std;
bool accepts(const string &s){
    int state = 0; // q0
    for(char c: s){
        if(c!='0' && c!='1') return false;
        if(state==0) state = (c=='0'?1:0);
        else if(state==1) state = (c=='0'?1:2);
        else state = (c=='0'?1:0);
    }
    return state==2;
}
int main(){
    vector<string> tests = {"101","1101","100","001"};
    for(auto &t: tests) cout<<t<<" -> "<<(accepts(t)?"ACCEPT":"REJECT")<<"\n";
    // interactive
    cout<<"\nEnter a binary string to test (or empty to exit):\n";
    string s;
    while(cin>>s){
        cout<<s<<" -> "<<(accepts(s)?"ACCEPT":"REJECT")<<"\n";
    }
    return 0;
}
