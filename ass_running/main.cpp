#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<cmath>
#include<conio.h>
#include"Stack.h"

#define INPUT_FILE "output.bin"
#define FILE_TO_WRITE_ERROR "log.txt"

void Print_in_log(char* error_info);
void Running(char* buffer);

void Print_in_log(char* error_info)
{
    FILE* log = fopen(FILE_TO_WRITE_ERROR, "a");
    assert(log);

    fprintf(log, "%s\n", error_info);

    fclose(log);
}

int main()
{
    FILE* input = fopen(INPUT_FILE, "rb");

    int count_fseek = fseek(input, 0, SEEK_END);

    if(count_fseek)
    {
        Print_in_log("ERROR with fseek in the end");
        return 1;
    }
    int end_file = ftell(input);

    count_fseek = fseek(input, 0, SEEK_SET);
    if(count_fseek)
    {
        Print_in_log("ERROR with fseek in the start");
        return 1;
    }
    int start_file = ftell(input);

    if(end_file <= start_file ||
        end_file == -1 || start_file == -1)
    {
        Print_in_log("ERROR with start and end of file");
        return 1;
    }

    unsigned int long_file = end_file - start_file;
    if(!std::isfinite(end_file) || !std::isfinite(long_file))
    {
        Print_in_log("ERROR: file is big");
        return 1;
    }

    char* buffer = (char*)calloc(sizeof(char), long_file);
    if(fread(buffer, sizeof(char), long_file, input) != long_file)
    {
        Print_in_log("ERROR in reading of input file\n");
        return 1;
    }

    Running(buffer);

    fclose(input);
    return 0;
}

typedef struct Processor
{
    Stack data;
    Stack return_codes;
    int rax;
    int rbx;
    int rcx;
    int rdx;
    int rci;
    int rdi;
    int rsp;
    int rbp;

    void initial()
    {
        Stack_init(&data);
        Stack_init(&return_codes);
        rax = 0;
        rbx = 0;
        rcx = 0;
        rdx = 0;
        rci = 0;
        rdi = 0;
        rsp = 0;
        rbp = 0;
    }
}Processor;

void Running(char* buffer)
{
    Processor processor;
    processor.initial();
    int count = 0;

    for(unsigned int i = 0; ;  )
    {
        switch (buffer[i])
        {
        #define CMD_DEF(name, num, code1, code2)         \
        case num:                                        \
            code2

            #include "C:\\Users\\User\\Desktop\\C\\assembler_compiling\\commands.h"
        }
        printf("buffer1: %d\n", buffer[i]);

        if(count)
            {break; printf("1");}
    }

}





























