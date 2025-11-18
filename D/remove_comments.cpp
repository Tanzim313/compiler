
#include <bits/stdc++.h>
using namespace std;
string removeComments(const string &code){
    string out; for(size_t i=0;i<code.size();){
        if(i+1<code.size() && code[i]=='/' && code[i+1]=='/'){ i+=2; while(i<code.size() && code[i]!='\n') ++i; }
        else if(i+1<code.size() && code[i]=='/' && code[i+1]=='*'){ i+=2; while(i+1<code.size() && !(code[i]=='*'&&code[i+1]=='/')) ++i; if(i+1<code.size()) i+=2; }
        else { out.push_back(code[i]); ++i; }
    } return out;
}
int main(){
    string code = "int x; // this is x\n/* block comment */\nfloat y; // end\n";
    cout<<"Before:\n"<<code<<"\nAfter:\n"<<removeComments(code)<<"\n";
    // read from stdin example
    // cout << removeComments(string(istreambuf_iterator<char>(cin), {})) << endl;
    return 0;
}
