
#define COMMANDS_H_INCLUDED

#include <iostream>


CMD_DEF(pushr, 9,
        {
            char command[2];
            command[0] = 9;
            command[1] = 0;

            if(strcmp(line + 6, "rax") == 0)
                command[1] = 1;
            else if(strcmp(line + 6, "rbx") == 0)
                command[1] = 2;
            else if(strcmp(line + 6, "rcx") == 0)
                command[1] = 3;
            else if(strcmp(line + 6, "rdx") == 0)
                command[1] = 4;
            else if(strcmp(line + 6, "rci") == 0)
                command[1] = 5;
            else if(strcmp(line + 6, "rdi") == 0)
                command[1] = 6;
            else if(strcmp(line + 6, "rsp") == 0)
                command[1] = 7;
            else if(strcmp(line + 6, "rbp") == 0)
                command[1] = 8;
            else
            {
                Print_in_log("ERROR in name of register", num_line);
                assert(!"pushr");
            }

            if(fwrite(&command, sizeof(char), 1, output) <= 0)
            {
                printf("ERROR\n");
                exit(1);
            }
        },

        {
            i++;
            switch (buffer[i])
            {
            case 1:
                push(&processor.data, processor.rax);
                break;
            case 2:
                push(&processor.data, processor.rbx);
                break;
            case 3:
                push(&processor.data, processor.rcx);
                break;
            case 4:
                push(&processor.data, processor.rdx);
                break;
            case 5:
                push(&processor.data, processor.rci);
                break;
            case 6:
                push(&processor.data, processor.rdi);
                break;
            case 7:
                push(&processor.data, processor.rsp);
                break;
            case 8:
                push(&processor.data, processor.rbp);
                break;
            }
            i++;
            break;
        })

CMD_DEF(popr, 10,
        {
            char command[2];
            command[0] = 9;
            command[1] = 0;

            if(strcmp(line + 6, "rax") == 0)
                command[1] = 1;
            else if(strcmp(line + 6, "rbx") == 0)
                command[1] = 2;
            else if(strcmp(line + 6, "rcx") == 0)
                command[1] = 3;
            else if(strcmp(line + 6, "rdx") == 0)
                command[1] = 4;
            else if(strcmp(line + 6, "rci") == 0)
                command[1] = 5;
            else if(strcmp(line + 6, "rdi") == 0)
                command[1] = 6;
            else if(strcmp(line + 6, "rsp") == 0)
                command[1] = 7;
            else if(strcmp(line + 6, "rbp") == 0)
                command[1] = 8;
            else
            {
                Print_in_log("ERROR in name of register", num_line);
                exit(1);
            }

            if(fwrite(&command, sizeof(char), 2, output) <= 0)
            {
                printf("ERROR\n");
                exit(1);
            }
        },

        {
            i++;
            switch (buffer[i])
            {
            case 1:
                processor.rax = pop(&processor.data);
                break;
            case 2:
                processor.rbx = pop(&processor.data);
                break;
            case 3:
                processor.rcx = pop(&processor.data);
                break;
            case 4:
                processor.rdx = pop(&processor.data);
                break;
            case 5:
                processor.rci = pop(&processor.data);
                break;
            case 6:
                processor.rdi = pop(&processor.data);
                break;
            case 7:
                processor.rsp = pop(&processor.data);
                break;
            case 8:
                processor.rbp = pop(&processor.data);
                break;
            }
            i++;
            break;
        })


CMD_DEF(add, 3,
        {
            char command = 3;
            if(fwrite(&command, sizeof(char), 1, output) <= 0)
            {
                printf("ERROR\n");
                exit(1);
            }
        },

        {
            push(&processor.data,
                 pop(&processor.data) + pop(&processor.data));

            i++;
            break;
        })

CMD_DEF(sub, 4,
        {
            char command = 4;

            if(fwrite(&command, sizeof(char), 1, output) <= 0)
            {
                printf("ERROR\n");
                exit(1);
            }
        },

        {
            push(&processor.data,
                 pop(&processor.data) - pop(&processor.data));

            i++;
            break;
        })

CMD_DEF(mul, 5,
        {
            char command = 5;

            if(fwrite(&command, sizeof(char), 1, output) <= 0)
            {
                printf("ERROR\n");
                exit(1);
            }
        },

        {
            push(&processor.data,
                 pop(&processor.data) * pop(&processor.data));

            i++;
            break;
        })

CMD_DEF(div, 6,
        {
            char command = 6;

            if(fwrite(&command, sizeof(char), 1, output) <= 0)
            {
                printf("ERROR\n");
                exit(1);
            }
        },

        {
            push(&processor.data,
                 pop(&processor.data) / pop(&processor.data));
            break;
        })
CMD_DEF(out, 7,
        {
            char command = 7;

            if(fwrite(&command, sizeof(char), 1, output) <= 0)
            {
                printf("ERROR\n");
                exit(1);
            }
        },

        {
            //printf("6 step\n");
            printf("%d\n", pop(&processor.data));
            i++;
            break;
        })

CMD_DEF(endf, 8,
        {
            char command = 8;

            if(fwrite(&command, sizeof(char), 1, output) <= 0)
            {
                printf("ERROR\n");
                exit(1);
            }
        },

        {
            count = 1;
            break;
        })

CMD_DEF(push, 1,
        {
            char command[5];
            for(int i = 0; i < 5; i++)
                command[i] = 0;
            command[0] = 1;
            *(int*)(command+1) = atoi(line+5);

            if(fwrite(command, sizeof(char), 5, output) <= 0)
            {
                printf("ERROR\n");
                exit(1);
            }
        },
        {
            i++;
            push(&processor.data, *(int*)(buffer + i));
            i+=4;

            break;
        })

CMD_DEF(pop, 2,
        {
            char command = 2;
            if(fwrite(&command, sizeof(char), 1, output) <= 0)
            {
                printf("ERROR\n");
                exit(1);
            }
        },
        {
            i++;
            break;
        })


CMD_DEF(jmp, 11,
        {
            char command[5];
            for(int i = 0; i < 5; i++)
                command[i] = 0;
            command[0] = 11;
            int i = 0;

            for(i = 0; i < QUANTITY_LABELS; i++)
            {

                if(strcmp(labels[i].name, line + 4) == 0)
                {
                    *(int*)(command + 1) = labels[i].pointer_to_jump;
                    break;
                }
            }

            if(i == QUANTITY_LABELS && quantity_lines == 0)
                *(int*)(command + 1) = -1;
            else if(i == QUANTITY_LABELS)
            {
                Print_in_log("ERROR in label", num_line);
                exit(1);
            }

            if(fwrite(command, sizeof(char), 5, output) <= 0)
            {
                printf("ERROR\n");
                exit(1);
            }
        },
        {
            i++;
            i = *(int*)(buffer+i);
        })

CMD_DEF(ja, 12,
        {
            char command[5];
            for(int i = 0; i < 5; i++)
                command[i] = 0;
            command[0] = 12;
            int i = 0;
            for(i = 0; i < QUANTITY_LABELS; i++)
                if(strcmp(labels[i].name, line + 3) == 0)
                {
                    *(int*)(command + 1) = labels[i].pointer_to_jump;
                    break;
                }

            if(i == QUANTITY_LABELS && quantity_lines == 0)
                *(int*)(command + 1) = -1;
            else if(i == QUANTITY_LABELS)
            {
                Print_in_log("ERROR in label", num_line);
                exit(1);
            }

            if(fwrite(command, sizeof(char), 5, output) <= 0)
            {
                printf("ERROR\n");
                exit(1);
            }
        },
        {
            processor.rsp = pop(&processor.data);
            processor.rbp = pop(&processor.data);
            i++;

            if(processor.rsp > processor.rbp)
                i = *(int*)(buffer+i);
            else   i += 4;

            push(&processor.data, processor.rbp);
            push(&processor.data, processor.rsp);
            break;
        })

CMD_DEF(jb, 13,
        {
            char command[5];
            for(int i = 0; i < 5; i++)
                command[i] = 0;
            command[0] = 13;
            int i = 0;
            for(i = 0; i < QUANTITY_LABELS; i++)
                if(strcmp(labels[i].name, line + 3) == 0)
                {
                    *(int*)(command + 1) = labels[i].pointer_to_jump;
                    break;
                }

            if(i == QUANTITY_LABELS && quantity_lines == 0)
                *(int*)(command + 1) = -1;
            else if(i == QUANTITY_LABELS)
            {
                Print_in_log("ERROR in label", num_line);
                exit(1);
            }

            if(fwrite(command, sizeof(char), 5, output) <= 0)
            {
                printf("ERROR\n");
                exit(1);
            }
        },
        {
            processor.rsp = pop(&processor.data);
            processor.rbp = pop(&processor.data);
            i++;

            if(processor.rsp < processor.rbp)
                i = *(int*)(buffer+i);
            else   i += 4;

            push(&processor.data, processor.rbp);
            push(&processor.data, processor.rsp);
            break;
        })

CMD_DEF(je, 14,
        {
            char command[5];
            for(int i = 0; i < 5; i++)
                command[i] = 0;
            command[0] = 14;
            int i = 0;
            for(i = 0; i < QUANTITY_LABELS; i++)
                if(strcmp(labels[i].name, line + 3) == 0)
                {
                    *(int*)(command + 1) = labels[i].pointer_to_jump;
                    break;
                }

            if(i == QUANTITY_LABELS && quantity_lines == 0)
                *(int*)(command + 1) = -1;
            else if(i == QUANTITY_LABELS)
            {
                Print_in_log("ERROR in label", num_line);
                exit(1);
            }

            if(fwrite(command, sizeof(char), 5, output) <= 0)
            {
                printf("ERROR\n");
                exit(1);
            }
        },
        {
            processor.rsp = pop(&processor.data);
            processor.rbp = pop(&processor.data);
            i++;

            if(processor.rsp == processor.rbp)
                i = *(int*)(buffer+i);
            else   i += 4;

            push(&processor.data, processor.rbp);
            push(&processor.data, processor.rsp);
            break;
        })

CMD_DEF(jae, 15,
        {
            char command[5];
            for(int i = 0; i < 5; i++)
                command[i] = 0;
            command[0] = 15;
            int i = 0;
            for(i = 0; i < QUANTITY_LABELS; i++)
                if(strcmp(labels[i].name, line + 4) == 0)
                {
                    *(int*)(command + 1) = labels[i].pointer_to_jump;
                    break;
                }

            if(i == QUANTITY_LABELS && quantity_lines == 0)
                *(int*)(command + 1) = -1;
            else if(i == QUANTITY_LABELS)
            {
                Print_in_log("ERROR in label", num_line);
                exit(1);
            }

            if(fwrite(command, sizeof(char), 5, output) <= 0)
            {
                printf("ERROR\n");
                exit(1);
            }

        },
        {
            processor.rsp = pop(&processor.data);
            processor.rbp = pop(&processor.data);
            i++;

            if(processor.rsp >= processor.rbp)
                i = *(int*)(buffer+i);
            else   i += 4;

            push(&processor.data, processor.rbp);
            push(&processor.data, processor.rsp);
            break;
        })

CMD_DEF(jbe, 16,
        {
            char command[5];
            for(int i = 0; i < 5; i++)
                command[i] = 0;
            command[0] = 16;
            int i = 0;
            for(i = 0; i < QUANTITY_LABELS; i++)
                if(strcmp(labels[i].name, line + 4) == 0)
                {
                    *(int*)(command + 1) = labels[i].pointer_to_jump;
                    break;
                }

            if(i == QUANTITY_LABELS && quantity_lines == 0)
                *(int*)(command + 1) = -1;
            else if(i == QUANTITY_LABELS)
            {
                Print_in_log("ERROR in label", num_line);
                exit(1);
            }

            if(fwrite(command, sizeof(char), 5, output) <= 0)
            {
                printf("ERROR\n");
                exit(1);
            }

        },
        {
            processor.rsp = pop(&processor.data);
            processor.rbp = pop(&processor.data);
            i++;

            if(processor.rsp <= processor.rbp)
                i = *(int*)(buffer+i);
            else   i += 4;

            push(&processor.data, processor.rbp);
            push(&processor.data, processor.rsp);
            break;
        })

CMD_DEF(call, 17,
        {
            char command[9];
            for(int i = 0; i < 9; i++)
                command[i] = 0;
            command[0] = 17;

            int i = 0;
            for(i = 0; i < QUANTITY_LABELS; i++)
                if(strcmp(labels[i].name, line + 5) == 0)
                {

                    *(int*)(command + 1) = labels[i].pointer_to_jump;
                    break;
                }

            if(i == QUANTITY_LABELS && quantity_lines == 0)
                *(int*)(command + 1) = -1;
            else if(i == QUANTITY_LABELS)
            {
                Print_in_log("ERROR in label", num_line);
                exit(1);
            }

            *(int*)(command + 5) = ftell(output) + 9;

            if(fwrite(command, sizeof(char), 9, output) <= 0)
            {
                printf("ERROR\n");
                exit(1);
            }
        },
        {
            i++;
            push(&processor.return_codes,
                 *(int*)(buffer + i + 4));
            i = *(int*)(buffer + i);
            break;
        })

CMD_DEF(ret, 18,
        {
            char command = 18;
            if(fwrite(&command, sizeof(char), 1, output) <= 0)
            {
                printf("ERROR\n");
                exit(1);
            }
        },
        {
            i = pop(&processor.return_codes);
        })
CMD_DEF(in, 19,
        {
            char command = 19;
            if(fwrite(&command, sizeof(char), 1, output) <= 0)
            {
                printf("ERROR\n");
                exit(1);
            }
        },
        {
            int scan_value = 0;
            prinf("Parameter:\n");
            while(scanf("%d\n", &scan_value) != 1)
                continue;

            push(&processor.data, scan_value);
            i++;
            break;
        })
CMD_DEF(mysqrt, 20,
        {
            char command = 20;
            if(fwrite(&command, sizeof(char), 1, output) <= 0)
            {
                printf("ERROR\n");
                exit(1);
            }
        },

        {
            push(&processor.data,
                 sqrt(pop(&processor.data)));

            i++;
            break;
        })

