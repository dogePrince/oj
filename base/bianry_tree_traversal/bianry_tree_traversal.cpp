#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<stack>

using namespace std;

typedef struct TN{
    int val;
    struct TN *left;
    struct TN *right;
}TreeNode;

void insert_node(TreeNode* &root, TreeNode* p){
    if (root == NULL) {
        root = p;
    }
    else {
        if (p->val < root->val) {
            insert_node(root->left, p);
        }
        else {
            insert_node(root->right, p);
        }
    }
}

vector<int> PostTraversal(TreeNode *root) {
    vector<int> result;

    stack<TreeNode*> TS;

    TreeNode *p = root;
    TreeNode *temp = p;

    while (!TS.empty() || p != NULL) {
        while (p != NULL) {
            TS.push(p);
            p = p->left;
        }
        p = TS.top();
        if (p->right != NULL && temp != p->right) {
            p = p->right;
        }
        else {
            result.push_back(p->val);
            TS.pop();
            temp = p;
            p = NULL;
        }
    }
    return result;
}

int main(int argc, char const *argv[]) {
    int n;
    scanf("%d", &n);
    TreeNode *root = NULL;
    for (int i = 0; i < n; i++) {
        TreeNode *p = (TreeNode*)malloc(sizeof(TreeNode));
        scanf("%d", &(p->val));
        p->left = NULL;
        p->right = NULL;
        insert_node(root, p);
    }
    vector<int> res = PostTraversal(root);
    for (vector<int>::iterator it = res.begin(); it != res.end(); it++) {
        printf("%d ", *it);
    }
    reverse(res.begin(), res.end());
    for (vector<int>::iterator it = res.begin(); it != res.end(); it++) {
        printf("%d ", *it);
    }
    return 0;
}
