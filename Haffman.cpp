#include <iostream>
#include <vector>
#include <map>


using namespace std;

vector<bool> bitcode;
map<char, vector<bool>> mappingtable;

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

void Table(Node *root) {
    if (root->left != NULL){
        bitcode.push_back(0);
        Table(root->left);
    }

    if (root->right != NULL){
        bitcode.push_back(1);
        Table(root->right);
    }

    if (root->left == NULL && root->right == NULL)
        mappingtable[root->c] = bitcode;

    bitcode.pop_back();
}


int main(){

    return 0;
}