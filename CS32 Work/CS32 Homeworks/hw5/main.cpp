#include <iostream>
#include <string>
#include <cassert>

using namespace std;

int Fib(int N)
{
    cout << "N value is " << N << endl;
    if (N == 0 || N == 1)
        return 1;
    return Fib(N - 1) + Fib(N - 2);
}

//
//
//
//
//class binaryTree
//{
//private:
//    struct binaryTreeNode
//    {
//        binaryTreeNode* left;
//        binaryTreeNode* right;
//        binaryTreeNode* prev;
//        int data;
//    };
//    
//    binaryTreeNode* root;
//
//public:
//    binaryTree() {root = nullptr;}
//    void printInOrder();
//    void inOrder(binaryTreeNode* node);
//    void insert (int value);
//};
//
//
//void binaryTree::printInOrder()
//{
//    inOrder(root);
//}
//
//void binaryTree::inOrder(binaryTreeNode* node)
//{
//    if (node != nullptr)
//    {
//        if (node->left) // not nullptr
//            inOrder(node->left);
//        
//        cout << node->data << endl;
//        
//        if (node->right) // not nullptr
//            inOrder(node->right);
//    }
//    else // node is a lef
//        return;
//}
//
//void binaryTree::insert(int value)
//{
//    binaryTreeNode* temp = new binaryTreeNode;
//    binaryTreeNode* parent;
//    
//    temp->data = value;
//    temp->left = nullptr;
//    temp->right = nullptr;
//    parent = nullptr;
//    
//    if (root == nullptr)
//    {
//        root = temp;
//        temp->prev = root;
//    }
//    else
//    {
//        binaryTreeNode* curr = root;
//        
//        while (curr) // while not a nullptr
//        {
//            parent = curr;
//            if (temp->data > curr->data)
//                curr = curr->right;
//            else
//                curr = curr->left;
//        }
//        
//        if (temp->data < parent->data)
//        {
//            parent->left = temp;
//            temp->prev = parent;
//        }
//        else
//        {
//            parent->right = temp;
//            temp->prev = parent;
//        }
//    }
//}

int main()
{
//    binaryTree BT1;
//    BT1.insert(10);
//    BT1.insert(15);
//    BT1.insert(13);
//    BT1.insert(0);
//    BT1.insert(600);
//    BT1.insert(20);
//    BT1.insert(-500);
//    BT1.insert(10000000);
//    
//    BT1.printInOrder();
    
    cout << Fib(5) << endl;
    
}