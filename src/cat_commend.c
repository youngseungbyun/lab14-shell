#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "cat_commend.h"


void my_cat(const char *filename) {
    // Check if the file exists and is readable
    if (access(filename, R_OK) != 0) {
        perror("access");
        return;
    }

    // Open the file
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("open");
        return;
    }

    // Read and print the file content
    char buffer[1024];
    ssize_t bytes_read;

    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        if (write(STDOUT_FILENO, buffer, bytes_read) < 0) {
            perror("write");
            close(fd);
            return;
        }
    }

    if (bytes_read < 0) {
        perror("read");
    }

    // Close the file
    close(fd);
}