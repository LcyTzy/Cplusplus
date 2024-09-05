#pragma once

#include "iostream"
#include "vector"
#include "stack"
using namespace std;

class TreeNode {
public:
    int value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : value(x), left(nullptr), right(nullptr) {}
};

// 插入
void insert(TreeNode*& root, int value) {
    if (root == nullptr) {
        root = new TreeNode(value);
        return;
    }
    if (value < root->value) {
        insert(root->left, value);
    } else {
        insert(root->right, value);
    }
}

// 递归输出
void PrintBinaryTreeAux01(TreeNode *root) {
    if (root == nullptr) {
        return;
    }
    cout << root->value << endl;
    PrintBinaryTreeAux01(root->left);
    PrintBinaryTreeAux01(root->right);
}

void PrintBinaryTreeAux02(TreeNode *root) {
    if (root == nullptr) {
        return;
    }
    PrintBinaryTreeAux02(root->left);
    cout << root->value << endl;
    PrintBinaryTreeAux02(root->right);
}

void PrintBinaryTreeAux03(TreeNode *root) {
    if (root == nullptr) {
        return;
    }
    PrintBinaryTreeAux03(root->left);
    PrintBinaryTreeAux03(root->right);
    cout << root->value << endl;
}

/*非递归*/
vector<int> preorderTraversal01(TreeNode* root) {
    vector<int> v;
    stack<TreeNode*> st;
    TreeNode *cur = root;
    while (cur || st.size() != 0) {
            //访问左路节点
        while (cur) {
            v.push_back(cur->value);
            st.push(cur);
            cur=cur->left;
        }
        //取栈顶
        TreeNode*stop=st.top();
        st.pop();
        //左路节点的右子树
        cur=stop->right;
    }
    return v;
}

vector<int> preorderTraversal02(TreeNode* root) {
    vector<int> v;
    stack<TreeNode*> st;
    TreeNode *cur = root;
    while (cur || st.size() != 0) {
            //访问左路节点
        while (cur) {
            st.push(cur);
            cur=cur->left;
        }
        //取栈顶
        TreeNode*stop=st.top();
        v.push_back(cur->value);
        st.pop();
        //左路节点的右子树
        cur=stop->right;
    }
    return v;
}

vector<int> preorderTraversal03(TreeNode* root) {
    vector<int> v;
    stack<TreeNode*> st;
    TreeNode *cur = root;
    TreeNode *prev = nullptr;
    while (cur || st.size() != 0) {
            //访问左路节点
        while (cur) {
            st.push(cur);
            cur=cur->left;
        }
        //取栈顶
        TreeNode*stop=st.top();
        if (stop->right == nullptr || stop->right == prev) {
            v.push_back(cur->value);
            st.pop();
            prev = stop;
        } else {
            cur=stop->right;
        }
    }
    return v;
}