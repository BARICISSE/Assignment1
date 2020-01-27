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
char **parse(char *input){
    char **command = malloc(3*sizeof(char *));
    char *separator = " ";
    char *parsed;
    int index = 0;
    parsed = strtok(input, separator);
    while(parsed != NULL){
        command[index] = parsed;
        index++;

        parsed = strtok(NULL, separator);
    }
    command[index] = NULL;
    return command;
}
void print_image(FILE *fptr);
void printArt();
int main(){
    clear();
    char **command;
    char *input;
    pid_t child_pid;
    int stat_loc;
    while(1){
        
        printArt();
        printf("\nWelcome to the obaric shell!\n Version 1.0 Created January 2020\n");
        scanf("$%s", input);
        printf("input is : %s", input);
    }
    
    
    return 0;
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