#include <stdio.h>
#include <string.h>
#define MAX_L 256
#define MAX 100000

typedef struct Profile{
    char name[MAX_L];
    char email[MAX_L];
}Profile;

Profile students[MAX];
int k = 0;

void processLoad(char *filename){
    char name[MAX_L];
    char email[MAX_L];
    FILE* fptr = fopen(filename, "r");
    while(1){
        fgets(name, sizeof(name), fptr);
        if(strcmp(name, "#") == 0)break;
        k++;
        strcpy(students[k].name, name);
        fgets(email, sizeof(email), fptr);
        //printf("%s%s", name, email);
        //printf("%s\n%s\n", students[i]->name, name);
        strcpy(students[k].email, email);
    }
    fclose(fptr);
}

void printList(){
    printf("STT Infos\n");
    for (int i = 1; i <= k; i++)
    {
        printf("#%d. %s    %s", i, students[i].name, students[i].email);
    }
}
void main(){
    while(1){
        printf("Enter command: ");
        char cmd[256];
        scanf("%s", cmd);
        if(strcmp(cmd, "Quit")==0) break;
        else if(strcmp(cmd,"Load")==0) processLoad("profile5.txt");
        else if(strcmp(cmd,"Print")==0) printList();
        //else if(strcmp(cmd,"Find")==0) processFind();
        //else if(strcmp(cmd,"Insert")==0) processInsert();
        //else if(strcmp(cmd,"Remove")==0) processRemove();
        //else if(strcmp(cmd,"Store")==0) processStore();
    }
}