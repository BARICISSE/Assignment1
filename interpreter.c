#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "shellmemory.h"
#include "shell.h"

void help();
void run(char **command, size_t sizeCommand, struct MEM * memarray, size_t sizeMem);
void print(char **command, size_t sizeCommand, struct MEM * memarray, size_t sizeMem);
void set(char **command, size_t sizeCommand, struct MEM * memarray, size_t sizeMem);

int containsKey();

int interpreter(char **command, size_t sizeCommand, struct MEM * memarray, size_t sizeMem){
    
    // maps command to corresponding function
    char *commandName = command[0];
    //printf("commandnAME: %s\n", commandName);
    if(strcmp(commandName, "quit")==0){
        return -2;
    } else if(strcmp(commandName, "help")==0){
        help();
        return 0;

    } else if(strcmp(commandName, "set")==0){
       set(command, sizeCommand, memarray, sizeMem);
        return 0;

    } else if(strcmp(commandName, "print")==0){
       // printf("=====ABOUT TO PRINT======\n");
        print(command, sizeCommand, memarray, sizeMem);
        //printf("=====DONE PRINTING TO PRINT======\n");
        return 0;

    } else if(strcmp(commandName, "run")==0){
        run(command, sizeCommand, memarray, sizeMem);
        return 0;

    }else {
        printf("Unknown command\n");
        return -1;
    }

    return 0;

}
void run(char **command, size_t sizeCommand, struct MEM * memarray, size_t sizeMem){
    // printf("SIZE COMMAD : %zu", sizeCommand);
    // printf("SIZE MEMORY : %zu", sizeMem);
    const char *filename = command[1];
    FILE *file = fopen(filename, "r");
    if(file==NULL){
        printf("Script not found\n");
        return;
    }
    char line[1000];
    char **arrayLines = malloc(1000*sizeof(char *));
    char ** command2;
    int i = 0;
    
    while(fgets(line, sizeof(line), file)){
        while(line[strlen(line)-1] == '\r' || line[strlen(line)-1] == '\n'){
			line[strlen(line)-1] = '\0';
        }
         arrayLines[i] = strdup(line);
        
        i++;
    }
   
    //int size = (int)sizeof(arrayLines)/sizeof(arrayLines[0]);
    
    fclose(file);
    int errorCode = 0;
    size_t nsizeCommand = (size_t)(i+1);
    int fileSize = i +1;
    printf("FILE SIZE COMMAND-- : %zu\n", nsizeCommand);
    int j = 0;
    while(j< nsizeCommand-1){
        char *ptr = arrayLines[j];
        
        command2 = parse(ptr, memarray, sizeMem);
        interpreter(command2,  nsizeCommand, memarray, sizeMem);
       // printf("j is : %d\n", j);
        j++;
       
    }

    free(command2);
    free(arrayLines);
}
void print(char **command, size_t sizeCommand, struct MEM * memarray, size_t sizeMem){
    char varName[100];
    char *ptr1 = varName;
    ptr1 = strdup(command[1]);
    //printf("======checking contains:\n");
    int index =-1;
    for(int i=0; i<sizeMem && memarray[i].var != NULL; ++i){
        //  printf("CHAR IS : %s\n", memarray[i].var);
         if(strcmp(memarray[i].var, command[1])==0){
             index = i;
             break;
         }
     }
    if(index<0) printf("Variable does not exist\n");
    else if(index>=0){
        char *value =  memarray[index].value;
        printf("%s\n", value);
    }
}

void set(char **command, size_t sizeCommand, struct MEM * memarray, size_t sizeMem){
    //  printf("SIZE COMMAD : %zu\n", sizeCommand);
    //  printf("SIZE MEMORY : %zu\n", sizeMem);
    char varName[100];
    char value[100];
    char *ptr1 = varName;
    char *ptr2 = value;

    strcpy(ptr1, command[1]);
    strcpy(ptr2, command[2]);
    
    for(int i=3; i<sizeCommand & command[i] != NULL; i++){
        strcat(ptr2, " ");
        strcat(ptr2, command[i]);
        
    }
    
    int index = -1;
    for(int i=0; i<sizeMem && memarray[i].var != NULL; i++){
         // printf("CHAR IS : %s\n", memarray[i].var);
         if(strcmp(memarray[i].var, ptr1)==0){
            //  printf("MEMARRAY CUR VAL IS : %s\n", memarray[i].var);
            //  printf("CONTAINS FOUND : %s\n", memarray[i].value);
             index = i;
             break;
         }
     }
    printf("Mem size is : %d\n", index);
   if(index >= 0){
        memarray[index].value = strdup(ptr2);
        
   } else {
    //    printf("%s NOT FOUND\n", ptr1);
       
       for(int i=0; i<sizeMem && memarray[i].var!=NULL; i++){
           //printf("i is : %d\n", i);
           index = i;
       }
        
        index = index + 1;
        if(index>=sizeMem){
            sizeMem = 2*sizeMem;
            memarray = realloc(memarray, sizeMem);
            
        }
        memarray[index].var = strdup(ptr1);
        memarray[index].value = strdup(ptr2);
       
       
   }

}
void help(){
    printf("COMMAND                 DESCRIPTION \n");
	printf("help                   Displays all the commands \n");
	printf("quit                   Exits / terminates the shell with Bye!\n");
	printf("set VAR STRING         Assigns a value to shell memory \n");
	printf("print VAR              Prints the STRING assigned to VAR \n");
	printf("run SCRIPT.TXT         Executes the file SCRIPT.TXT \n");
	

}

int containsKey(struct MEM * memarray, char** command, size_t sizeMem){
    int index = -1;
    // printf("KEY IS : %s\n", command[1]);
     for(int i=0; i<(int)sizeof(memarray) && memarray[i].var != NULL; ++i){
        //  printf("CHAR IS : %s\n", memarray[i].var);
         if(strcmp(memarray[i].var, command[1])==0){
            //  printf("MEMARRAY CUR VAL IS : %s\n", memarray[i].var);
            //  printf("CONTAINS FOUND : %s\n", memarray[i].value);
             return i;
         }
     }
     return index;
}

