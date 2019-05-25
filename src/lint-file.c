// Created by: WestleyR
// email: westleyr@nym.hush.com
// Date: May 25, 2019
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

#include "lint-file.h"

int diff_lint(char *path) {
    FILE *fr = fopen(path, "r");

    if (fr == NULL) {
        printf("Couldn't open file: %s!\n", path);
        return(1);
    }

    struct stat info;
    if (lstat(path, &info) != 0) {
        printf("unable to open stat on: %s\n", path);
        return(1);
    }

    if (S_ISDIR(info.st_mode)) {
        printf("file is a directory: %s\n", path);
        return(1);
    }

    int c_line;
    int lines_count = 0;
    char line[256];
    int lint_errors = 0;

    while (fgets(line, sizeof line, fr) != NULL) {
        lines_count++;
        for (c_line = 0; c_line <= strlen(line); c_line++) {
            if (line[c_line] == '\n') {
                if (line[c_line-1] == ' ') {
                    printf("Extra space after content: %s: %i:\n", path, lines_count);
                    print_red_space(line);
                    lint_errors++;
                    break;
                }
            }
        }
    }
    fclose(fr);

    printf("\n");
    print_verbosef("Total tabs in %s: %i\n", path, lint_errors);

    return(0);
}

int linter_file(char* path) {
    printf("this function is not yet developt\n");

    return(2);
}

int lint_file(char* path, int diff_view) {
    if (diff_view != 0) {
        return(diff_lint(path));
    }
    return(linter_file(path));
}

//
// End lint-file.c
//
