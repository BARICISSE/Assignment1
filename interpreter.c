#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "shellmemory.h"

void help();
void run();
void print();
void set();
int containsKey();

int interpreter(char **command, struct MEM * memarray){
    
    // maps command to corresponding function
    char *commandName = command[0];
    printf("commandnAME: %s\n", commandName);
    if(strcmp(commandName, "quit")==0){
        return -2;
    } else if(strcmp(commandName, "help")==0){
        help();
        return 0;

    } else if(strcmp(commandName, "set")==0){
       set(command, memarray);
        return 0;

    } else if(strcmp(commandName, "print")==0){
       // printf("=====ABOUT TO PRINT======\n");
        print(command, memarray);
        //printf("=====DONE PRINTING TO PRINT======\n");
        return 0;

    } else if(strcmp(commandName, "run")==0){
        run();
        return 0;

    }else {
        printf("Unknown command\n");
        return -1;
    }

    return 0;

}

void run(){

}
void print(char ** command, struct MEM * memarray){
    char varName[100];
    char *ptr1 = varName;
    ptr1 = strdup(command[1]);
    //printf("======checking contains:\n");
    int index =-1;
    for(int i=0; i<sizeof(memarray) && memarray[i].var != NULL; ++i){
         printf("CHAR IS : %s\n", memarray[i].var);
         if(strcmp(memarray[i].var, command[1])==0){
             index = i;
             break;
         }
     }
    if(index<0) printf("Variable does not exist\n");
    else if(index>=0){
        char *value =  memarray[index].value;
        printf("===VALUE IS : %s\n", value);
    }
}

void set(char ** command, struct MEM * memarray){
    char varName[100];
    char value[100];
    char *ptr1 = varName;
    char *ptr2 = value;

    strcpy(ptr1, command[1]);
    strcpy(ptr2, command[2]);
    
    for(int i=3; i<sizeof(command) & command[i] != NULL; i++){
        strcat(ptr2, command[i]);
    }
    
    struct MEM temp;
  
    int index =-1;
    for(int i=0; i<sizeof(memarray) && memarray[i].var != NULL; ++i){
         printf("CHAR IS : %s\n", memarray[i].var);
         if(strcmp(memarray[i].var, command[1])==0){
             printf("MEMARRAY CUR VAL IS : %s\n", memarray[i].var);
             printf("CONTAINS FOUND : %s\n", memarray[i].value);
             index = i;
             break;
         }
     }
    printf("Index is : %d\n", index);
   if(index >= 0){
        memarray[index].var = strdup(ptr1);
        memarray[index].value = strdup(ptr2);
    
   } else {
       printf("%s NOT FOUND\n", ptr1);
       
       for(int i=0; i<sizeof(memarray) && memarray[i].var!=NULL; ++i){
           printf("i is : %d\n", i);
           index = i;
       }
        
        // strcpy(temp.var, varName);
        // strcpy(temp.value, value);
        index = index + 1;
        memarray[index].var = strdup(ptr1);
        memarray[index].value = strdup(ptr2);
        // memarray[index].var = "none";
        // memarray[index].value = "none";
        // strcpy(memarray[index].var, varName);
        // strcpy(memarray[index].value, value);
        
        
       
   }

}
void help(){
    printf("help\nrun\nprint\nset\nquit\n");

}

int containsKey(struct MEM * memarray, char** command){
    int index = -1;
    printf("KEY IS : %s\n", command[1]);
     for(int i=0; i<sizeof(memarray) && memarray[i].var != NULL; ++i){
         printf("CHAR IS : %s\n", memarray[i].var);
         if(strcmp(memarray[i].var, command[1])==0){
             printf("MEMARRAY CUR VAL IS : %s\n", memarray[i].var);
             printf("CONTAINS FOUND : %s\n", memarray[i].value);
             return i;
         }
     }
     return index;
}
