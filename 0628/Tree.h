#pragma once
#include <iostream>
#include <stack>
using namespace std;

class Node{
    public:
        Node* left;
        Node* right;
        int value;
};

void ProderTraversal(Node* root){
    //利用栈对二叉树进行先序遍历
    if(root == nullptr){
        return;
    }
    stack<Node*>st;
    //先让根结点入栈
    st.push(root);

    while(!st.empty ()){
        //标记栈顶元素，并且弹出
        Node* node = st.top();
        st.pop();
        std::cout<<node->value<<" ";
        //由于栈是先入后出的规则，所以如果右子树存在
        //的情况下要先对右子树入栈，右子树不存在则
        //看左子树，左子树存在则入栈，不存在的话就说明
        //遍历到最后一个结点了
        if(node->right != nullptr){
           st.push(node->right);
           if(node->left != nullptr){
               st.push(node->left);
           }
        }
    }
    cout<<endl;
}

void RecursionProderTraversal(Node* root){
    if(root == nullptr){
        return;
    }

    //如果根结点存在的情况下先输出根结点
    //然后再去遍历左右子树
    std::cout<<root->value<<std::endl;
    RecursionProderTraversal(root->left);
    RecursionProderTraversal(root->right);
}

//利用栈以中序的方式遍历二叉树
void InorderTraversal(Node* root){
    if(root == nullptr){
        return;
    }
    stack<Node*>st;
    while(root != nullptr || !st.empty()){
        //只要结点存在就入栈
        while(root != nullptr){
            st.push(root);
            root = root->left;
        }
        Node* node = st.top();
        st.pop();
        cout<<node->value<<" ";
        //把右子树标记为root
        root = node->right;
    }
    cout<<endl;
}

void RercursionInorderTraversal(Node* root){
    if(root == nullptr){
        return;
    }

    RecursionProderTraversal(root->left);
    cout<<root->value<<" ";
    RecursionProderTraversal(root->right);
}

//非递归实现二叉树的后序遍历
void PostorderRraversal(Node* root){
    stack<Node*>st;
    Node* tag = nullptr;

    while(root != nullptr || !st.empty()){
        while(root != nullptr){
            st.push(root);
            root = root->left;
        }
        Node* node = st.top();
        st.pop();
        if(node->right == nullptr || node->right == tag){
            cout<<node->value<<" ";
            tag = node;
            node = nullptr;
        }else{
            st.push(node);
            root = node->right;
        }
    }
    cout<<endl;
}

//递归后序遍历二叉树
void RecursionPostorderTraversal(Node* root){
    if(root == nullptr){
        return;
    }

    RecursionPostorderTraversal(root->left);
    RecursionPostorderTraversal(root->right);
    cout<<root->value<<" ";
}
