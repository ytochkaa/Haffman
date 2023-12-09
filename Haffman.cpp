#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>

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

void CreateEncodedFile() {
    ifstream f("text.txt", ios::binary);
    ofstream encodedFile("encoded.txt", ios::binary);

    int count = 0;
    char buf = 0;
    while (!f.eof()) {
        char c = f.get();
        vector<bool> x = mappingtable[c];
        for (int n = 0; n < x.size(); n++) {
            buf = buf | x[n] << (7 - count);
            count++;
            if (count == 8) {
                count = 0;
                encodedFile.write((char*)& buf, sizeof(buf));
                buf = 0;
            }
        }
    }

    f.close();
    encodedFile.close();
}



int main(int argc, char *argv[]){
    ifstream f("text.txt", ios::binary);
    map <char, int> m;

    while (!f.eof()){
        char c = f.get();
        m[c]++;
    }

    list<Node *> t;
    for (map<char, int>::iterator itr = m.begin(); itr != m.end(); ++itr){
        Node *p = new Node;
        p->c = itr->first;
        p->a = itr->second;
        t.push_back(p);
    }

    while (t.size() != 1){
        t.sort(MyCompare());

        Node *Lchild = t.front();
        t.pop_front();
        Node *Rchild = t.front();
        t.pop_front();

        Node *parent = new Node(Lchild, Rchild);
        t.push_back(parent);
    }

    Node *root = t.front();

    Table(root);
    CreateEncodedFile();

    return 0;
}