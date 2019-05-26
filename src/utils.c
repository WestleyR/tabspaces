// Created by: WestleyR
// email: westleyr@nym.hush.com
// Date: Apr 25, 2019
// https://github.com/WestleyR/tabspaces
// version-1.0.0
//
// The Clear BSD License
//
// Copyright (c) 2019 WestleyR
// All rights reserved.
//
// This software is licensed under a Clear BSD License.
//

#include "utils.h"

int get_file(FILE** file, const char* path) {
    *file = fopen(path, "r");

    if (file == NULL) {
        printf("Couldn't open file: %s\n", path);
        perror(path);
        return(errno);
    }

    struct stat info;
    if (lstat(path, &info) != 0) {
        printf("unable to open stat on: %s\n", path);
        perror(path);
        return(errno);
    }

    if (S_ISDIR(info.st_mode)) {
        printf("%s: File is a directory\n", path);
        return(2);
    }
//    fclose(*file);

    return(0);
}

int remove_tab_line(char* ret, char* line, int spaces_set) {
    int count;

    for (count = 0; count <= strlen(line); count++) {
        if (line[count] == '\t') {
            strcat(ret, "    ");
        } else {
            add_char_to_string(ret, line[count]);
        }
    }

    return(0);
}

void print_red_space(char* line) {
    char *newl = line;
    newl[strcspn(newl, "\n")] = 0;
    if (newl[strlen(newl)-1] == ' ') {
        newl[strlen(newl)-1] = 0;
    }
    printf("%s%s%s%c%s\n\n", newl, RED, NEGATIVE, ' ', COLOR_RESET);

    return;
}

//
// End utils.c
//
