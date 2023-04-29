#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10000
#define MAX_L 256

typedef struct NODETREE{
    int id;
    struct NODETREE* next;
} NODE;

NODE* Head;
NODE* Last; 

NODE* Make_Node(int index){
    NODE* New_Node = (NODE*)malloc(sizeof(NODE));
    New_Node->id = index;
    New_Node->next = NULL;
    return New_Node;
}

void Insert(int index){
    if(Head == NULL){
        Head = Make_Node(index);
        Last = Head;
    }
    else{
        Last->next = Make_Node(index);
        Last = Last->next;
    }
    return;
}

int Find(int index){
    NODE* root = Head;
    while(root != NULL){
        if(root->id == index) return 1;
        root = root->next;     
    }
    return 0;
}

void Add_Last(int index){
    if(Find(index)) return;
    Last->next = Make_Node(index);
    Last = Last->next;
}

void Add_First(int index){
    if(Find(index)) return;
    NODE* New_Node = Make_Node(index);
    New_Node->next = Head;
    Head = New_Node;
}

void Add_Before(int index, int here){
    if(Find(index)) return;
    
    NODE* NewNode;
    NODE* root = Head;
    
    if(Head->id == here){ //khi here o dau danh sach
        NewNode = Make_Node(index);
        NewNode->next = Head;
        Head = NewNode;
        return;
    }

    while(root->next != NULL){
        if(root->next->id == here){ //tim kiem phan tu (root) ke truoc here
            NODE* tmp;
            NewNode = Make_Node(index);
            tmp = root->next; //chen tmp vao giua here va root
            root->next = NewNode;
            NewNode->next = tmp;
            return;
        }
        root = root->next;
    }
}

void Add_After(int index, int here){
    if(Find(index)) return;

    NODE* root = Head;
    NODE* NewNode;

    while(root != NULL){
        if(root->id == here){
            NODE* tmp; 
            NewNode = Make_Node(index); 
            tmp = root->next; //chen NewNode vao giua
            root->next = NewNode;
            NewNode->next = tmp;
            if(root == Last) Last = NewNode;
            return;
        }
        root = root->next;     
    }
}

void Remove(int index){
    if( ! Find(index)) return;

    NODE* root = Head;

    if(Head->id == index){ //neu index o dau danh sach
        Head = root->next;
        free(root);
        return;
    } 

    while(root->next != NULL){ //dung root->next vi neu index o cuoi danh sach thi cap nhat lai last = root
        if(root->next->id == index){
            NODE* tmp = root->next; //xoa tmp
            root->next = tmp->next;
            if(tmp == Last) Last = root; //neu tmp o cuoi
            free(tmp);
            return;
        }
        root = root->next;
    }
}

void Reverse(){
    NODE* tmp = Last; //doi cho head va last, cap nhat lai head, last moi
    Last->next = Head;
    Last = Head;
    Head = tmp;

    NODE* key = Last;
    NODE* next;
    tmp = Last->next; //chen lan luon tmp vao giua head va key
    while(tmp != Head){
        next = tmp->next;
        Head->next = tmp;
        tmp->next = key; 
        key = tmp;
        tmp = next;
    }
    Last->next = NULL;
}

void Load_Data(){
    int n, id;
    //printf("Nhap data: \n");
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d", &id);
        Insert(id);
    }
    //printf("1");
}

void Load_File(){
    int id, n;
    FILE* fptr = fopen("data.txt", "r");
    fscanf(fptr, "%d", &n);
    while( ! feof(fptr) ){
        fscanf(fptr, "%d", &id);
        //printf("%d ", id);
        Insert(id);
    }
}

void Print_List(){
    //printf("1");
    NODE* root = Head;
    while(root != NULL){
        printf("%d ", root->id);
        root = root->next;
    }
    printf("\n");
    return;
}

int main()
{
    char cmd[MAX_L];
    int index, here;
    Load_Data();
    while(1){
        fflush(stdin);
        scanf("%s", cmd);

        if( ! strcmp(cmd, "#") ) break;
        if( ! strcmp(cmd, "Print") ) Print_List();
        if( ! strcmp(cmd, "addfirst") ) {
            scanf("%d", &index);
            Add_First(index);
        }
        if( ! strcmp(cmd, "addlast") ) {
            scanf("%d", &index);
            Add_Last(index);
        }
        if( ! strcmp(cmd, "addafter") ) {
            scanf("%d%d", &index, &here);
            Add_After(index, here);
        }
        if( ! strcmp(cmd, "addbefore") ) {
            scanf("%d%d", &index, &here);
            Add_Before(index, here);
        }
        if( ! strcmp(cmd, "remove") ) {
            scanf("%d", &index);
            Remove(index);
        }
        if( ! strcmp(cmd, "reverse") ) {
            Reverse();
        }
    }
    Print_List();
    return 0;
}