#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node* right;
    struct Node* left;
};
struct Node* createNode(int data);
struct Node* insert(struct Node* node, int data);
bool hasEqualStructure(struct Node* thisNode, struct Node* otherNode);
int main() {
    int n = 0;
    int k = 0;
    scanf("%d %d",&n ,&k);
    int data = 0;
    int res = 1;
    struct Node* nodes[n];
    for (int i = 0; i < n; i++) {
        nodes[i] = createNode(0);
        for (int j = 0; j < k; j++) {
            scanf("%d",&data);
            nodes[i] = insert(nodes[i],data);
        }
    }
    for (int i=1; i<n; i++) {

        bool countIt = true;
        for (int j=0; j<i; j++) {
            if (hasEqualStructure(nodes[i], nodes[j])) {
                countIt = false;
                break;
            }
        }
        if (countIt) res++;
    }
    printf("%d\n",res);
    return 0;
}
int compareNulls(struct Node* node) {
    if (node->left == NULL && node->right == NULL)
        return -1;
    if (node->left == NULL || node->right == NULL)
        return 1;
    return 0;
}
bool hasEqualStructure(struct Node* thisNode, struct Node* otherNode) {
    bool ret = false;
    if (compareNulls(thisNode) == -1 && compareNulls(otherNode) == -1)
        return true;
    if (compareNulls(thisNode) != compareNulls(otherNode))
        return ret;
    if (compareNulls(thisNode) == 1 && ((thisNode->left == NULL && otherNode->left != NULL ) || (thisNode->right == NULL && otherNode->right != NULL)))
        return ret;
    if (thisNode->left != NULL)
        ret = hasEqualStructure(thisNode->left, otherNode->left);
    if (thisNode->right != NULL)
        ret = hasEqualStructure(thisNode->right, otherNode->right);
    return ret;
}
struct Node* insert(struct Node* node, int data){
    if(node == NULL){
        return createNode(data);
    } else if(data<= node->data){
        node->left = insert(node->left,data);
    }else{
        node->right = insert(node->right,data);
    }
    return node;
}
struct Node* createNode(int data){
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
