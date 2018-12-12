#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<cmath>
#include<conio.h>


#define FILE_TO_WRITE_ERROR     "log.txt"
#define INPUT_FILE              "input.txt"
#define OUTPUT_FILE             "C:\\Users\\User\\Desktop\\C\\asembler\\output.bin"
#define START_SIZE              100
#define MAX_SIZE_COMMAND        10
#define QUANTITY_LABELS         10
#define MAX_SIZE_NAME_LABEL     12

#define CMD_DEF(name, num, code1, code2) CMD_##name = num,

enum Commands
{
    #include "commands.h"
};

#undef CMD_DEF

void Print_in_log(char* error_info, int line);
void Compile(FILE* input, FILE* output);

void Print_in_log(char* error_info, int line)
{
    FILE* log = fopen(FILE_TO_WRITE_ERROR, "a");
    assert(log);

    if(line == -1)
        fprintf(log, "%s\n", error_info);
    else if (line >= 0)
        fprintf(log, "%s in line %d\n", error_info, line);
    else
        fprintf(log, "%s in unreal line\n", error_info);
    fclose(log);
}

int main()
{
    FILE* input = fopen(INPUT_FILE, "r");
    if(input == nullptr)
    {
        Print_in_log("ERROR with open input file", -1);
        return 1;
    }

    FILE* output = fopen(OUTPUT_FILE, "w+b");
    if(output == nullptr)
    {
        Print_in_log("ERROR with open output file", -1);
        return 1;
    }

    Compile(input, output);

    fclose(input);
    fclose(output);
    return 0;
}

typedef struct label
{
    int pointer_to_jump;
    char name[];
}label;

void Compile(FILE* input, FILE* output)
{
    char line[100];
    assert(line);
    assert(output);
    int c;
    int num_line = 0;
    label labels[QUANTITY_LABELS];

    for(int i = 0; i < QUANTITY_LABELS; i++)
    {
        labels[i].pointer_to_jump = -1;
        for(int j = 0; j < 10; j++)
            labels[i].name[j] = 0;

    }

    int now_label = 0; //quantity labels at the instance
    int quantity_lines = 0;

    while((c = fscanf(input, "%[^\n]\n", line)) != EOF)
    {
        //printf("%s\n", line);
        if(strlen(line) == 0)
        {
            num_line++;
            continue;
        }

        Print_in_log(line, num_line);
        char* pos_of_colon = 0;
        if(strstr(line, "//") != NULL)
            Print_in_log("Comment", num_line);

        #define CMD_DEF(name, num, code1, code2)        \
        else if(strstr(line, #name) != nullptr)         \
            code1

        #include "commands.h"

        else if((pos_of_colon = strstr(line, ":")) != NULL)
        {
            labels[now_label].pointer_to_jump = ftell(output);
            //printf("%d\n", output);
            //printf("\n%d\n", labels[now_label].pointer_to_jump);

            if(labels[now_label].pointer_to_jump == -1)
                Print_in_log("ERROR in ftell for output", num_line);
            strncpy(labels[now_label].name, line, (pos_of_colon - line));
            /*for(int i = 0; i < pos_of_colon-line; i++)
                printf("%c", labels[now_label].name[i]);*/
            labels[now_label].name[pos_of_colon - line] = '\0';

            now_label++;
        }
        else
        {
            Print_in_log("ERROR with command", num_line);
            exit(1);
        }
        num_line++;

    }

    quantity_lines = num_line;
    num_line = 0;
    if(fseek(input, 0, SEEK_SET) != 0)
    {
        Print_in_log("ERROR in going to start in input", -1);
        exit(1);
    }

    if(fseek(output, 0, SEEK_SET) != 0)
    {
        Print_in_log("ERROR in going to start in output", -1);
        exit(1);
    }

    while((c = fscanf(input, "%[^\n]\n", line)) != EOF)
    {
        //printf("%s\n", line);
        if(strlen(line) == 0)
        {
            num_line++;
            continue;
        }

        if(strstr(line, "//") != NULL)
            Print_in_log("Comment", num_line);

        #define CMD_DEF(name, num, code1, code2)        \
        else if(strstr(line, #name) != nullptr)         \
        {                                               \
            code1                                       \
        }

        #include "commands.h"

        num_line++;
    }

}
