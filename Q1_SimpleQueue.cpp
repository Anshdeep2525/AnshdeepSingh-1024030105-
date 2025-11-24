
// Q1: Simple Queue in C++
#include <iostream>
using namespace std;

struct SimpleQueue {
    int capacity;
    vector<int> arr;
    int frontIdx, rearIdx, count;
    SimpleQueue(int size=100) {
        capacity = size;
        arr.assign(size, 0);
        frontIdx = 0;
        rearIdx = -1;
        count = 0;
    }
    bool isEmpty() { return count == 0; }
    bool isFull() { return count == capacity; }
    void enqueue(int x) {
        if (isFull()) { cout<<"Queue full\n"; return; }
        rearIdx++;
        if (rearIdx >= capacity) { cout<<"End reached\n"; rearIdx--; return; }
        arr[rearIdx] = x; count++;
    }
    int dequeue() {
        if (isEmpty()) { cout<<"Empty\n"; return INT_MIN; }
        int v = arr[frontIdx++];
        count--; return v;
    }
    void display() {
        if (isEmpty()) { cout<<"Empty\n"; return; }
        for (int i=frontIdx;i<=rearIdx;i++) cout<<arr[i]<<" ";
        cout<<"\n";
    }
};

int main() {
    int size; cin>>size;
    SimpleQueue q(size);
    int ch,x;
    while(cin>>ch){
        if(ch==1){cin>>x;q.enqueue(x);}
        else if(ch==2){cout<<q.dequeue()<<"\n";}
        else if(ch==3){q.display();}
        else break;
    }
}
