
#include <bits/stdc++.h>
using namespace std;
bool validInteger(const string &s){
    if(s.empty()) return false;
    int i=0;
    if(s[0]=='-'){ if(s.size()==1) return false; i=1; }
    for(; i<(int)s.size(); ++i) if(!isdigit((unsigned char)s[i])) return false;
    return true;
}
int main(){
    vector<string> tests = {"12","0034","-45","abc"};
    for(auto &t: tests) cout<<t<<" -> "<<(validInteger(t)?"VALID":"INVALID")<<"\n";
    // interactive
    cout<<"\nEnter integers to validate (Ctrl+D to end):\n";
    string s;
    while(cin>>s) cout<<s<<" -> "<<(validInteger(s)?"VALID":"INVALID")<<"\n";
    return 0;
}
