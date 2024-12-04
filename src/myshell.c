#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "ls_commend.h"

#define MAX_LINE 80
#define MAX_ARGS 10

int main() {
    char input[MAX_LINE];
    char *token;
    char *argv[MAX_ARGS];

    while (1) {
        // Print the prompt
        printf("myshell> ");

        // Read the input from the user
        if (fgets(input, MAX_LINE, stdin) == NULL) {
            continue; // Handle EOF gracefully
        }

        // Tokenize the input
        token = strtok(input, " \n\t");
        int i = 0;
        while (token != NULL) {
            argv[i++] = token;
            token = strtok(NULL, " \n\t");
        }
        argv[i] = NULL;

        if (argv[0] == NULL) {
            continue; // Empty command
        }

        else if (strcmp(argv[0], "exit") == 0) {
            printf("goodbye\n");
            exit(0);
        } 

        // cd command
        else if (strcmp(argv[0], "cd") == 0) {
            if (argv[1] == NULL) {
                printf("cd: missing argument\n");
            } else {
                // Attempt to change the directory
                if (chdir(argv[1]) != 0) {
                    perror("cd"); // 출력: 디렉토리 변경 실패 시 에러 메시지
                }
            }
        }
        // pwd command
        else if (strcmp(argv[0], "pwd") == 0) {
            if (getcwd(input, MAX_LINE) != NULL) {
                printf("%s\n", input);
            } else {
                perror("pwd");
            }
        } 
        
        // ls command
        else if (strcmp(argv[0], "ls") == 0) {
            printf("execute ls\n");
            my_ls();
        } 
        
        // Unrecognized command
        else {
            if (access(argv[0], F_OK) == 0) {
                printf("execute %s\n", argv[0]);
            } else {
                printf("command not found\n");
            }
        }
    }

    return 0;
}
