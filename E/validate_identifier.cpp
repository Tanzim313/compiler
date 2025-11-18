
#include <bits/stdc++.h>
using namespace std;
bool validIdentifier(const string &s){ if(s.empty()) return false; if(!isalpha((unsigned char)s[0]) && s[0]!='_') return false; for(char c:s) if(!isalnum((unsigned char)c) && c!='_') return false; return true; }
int main(){
    vector<string> tests = {"_temp","9abc","value1","__id"};
    for(auto &t: tests) cout<<t<<" -> "<<(validIdentifier(t)?"VALID":"INVALID")<<"\n";
    // interactive
    cout<<"\nEnter identifiers (Ctrl+D to end):\n";
    string s;
    while(cin>>s) cout<<s<<" -> "<<(validIdentifier(s)?"VALID":"INVALID")<<"\n";
    return 0;
}
