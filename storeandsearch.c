#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Treenode{
    char name[256];
    struct Treenode *left;
    struct Treenode *right;
} NODE;

NODE* Profile;

NODE* makeNode(char *name){
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    strcpy(newNode->name, name);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//Chen nut
void Insert(char *name){
    if(Profile == NULL) Profile = makeNode(name);
    else {
            NODE *Root = Profile;
            while(Root != NULL) {
                if(strcmp(Root->name, name) > 0) {
                    if(Root->left == NULL) {
                        Root->left = makeNode(name);
                        break;
                    }
                    Root = Root->left;
                }
                else if(strcmp(Root->name, name) < 0) {
                    if(Root->right == NULL) {
                        Root->right = makeNode(name);
                        break;
                    }
                    Root = Root->right;
                }
                else return;
            }
    }
}

NODE* Find(char *name){
    NODE* Root = Profile;
    while(Root != NULL){
        if(strcmp(Root->name, name) > 0) Root = Root->left;
        else if(strcmp(Root->name, name) < 0) Root = Root->right;
        else return Root;
    }
    return NULL;
}

void printTree(NODE* root){
    if(root == NULL)return;
    printf("%s ", root->name);
    if(root->left != NULL) printf("%s ", root->left->name);
    else printf("-1 ");
    if(root->right != NULL) printf("%s ", root->right->name);
    else printf("-1 ");
    printf("\n");
    printTree(root->left);
    printTree(root->right);
}

int main(){
    char name[256];
    char cmd[256];
    while(strcmp(name, "*") != 0){
        scanf("%s", name);
        if(strcmp(name, "*") != 0)Insert(name);
    }
    //printTree(Profile);
    int i = 0;
    int s[10000];
    while(1){
        fflush(stdin);
        scanf("%s", cmd);
        if(strcmp(cmd, "***") == 0)break;
        scanf("%s", name);
        //printf("%s %s\n", cmd, name);
        if(strcmp(cmd, "find") == 0){
            if(Find(name) != NULL) s[i] = 1;
            else s[i] = 0;
        }
        if(strcmp(cmd, "insert") == 0){
            if(Find(name) == NULL){
                Insert(name);
                s[i] = 1;
            }
            else s[i] = 0;
        }
        i++;
    }
    for(int j = 0; j < i; j++) printf("%d\n", s[j]);
    return 0 ;
}