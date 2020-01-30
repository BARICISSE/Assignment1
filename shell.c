#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<readline/history.h> 
#include "shellmemory.h"
#include "interpreter.h"

#define MAX_LEN 128


#define clear() printf("\033[H\033[J")
void print_image(FILE *fptr);
void printArt();
void initializeStruct(struct MEM* memarrayarray);

void parse(char *input, struct MEM** memarray, size_t *sizeMem);

void check_malloc(void *ptr) {
    if(ptr == NULL) {
        puts("failed to allocate memory!");
        exit(1);
    }
} 

int main(){
    clear();
    
    char input[1000];
    size_t size = 10;
    struct MEM *memarray = (struct MEM *) calloc(size, sizeof(struct MEM));
    check_malloc(memarray);
    
    printf("\nWelcome to the Ousmane Baricisse shell!\nVersion 1.0 Created January 2020\n$ ");
    while(1){
        
        fgets(input, 1000, stdin);
        if(input[strlen(input)-1] == '\r' || input[strlen(input)-1] == '\n'){
			input[strlen(input)-1] = '\0';
        }
        char *inputStr = input;
        
        parse(inputStr, &memarray, &size);
      
    }
     
    free(memarray);
    
    return 0;
}

void parse(char *input, struct MEM** memarray, size_t *sizeMem){
    char **command = malloc(1000*sizeof(char *));
    check_malloc(command);
    char *separator = " ";
    char *parsed;
    int index = 0;
    parsed = strtok(input, separator);
    
    
    while(parsed != NULL){
        command[index] = parsed;
        
        index++;

        parsed = strtok(NULL, separator);
      
    }
    int errorCode = 0;
    errorCode = interpreter(command, (size_t)(index), memarray, sizeMem);
    if(errorCode ==-2){
        printf("Bye!\n");
        _Exit(0);
    }
    
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