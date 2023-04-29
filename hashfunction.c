#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_L 256
#define MAX 100

typedef struct NODE{
    char Name[MAX_L];
    char Email[MAX_L];
    struct NODE* left;
    struct NODE* right;
}NODE;

NODE* hash_Table[MAX];

void init(){
    for (int i = 0; i < MAX; i++)
        hash_Table[i] = NULL;
    
    return;
}

NODE* make_node(char *name, char *email){
    NODE* newnode = (NODE*)malloc(sizeof(NODE));
    strcpy(newnode->Name, name);
    strcpy(newnode->Email, email);
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

int hash_function(char *name){
    int n = strlen(name);
    int rs = 0;
    for(int i = 0; i < n; i++){
        //printf("%c\n", name[i]);
        rs = (rs * 255 + name[i]) % MAX;
    }
    //printf("1");
    return rs;
}

void Insert_Profile(NODE** root, char *name, char *email){
    if(*root == NULL){
        NODE* new_node = make_node(name, email);
        *root = new_node;
        //printf("1");
        return;
    }

    NODE* tmp = *root;
    if(strcmp(tmp->Name, name) > 0){
        Insert_Profile(&(tmp->left), name, email);
    }
    else if(strcmp(tmp->Name, name) < 0){
        Insert_Profile(&(tmp->right), name, email); 
    }
    //printf("1");
}

void Insert_hashtable(char *name, char *email){
    int index = hash_function(name);
    //printf("%d\n", index);
    //printf("1");
    Insert_Profile(&hash_Table[index], name, email);
    //printf("1\n");
}

void Insert(){
    char name[MAX_L], email[MAX_L];
    fflush(stdin);
    scanf("%s %s", name, email);
    Insert_hashtable(name, email);
}

void Find_Profile(){
    char name[MAX_L];
    int id;
    fflush(stdin);
    scanf("%s", name);

    id = hash_function(name);

    NODE* tmp = hash_Table[id]; //con tro tim kiem vi tri
    if(tmp == NULL) {
        printf("Not found\n");
        return;
    }

    while(strcmp(tmp->Name, name) != 0){
        if(strcmp(tmp->Name, name) > 0) 
            tmp = tmp->left;
        else tmp = tmp->right;
    }

    printf("%d %s\n", id, tmp->Email);
}

void Find_Replace_Node(NODE** tmp, NODE** root){
    if((*root)->left)
        Find_Replace_Node(tmp, &((*root)->left));
    else{
        strcpy((*tmp)->Name, (*root)->Name);
        strcpy((*tmp)->Email, (*root)->Email);
        (*tmp) = (*root);
        (*root) = (*root)->right;
    }
    return;
}

void Remove_Data(NODE** root, char *name){
    //printf("1");
    if(strcmp((*root)->Name, name) > 0) 
        Remove_Data(&(*root)->left, name);
    else if(strcmp((*root)->Name, name) < 0) 
        Remove_Data(&(*root)->right, name);
    else{
        NODE* tmp;
        //printf("1\n");
        if((*root)->left == NULL)
            (*root) = (*root)->right;
        else if((*root)->right == NULL)
            (*root) = (*root)->left;
        else{
            tmp = (*root);
            Find_Replace_Node(&tmp, &(*root)->right);
        }
        free(tmp);
    }
    return;
}

void Load_Data(){
    int n;
    char name[MAX_L], email[MAX_L];
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        fflush(stdin);
        scanf("%s %s", name, email);
        Insert_hashtable(name, email);
    }
}

void Load_File(){
    char name[MAX_L];
    char email[MAX_L];
    FILE* fptr = fopen("lab1.txt", "r");
    while(1){
        //fflush(fptr);
        fscanf(fptr, "%s", name);
        if(strcmp(name, "#") == 0)break;
        fscanf(fptr, "%s", email);
        //printf("%s\n%s\n", students[i]->name, name);
        Insert_hashtable(name, email);
    }
    fclose(fptr);
}

void Store(NODE* root, FILE* fptr, int id){
    if(root == NULL) return;
    Store(root->left, fptr, id);
    fprintf(fptr, "%d %s %s\n", id, root->Name, root->Email);
    Store(root->right, fptr, id);
}

void Export_File(){
    FILE* fptr = fopen("profile.txt", "w");
    for(int i = 0; i < MAX; i++){
        if(hash_Table[i] != NULL){
            if(hash_Table[i]->left != NULL || hash_Table[i]->right != NULL) 
                Store(hash_Table[i], fptr, i);
            else 
                fprintf(fptr, "%d %s %s\n", i, hash_Table[i]->Name, hash_Table[i]->Email);
        }
    }
    fclose(fptr);
}

void printTree(NODE* root){
    //printf("1");
    if(root == NULL)return;
    printf("%s ", root->Name);
    if(root->left != NULL) printf("%s ", root->left->Name);
    else printf("-1 ");
    if(root->right != NULL) printf("%s ", root->right->Name);
    else printf("-1 ");
    printf("\n");
    printTree(root->left);
    printTree(root->right);
}

void Print(){
    for(int i = 0; i < MAX; i++){
        if(*(&hash_Table[i]) != NULL) {
            printf("%s, %s\n", hash_Table[i]->Name, hash_Table[i]->Email);
            if(*(&hash_Table[i]->left) != NULL || *(&hash_Table[i]->right) != NULL){
                printf("*\n");
                printTree(hash_Table[i]);
                printf("*\n");
            }
        }
    }
}

int main()
{
    char cmd[MAX_L];
    init();
    while(1){
        //printf("Enter a command: ");
        fflush(stdin);
        scanf("%s", cmd);
        if(strcmp(cmd, "Quit") == 0) {
            printf("Bye\n");
            break;
        }
        if(strcmp(cmd, "Load") == 0) Load_File();
        if(strcmp(cmd, "Print") == 0) Print();
        if(strcmp(cmd, "Insert") == 0) Insert();
        if(!strcmp(cmd, "Find")) Find_Profile();
        if(!strcmp(cmd, "Remove")){
            char name[MAX_L];
            fflush(stdin);
            scanf("%s", name);
            int id = hash_function(name);
            Remove_Data(&hash_Table[id], name);
        }
        if(!strcmp(cmd, "Store")) Export_File();
    }
    return 0;
}