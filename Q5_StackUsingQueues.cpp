
// Q5: Stack Using Queues
#include <iostream>
using namespace std;

struct StackOneQueue {
    queue<int> q;
    void push(int x){
        q.push(x);
        int s=q.size();
        for(int i=0;i<s-1;i++){
            q.push(q.front());
            q.pop();
        }
    }
    int pop(){
        if(q.empty()) return INT_MIN;
        int v=q.front(); q.pop(); return v;
    }
};

int main(){
    StackOneQueue st;
    int ch,x;
    while(cin>>ch){
        if(ch==1){cin>>x; st.push(x);}
        else if(ch==2){cout<<st.pop()<<"\n";}
        else break;
    }
}
