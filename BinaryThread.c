#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct ThreadNode {
    int data;
    struct ThreadNode* left;
    struct ThreadNode* right;
    int lthread;
    int rthread;
} ThreadNode;

TreeNode* CreateNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

TreeNode* InsertBST(TreeNode* root, int data) {
    if (root == NULL) {
        return CreateNode(data);
    }
    if (data < root->data) {
        root->left = InsertBST(root->left, data);
    }
    else {
        root->right = InsertBST(root->right, data);
    }
    return root;
}

TreeNode* GenerateBinaryTree(int inputData[], int n) {
    TreeNode* root = NULL;
    for (int i = 0; i < n; i++) {
        root = InsertBST(root, inputData[i]);
    }
    return root;
}

void BinaryTreeInOrder(TreeNode* root) {
    if (root != NULL) {
        BinaryTreeInOrder(root->left);
        printf("%d ", root->data);
        BinaryTreeInOrder(root->right);
    }
}

ThreadNode* CreateThreadNode(int data) {
    ThreadNode* newNode = (ThreadNode*)malloc(sizeof(ThreadNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->lthread = 1;
    newNode->rthread = 1;
    return newNode;
}

ThreadNode* InsertThreadTree(ThreadNode* root, ThreadNode* newNode) {
    if (root == NULL) {
        return newNode;
    }

    ThreadNode* current = root;
    ThreadNode* parent = NULL;

    while (current != NULL) {
        parent = current;
        if (newNode->data < current->data) {
            if (current->lthread == 0) {
                current = current->left;
            }
            else {
                break;
            }
        }
        else {
            if (current->rthread == 0) {
                current = current->right;
            }
            else {
                break;
            }
        }
    }

    if (newNode->data < parent->data) {
        newNode->left = parent->left;
        newNode->right = parent;
        parent->lthread = 0;
        parent->left = newNode;
    }
    else {
        newNode->right = parent->right;
        newNode->left = parent;
        parent->rthread = 0;
        parent->right = newNode;
    }

    return root;
}

ThreadNode* GenerateThreadTree(int inputData[], int n) {
    ThreadNode* root = NULL;
    for (int i = 0; i < n; i++) {
        ThreadNode* newNode = CreateThreadNode(inputData[i]);
        root = InsertThreadTree(root, newNode);
    }
    return root;
}

ThreadNode* Leftmost(ThreadNode* node) {
    if (node == NULL) return NULL;
    while (node->lthread == 0) {
        node = node->left;
    }
    return node;
}

void ThreadTreeInOrder(ThreadNode* root) {
    ThreadNode* current = Leftmost(root);
    while (current != NULL) {
        printf("%d ", current->data);
        if (current->rthread == 1) {
            current = current->right;
        }
        else {
            current = Leftmost(current->right);
        }
    }
}

int main() {
    int inputData[] = { 4, 1, 9, 13, 15, 3, 6, 14, 7, 10, 12, 2, 5, 8, 11 };
    int n = sizeof(inputData) / sizeof(inputData[0]);

    TreeNode* root = GenerateBinaryTree(inputData, n);
    printf("Binary tree inorder : ");
    BinaryTreeInOrder(root);
    printf("\n");

    ThreadNode* troot = GenerateThreadTree(inputData, n);
    printf("Thread tree inorder : ");
    ThreadTreeInOrder(troot);
    printf("\n");

    free(root);
    free(troot);

    return 0;
}