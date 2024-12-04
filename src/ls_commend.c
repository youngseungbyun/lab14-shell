#include <stdio.h>
#include <stdlib.h>
#include "ls_commend.h"
#include <dirent.h>
#include <sys/types.h>

void my_ls(void) {
    DIR *dir;
    struct dirent *entry;

    // Open the current directory
    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return;
    } 
    
    // Read and print each entry in the directory
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            printf("%s/\n", entry->d_name); // Append '/' to directories
        } else {
            printf("%s\n", entry->d_name); // Print files normally
        }
    }
    closedir(dir); // Close the directory
}
