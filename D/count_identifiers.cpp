
#include <bits/stdc++.h>
using namespace std;
bool isIdentifier(const string &s){ if(s.empty()) return false; if(!isalpha((unsigned char)s[0]) && s[0]!='_') return false; for(char c:s) if(!isalnum((unsigned char)c) && c!='_') return false; return true; }
string removeComments(const string &code){
    string out; for(size_t i=0;i<code.size();){
        if(i+1<code.size() && code[i]=='/' && code[i+1]=='/'){ i+=2; while(i<code.size() && code[i]!='\n') ++i; }
        else if(i+1<code.size() && code[i]=='/' && code[i+1]=='*'){ i+=2; while(i+1<code.size() && !(code[i]=='*'&&code[i+1]=='/')) ++i; if(i+1<code.size()) i+=2; }
        else { out.push_back(code[i]); ++i; }
    } return out;
}
vector<string> simpleSplit(const string &s){
    vector<string> res; string cur;
    for(char c: s){
        if(isspace((unsigned char)c) || string("+-*/=;(),{}[]<>").find(c)!=string::npos){
            if(!cur.empty()){ res.push_back(cur); cur.clear(); }
            // optionally push puncts
        } else cur.push_back(c);
    }
    if(!cur.empty()) res.push_back(cur);
    return res;
}
int main(){
    string sample = "int main(){ int x; float y; x = 5; // comment\n x2 = x + 1; /* block comment */ _var = 10; }";
    cout<<"Original:\n"<<sample<<"\n\n";
    string cleaned = removeComments(sample);
    cout<<"Cleaned:\n"<<cleaned<<"\n\n";
    auto toks = simpleSplit(cleaned);
    int cnt=0;
    for(auto &t: toks) if(isIdentifier(t)) { cout<<"Identifier: "<<t<<"\n"; ++cnt; }
    cout<<"\nTotal identifiers: "<<cnt<<"\n";
    return 0;
}
