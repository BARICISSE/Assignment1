#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "shellmemory.h"
#include "shell.h"
#define S 0
void help();
void run(char **command, size_t sizeCommand, struct MEM **memarray, size_t *sizeMem);
void print(char **command, size_t sizeCommand, struct MEM **emarray, size_t *sizeMem);
void set(char **command, size_t sizeCommand, struct MEM **memarray, size_t *sizeMem);

int containsKey();

int interpreter(char **command, size_t sizeCommand, struct MEM **memarray, size_t *sizeMem)
{

    // maps command to corresponding function
    char *commandName = command[0];
    //printf("commandnAME: %s\n", commandName);
    if (strcmp(commandName, "quit") == 0 && sizeCommand == 1)
    {
        return -2;
    }
    else if (strcmp(commandName, "help") == 0 && sizeCommand == 1)
    {
        help();
        return 0;
    }
    else if (strcmp(commandName, "set") == 0 && sizeCommand == 3)
    {
        set(command, sizeCommand, memarray, sizeMem);
        return 0;
    }
    else if (strcmp(commandName, "print") == 0 && sizeCommand == 2)
    {
        print(command, sizeCommand, memarray, sizeMem);
        
        return 0;
    }
    else if (strcmp(commandName, "run") == 0 && sizeCommand == 2)
    {
        run(command, sizeCommand, memarray, sizeMem);
        return 0;
    }
    else
    {
        printf("Unknown command\n");
        return -1;
    }

    return 0;
}
void run(char **command, size_t sizeCommand, struct MEM **memarray, size_t *sizeMem)
{
    const char *filename = command[1];
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Script not found\n");
        return;
    }
    char *line = malloc(sizeof(char) * 1000);
    check_malloc(line);

    while (fgets(line, 1000, file))
    {
        int len = strlen(line);
        if(line[len - 1] == '\n')
        {
            line[len - 1] = '\0';
        }
        if(line[len - 2] == '\r') {
            line[len - 2] = '\0';
        }
        parse(line, memarray, sizeMem);

    }

    fclose(file);
}
void print(char **command, size_t sizeCommand, struct MEM **memarray, size_t *sizeMem)
{
    int index = -1;
    for (int i = 0; i < *sizeMem && (*memarray)[i].var != NULL; i++)
    {
        if (strcmp((*memarray)[i].var, command[1]) == 0)
        {
            index = i;
            break;
        }
    }
    if (index < 0)
        printf("Variable does not exist\n");
    else if (index >= 0)
    {
        char *value = (*memarray)[index].value;
        printf("%s\n", value);
    }
}

void set(char **command, size_t sizeCommand, struct MEM **memarray, size_t *sizeMem)
{
    char *key = strdup(command[1]);
    char *val = strdup(command[2]);


    int index = -1;
    for (int i = 0; i < *sizeMem && (*memarray)[i].var != NULL; i++)
    {
        if (strcmp((*memarray)[i].var, key) == 0)
        {

            index = i;
            break;
        }
    }

    if (index >= 0)
    {
        (*memarray)[index].value = val;
    }
    else
    {
        int i;
        for (i = 0; i < *sizeMem && (*memarray)[i].var != NULL; i++);

        if (i >= *sizeMem)
        {
            *sizeMem *= 2;
            *memarray = realloc(*memarray, *sizeMem * sizeof(struct MEM));
            check_malloc(memarray);
            for(int ctr = i; ctr < *sizeMem; ctr++) {
                (*memarray)[ctr].var = NULL;
                (*memarray)[ctr].value = NULL;
            }
        }
        (*memarray)[i].var = key;
        (*memarray)[i].value = val;
    }
}
void help()
{
    printf("COMMAND                 DESCRIPTION \n");
    printf("help                   Displays all the commands \n");
    printf("quit                   Exits / terminates the shell with Bye!\n");
    printf("set VAR STRING         Assigns a value to shell memory \n");
    printf("print VAR              Prints the STRING assigned to VAR \n");
    printf("run SCRIPT.TXT         Executes the file SCRIPT.TXT \n");
}

