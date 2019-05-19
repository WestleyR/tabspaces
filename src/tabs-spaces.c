// Created by: WestleyR
// email: westleyr@nym.hush.com
// Date: May 18, 2019
// https://github.com/WestleyR/tabspaces
// version-1.0.1
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
    char line[256];
    int c_line;
    int lines_count = 0;
    FILE *fw;
    char new_line[256];
    new_line[0] = '\0';
    int total_tab_count = 0;

    FILE *fr = fopen(file_path, "r");


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

    fw = fopen(TMP_FILE, "a");
    if (fw == NULL) {
        printf("unable to open tmp file: %s\n", TMP_FILE);
        return(1);
    }

    print_verbosef("Converting tabs to %d spaces.\n", spaces_set);

    while (fgets(line, sizeof line, fr) != NULL) {
        lines_count++;
        for (c_line = 0; c_line <= strlen(line); c_line++) {

            if (line[c_line] == '\t') {
                for (int i = 0; i < spaces_set; i++) {
                    add_char_to_string(new_line, ' ');
                }
                total_tab_count++;
            } else {
                add_char_to_string(new_line, line[c_line]);
            }
        }
        fputs(new_line, fw);
        new_line[0] = '\0';
    }
    fclose(fr);
    fclose(fw);
//    remove(file_path);
    rename(file_path, "/tmp/tabspaces_build.bck");
    rename(TMP_FILE, file_path);

    print_verbosef("Total tabs added: %i\n", total_tab_count);
    printf("Done: %s\n", file_path);

    total_tab_count = 0;
    new_line[0] = '\0';
    c_line = 0;
    lines_count = 0;

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
