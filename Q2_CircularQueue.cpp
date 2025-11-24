
// Q2: Circular Queue
#include <iostream>
using namespace std;

struct CircularQueue {
    int capacity;
    vector<int> arr;
    int frontIdx, rearIdx, count;
    CircularQueue(int s=100){
        capacity=s; arr.assign(s,0);
        frontIdx=0; rearIdx=s-1; count=0;
    }
    bool isFull(){return count==capacity;}
    bool isEmpty(){return count==0;}
    void enqueue(int x){
        if(isFull()){cout<<"Full\n";return;}
        rearIdx=(rearIdx+1)%capacity;
        arr[rearIdx]=x;
        count++;
    }
    int dequeue(){
        if(isEmpty()){cout<<"Empty\n";return INT_MIN;}
        int v=arr[frontIdx];
        frontIdx=(frontIdx+1)%capacity;
        count--;
        return v;
    }
    void display(){
        if(isEmpty()){cout<<"Empty\n";return;}
        int idx=frontIdx;
        for(int i=0;i<count;i++){
            cout<<arr[idx]<<" ";
            idx=(idx+1)%capacity;
        }
        cout<<"\n";
    }
};

int main(){
    int s; cin>>s;
    CircularQueue q(s);
    int ch,x;
    while(cin>>ch){
        if(ch==1){cin>>x;q.enqueue(x);}
        else if(ch==2){cout<<q.dequeue()<<"\n";}
        else if(ch==3){q.display();}
        else break;
    }
}
