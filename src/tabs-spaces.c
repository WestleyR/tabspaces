// Created by: WestleyR
// email: westleyr@nym.hush.com
// Date: Apr 19, 2019
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

#include "main-tabspaces.h"
#include "tabs-spaces.h"
#include "utils.h"

#include "logger/logger.h"
#include "c-utils/c-utils.h"
#include "colorc/colorc.h"

int view_diff(const char* file_path, int spaces_set) {
    print_verbosef("Viewing the diff\n");

    FILE *fr = fopen(file_path, "r");
    int tab_count = 0;

    if (fr == NULL) {
        printf("Couldn't open file: %s!\n", file_path);
        return(1);
    }

    struct stat info;
    if (lstat(file_path, &info) != 0) {
        printf("unable to open stat on: %s\n", file_path);
        return(1);
    }

    if (S_ISDIR(info.st_mode)) {
        printf("file is a directory: %s\n", file_path);
        return(1);
    }

    int c_line;
    int lines_count = 0;
    char line[256];
    char ret_line[256];

    while (fgets(line, sizeof line, fr) != NULL) {
        lines_count++;
        for (c_line = 0; c_line <= strlen(line); c_line++) {
            if (line[c_line] == '\t') {
                remove_tab_line(ret_line, line, spaces_set);
                printf("\nTAB(s) on line: %s:%i\n", file_path, lines_count);
                printf("%s:%i:%s\n%s%s", file_path, lines_count, RED, line, COLOR_RESET);
                printf("%s\n%s%s", GREEN, ret_line, COLOR_RESET);
                tab_count++;
                ret_line[0] = '\0';
                break;
            }
        }
    }
    fclose(fr);

    printf("\n");
    print_verbosef("Total tabs in %s: %i\n", file_path, tab_count);

    return(0);
}

int convert_tabs_to_spaces(char* file_path, int spaces_set) {
    int c;
    int spaces = 0;
    int charRead = 0;
    int ch = 0;
    char line[200];
    int total_count = 0;

    FILE *fr = fopen(file_path, "r");

    print_verbosef("Converting tabs to %d spaces.\n", spaces_set);

    if (fr == NULL) {
        printf("Couldn't open file: %s!\n", file_path);
        return(1);
    }

    struct stat info;
    if (lstat(file_path, &info) != 0) {
        printf("unable to open stat on: %s\n", file_path);
        return(1);
    }

    if (S_ISDIR(info.st_mode)) {
        printf("file is a directory: %s\n", file_path);
        return(1);
    }

    FILE *fw;
    int exited = 0;
    int line_count = 0;

    while ((c = fgetc(fr)) != EOF) {
        if (exited == 1) {
            spaces++;
            if (spaces == charRead) {
                spaces = 0;
                exited = 0;
            }
            continue;
        }
        charRead++;

        if (c == '\t') {
            for (int i = spaces; i < spaces_set; i++) {
                line[ch++] = ' ';
            }
            spaces = 0;
        } else {
            spaces++;
            if (spaces == 4) {
                spaces = 0;
            }
            line[ch++] = c;
        }

        if (c == '\n') {
            total_count++;
            line[ch] = '\0';
            spaces = 0;
            ch = 0;

            fclose(fr);

            fw = fopen(TMP_FILE, "a");
            fputs(line, fw);
            fclose(fw);

            fr = fopen(file_path, "r");
            exited = 1;
            line_count++;
        }
    }

    fclose(fr);

    remove(file_path);
    rename(TMP_FILE, file_path);
    printf("Done: %s\n", file_path);
    print_verbosef("Total tabs replaced: %i\n", total_count);

    return(0);
}

// tabs_to_spaces
int tabs_to_spaces(char* file_path, int spaces_set, int diff_view) {
    if (diff_view != 0) {
        return(view_diff(file_path, spaces_set));
    }

    return(convert_tabs_to_spaces(file_path, spaces_set));

}

//
// End tabs-spaces.c
//
