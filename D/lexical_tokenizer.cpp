
#include <bits/stdc++.h>
using namespace std;
bool isKeyword(const string &s){ static set<string> kw={"int","float","if","else"}; return kw.count(s); }
bool isIdentifier(const string &s){ if(s.empty()) return false; if(!isalpha((unsigned char)s[0]) && s[0]!='_') return false; for(char c:s) if(!isalnum((unsigned char)c) && c!='_') return false; return true; }
bool isNumber(const string &s){ if(s.empty()) return false; for(char c:s) if(!isdigit((unsigned char)c)) return false; return true; }
vector<pair<string,string>> tokenize(const string &line){
    vector<pair<string,string>> out; string cur;
    for(size_t i=0;i<line.size();++i){
        char c=line[i];
        if(isspace((unsigned char)c) || c=='+'||c=='-'||c=='*'||c=='/'||c=='='||c==';'){
            if(!cur.empty()){
                if(isKeyword(cur)) out.push_back({"Keyword",cur});
                else if(isNumber(cur)) out.push_back({"Number",cur});
                else if(isIdentifier(cur)) out.push_back({"Identifier",cur});
                else out.push_back({"Unknown",cur});
                cur.clear();
            }
            if(c=='+'||c=='-'||c=='*'||c=='/'||c=='=') out.push_back({"Operator", string(1,c)});
        } else cur.push_back(c);
    }
    if(!cur.empty()){
        if(isKeyword(cur)) out.push_back({"Keyword",cur});
        else if(isNumber(cur)) out.push_back({"Number",cur});
        else if(isIdentifier(cur)) out.push_back({"Identifier",cur});
        else out.push_back({"Unknown",cur});
    }
    return out;
}
int main(){
    string s="int x = y + 45;";
    cout<<"Input: "<<s<<"\n";
    auto toks = tokenize(s);
    for(auto &p: toks) cout<<p.first<<": "<<p.second<<"\n";
    cout<<"\nInteractive: enter a line to tokenize (empty to quit)\n";
    string line;
    while(true){
        getline(cin, line);
        if(line.empty()) break;
        for(auto &p: tokenize(line)) cout<<p.first<<": "<<p.second<<"\n";
    }
    return 0;
}
