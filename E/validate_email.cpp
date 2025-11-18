
#include <bits/stdc++.h>
using namespace std;
bool validEmail(const string &s){
    try {
        regex r(R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{1,}$)");
        return regex_match(s, r);
    } catch(...) { return false; }
}
int main(){
    vector<string> tests = {"user@gmail.com","test_mail@yahoo","a@b.c"};
    for(auto &t: tests) cout<<t<<" -> "<<(validEmail(t)?"VALID":"INVALID")<<"\n";
    cout<<"\nEnter emails to test (Ctrl+D to end):\n";
    string s;
    while(cin>>s) cout<<s<<" -> "<<(validEmail(s)?"VALID":"INVALID")<<"\n";
    return 0;
}
