
// Q3: Interleave 
#include <iostream>
using namespace std;

void interleave(vector<int>& arr){
    int n=arr.size();
    queue<int> q;
    for(int x:arr) q.push(x);
    int mid=n/2;
    vector<int> a,b,res;
    for(int i=0;i<mid;i++){a.push_back(q.front());q.pop();}
    while(!q.empty()){b.push_back(q.front());q.pop();}
    int i=0,j=0;
    while(i<a.size() || j<b.size()){
        if(i<a.size()) res.push_back(a[i++]);
        if(j<b.size()) res.push_back(b[j++]);
    }
    arr=res;
}

int main(){
    int n; cin>>n;
    vector<int>a(n);
    for(int i=0;i<n;i++)cin>>a[i];
    interleave(a);
    for(int x:a)cout<<x<<" ";
}
