#include <bits/stdc++.h>
using namespace std;

// -> This is the code when postorder is given. Notice that we first move to the right and then left in the lines 41 and 42. 
//    This is because in postorder, root elements are towards the right.
// => If we are given preorder instead, then we start with p index = 0 (from the left) and move towards the left subtree first
//    and then towards the right subtree

class Node {
  public:
    int data;
    Node *left, *right;
    Node(int x) {
        data = x;
        left = right = nullptr;
    }
};

int search(vector<int> &arr, int strt, int end, int value) {
    int i;
    for (i = strt; i <= end; i++) {
        if (arr[i] == value)
            break;
    }
    return i;
}

Node *foo(vector<int> &inorder, vector<int> &postorder, 
                int inStrt, int inEnd, int &pIndex) {

    // if inStart is greater than inEnd return nullptr
    if (inStrt > inEnd)
        return nullptr;

    Node *node = new Node(postorder[pIndex]);
    pIndex--;

    // no children
    if (inStrt == inEnd)
        return node;

    int iIndex = search(inorder, inStrt, inEnd, node->data);

    node->right = foo(inorder, postorder, iIndex + 1, inEnd, pIndex);
    node->left = foo(inorder, postorder, inStrt, iIndex - 1, pIndex);

    return node;
}

Node *createTree(vector<int> &inorder, vector<int> &postorder) {
    int n = inorder.size();
    int pIndex = n - 1;
    return foo(inorder, postorder, 0, n - 1, pIndex);
}

void print(Node *curr) {
    if (curr == nullptr)
        return;
    cout << curr->data << " ";
    print(curr->left);
    print(curr->right);
}

int main() {
    vector<int> inorder = {4, 8, 2, 5, 1, 6, 3, 7};
    vector<int> postorder = {8, 4, 5, 2, 6, 7, 3, 1};

    Node *root = createTree(inorder, postorder);
    print(root);
    return 0;
}
