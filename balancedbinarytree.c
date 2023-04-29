#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 10000
#define MAX_L 256

typedef struct TreeNode{
    int data;
    int height;
    int place; //vi tri left or right (0 or 1)
    struct TreeNode* left;
    struct TreeNode* right;
}NODE;

NODE* root;
int HeightLeftTree;
int HeightRightTree;

NODE* Make_Node(int data){
    NODE* NewNode = (NODE*)malloc(sizeof(NODE));
    NewNode->data = data;
    NewNode->height = 0;
    NewNode->left = NULL;
    NewNode->right = NULL;
    return NewNode;
}

NODE* Find_Node(NODE* root, int data){
    //printf("1");
    if(root == NULL) return NULL;
    if(root->data == data) return root;
    NODE* find = Find_Node(root->left, data);
    if(find != NULL && find->data == data) return find;
    find = Find_Node(root->right, data);
    if(find != NULL && find->data == data) return find;

    return NULL;
}

void Make_Root(int data){
    free(root);
    root = Make_Node(data);
    root->height = 1;
    HeightLeftTree = 1;
    HeightRightTree = 1;
}

void Add_Left(int data, int parent){
    if(Find_Node(root, data) != NULL) return;
    NODE* ParentNode = Find_Node(root, parent);
    if(ParentNode == NULL) return;
    NODE* tmp = ParentNode->left; // tmp bi don xuong duoi
    ParentNode->left = Make_Node(data);
    ParentNode->left->left = tmp;

    if(ParentNode == root) ParentNode->left->place = 0;
    else ParentNode->left->place = ParentNode->place;

    ParentNode->left->height = ParentNode->height + 1; // cap nhat chieu cao cua node
    if(ParentNode->place == 0){

        if(ParentNode->left->height > HeightLeftTree)//cap nhat chieu cao cua cay
            HeightLeftTree = ParentNode->left->height;
    }
    else {
        if(ParentNode->left->height > HeightRightTree)//cap nhat chieu cao cua cay
            HeightRightTree = ParentNode->left->height;
    }
    //printf("1");
}

void Add_Right(int data, int parent){
    if(Find_Node(root, data) != NULL) return;
    NODE* ParentNode = Find_Node(root, parent);
    if(ParentNode == NULL) return;
    NODE* tmp = ParentNode->right; // tmp bi don xuong duoi
    ParentNode->right = Make_Node(data);
    ParentNode->right->right = tmp;

    if(ParentNode == root) ParentNode->right->place = 1;
    else ParentNode->right->place = ParentNode->place;

    ParentNode->right->height = ParentNode->height + 1;// cap nhat chieu cao cua node
    if(ParentNode->place == 1){

        if(ParentNode->right->height > HeightRightTree)//cap nhat chieu cao cua cay
            HeightRightTree = ParentNode->right->height;
    }
    else {
        if(ParentNode->right->height > HeightLeftTree)//cap nhat chieu cao cua cay
            HeightLeftTree = ParentNode->right->height;
    }
    //printf("1");
}

void printTree(NODE* root){
    if(root == NULL)return;
    printf("%d ", root->data);
    if(root->left != NULL) printf("%d ", root->left->data);
    else printf("-1 ");
    if(root->right != NULL) printf("%d ", root->right->data);
    else printf("-1 ");
    printf("\n");
    printTree(root->left);
    printTree(root->right);
}


int main()
{
    char cmd[MAX_L];
    int data, parent;
    while(1){
        fflush(stdin);
        scanf("%s", cmd);
        if( ! strcmp(cmd, "MakeRoot") ){
            scanf("%d", &data);
            Make_Root(data);
        }
        if( ! strcmp(cmd, "AddLeft") ){
            scanf("%d%d", &data, &parent);
            Add_Left(data, parent);
        }
        if( ! strcmp(cmd, "AddRight") ){
            scanf("%d%d", &data, &parent);
            Add_Right(data, parent);
        }
        if( ! strcmp(cmd, "*") ){
            break;
        }
        
    }
    if(HeightLeftTree == HeightRightTree) printf("1 %d", HeightLeftTree);
    else if(HeightLeftTree > HeightRightTree) printf("0 %d", HeightLeftTree);
    else printf("0 %d", HeightRightTree);
    return 0;
}