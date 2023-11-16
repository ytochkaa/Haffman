#include <iostream>


using namespace std;


class Node{
public:
    int a;
    char c;
    Node *left, *right;

    Node() { left = right = NULL; }

    Node(Node *L, Node *R){
        left = L;
        right = R;
        a = L->a + R->a;
    }
};

struct MyCompare {
    bool operator()(const Node *l, const Node *r) const {
        return l->a < r->a;
    }
};


int main(){

    return 0;
}