#include <bits/stdc++.h>

using namespace std;

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;

    Node(int val)
    {
        data = val;
        left = NULL;
        right = NULL;
    }
};

//Inorder traversal of binary tree
void printNodes(struct Node *node)
{
    if (!node)
        return;
    if (node->left)
        printNodes(node->left);
    cout << node->data << endl;
    if (node->right)
        printNodes(node->right);
}

int main()
{
    struct Node *node = new Node(1);
    node->left = new Node(2);
    node->right = new Node(3);
    node->left->left = new Node(4);
    node->left->right = new Node(5);
    node->right->left = new Node(6);
    node->right->right = new Node(7);
    printNodes(node);
}