#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<readline/history.h> 
#include "shellmemory.h"
#define MAX_LEN 128


#define clear() printf("\033[H\033[J")
void print_image(FILE *fptr);
void printArt();
void initializeStruct(struct MEM* memarrayarray);
void helper(char**command, size_t sizeCommand, struct MEM *memarray, size_t sizeMem);

char **parse(char *input, struct MEM* memarray, size_t sizeMem);


int main(){
    clear();
    char **command = malloc(1000*sizeof(char *));
    
    char input[1000];
    struct MEM *memarray = (struct MEM *) malloc(1000 * sizeof(struct MEM));
    //initializeStruct(memarray);
    //int j = 0;
   
    // for(j=0; j<sizeof(struct MEM); ++j){
    //     printf("CHAR FOR STRUCT %d : %s\n", j,  memarray[j].var);
    // }
    
    
    //printArt();
    printf("\nWelcome to the obaric shell!\nVersion 1.0 Created January 2020\n$ ");
    while(1){
        
        fgets(input, 1000, stdin);
        while(input[strlen(input)-1] == '\r' || input[strlen(input)-1] == '\n'){
			input[strlen(input)-1] = '\0';
        }
        char *inputStr = input;
        int size = 1000;
        size_t sizeMem = (size_t)size;
       // printf("\n SIZE OF MEMARRAY : %zu",sizeMem);
        command = parse(inputStr, memarray, sizeMem);
      
       free(command);
    }
     
    free(memarray);
    
    return 0;
}
void helper(char**command, size_t sizeCommand, struct MEM *memarray, size_t sizeMem){
        
        
        int i = interpreter(command, sizeCommand, memarray, sizeMem);
        if(i==-2){
               printf("Bye!\n");
               _Exit(0);
        } 
}
char **parse(char *input, struct MEM* memarray, size_t sizeMem){
    char **command = malloc(1000*sizeof(char *));
    char *separator = " ";
    char *parsed;
    int index = 0;
    parsed = strtok(input, separator);
    
    
    while(parsed != NULL){
        command[index] = parsed;
        //printf("commandss: %s\n", command[index]);
        index++;

        parsed = strtok(NULL, separator);
      
    }
    index++;
    
    command[index] = NULL;
    size_t sizeCommand = (size_t)(index);
    // printf("PARSED COMAND SIZE %zu\n", sizeCommand);
    helper(command, sizeCommand, memarray, sizeMem);
    return command;
}
void print_image(FILE *fptr)
{
    char read_string[MAX_LEN];
 
    while(fgets(read_string,sizeof(read_string),fptr) != NULL)
        printf("%s",read_string);
}
void printArt(){
    char *filename = "./image.txt";
    FILE *fptr = NULL;
 
    if((fptr = fopen(filename,"r")) == NULL)
    {
        fprintf(stderr,"error opening %s\n",filename);
        
    }
 
    print_image(fptr);
 
    fclose(fptr);
}

void initializeStruct(struct MEM * memarray){
    
    
    memset(memarray, 0, 1000*sizeof(struct MEM));

}