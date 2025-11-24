
// Q4: First Non-Repeating 
#include <iostream>
using namespace std;

int main(){
    string s;
    getline(cin,s);
    vector<int>freq(256,0);
    queue<char> q;
    for(char c:s){
        freq[(unsigned char)c]++;
        q.push(c);
        while(!q.empty() && freq[(unsigned char)q.front()]>1) q.pop();
        if(q.empty()) cout<<-1<<" ";
        else cout<<q.front()<<" ";
    }
}
