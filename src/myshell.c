#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "ls_commend.h"
#include "cat_commend.h" // cat 명령어 헤더 파일 추가

#define MAX_LINE 80
#define MAX_ARGS 10

int main() {
    char input[MAX_LINE];
    char *token;
    char *argv[MAX_ARGS];

    while (1) {
        // Print the prompt
        printf("myshell> ");
        fflush(stdout);

        // Read the input from the user
        if (fgets(input, MAX_LINE, stdin) == NULL) {
            continue; // Handle EOF gracefully
        }

        // Remove the newline character from the input
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }

        // Tokenize the input
        token = strtok(input, " \n\t");
        int i = 0;
        while (token != NULL && i < MAX_ARGS - 1) {
            argv[i++] = token;
            token = strtok(NULL, " \n\t");
        }
        argv[i] = NULL;

        if (argv[0] == NULL) {
            continue; // Empty command
        }

        // Exit command
        else if (strcmp(argv[0], "exit") == 0) {
            printf("goodbye\n");
            exit(0);
        }

        // cd command
        else if (strcmp(argv[0], "cd") == 0) {
            if (argv[1] == NULL) {
                printf("cd: missing argument\n");
            } else {
                if (chdir(argv[1]) != 0) {
                    perror("cd");
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
            my_ls();
        }

        // cat command
        else if (strcmp(argv[0], "cat") == 0) {
            if (argv[1] == NULL) {
                fprintf(stderr, "cat: missing filename\n");
            } else {
                for (int j = 1; argv[j] != NULL; j++) {
                    my_cat(argv[j]); // cat 명령어 함수 호출
                }
            }
            printf("\n");
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
