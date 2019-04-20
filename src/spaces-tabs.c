// Created by: WestleyR
// email: westleyr@nym.hush.com
// Date: Apr 4, 2019
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

#include <stdio.h>
#include <string.h>

#include "main-tabspaces.h"
#include "spaces-tabs.h"

#include "logger/logger.h"
#include "c-utils/c-utils.h"

//#include "color.h"

FILE *check_file_fr;

/*
int check_file(const char* filepath) {
    FILE *fr = fopen(filepath, "r");

    if (fr == NULL) {
    	printf("Couldn't open file: %s!\n", filepath);
    	return(1);
    }

    struct stat info;
    if (lstat(filepath, &info) != 0) {
        printf("unable to open stat on: %s\n", filepath);
        return(1);
    }

    if (S_ISDIR(info.st_mode)) {
        printf("file is a directory: %s\n", filepath);
        return(1);
    }
    check_file_fr = fr;
    fclose(fr);

    return(0);
}
*/

int tabs_view_diff(const char* file_path, int spaces_set) {
    print_verbosef("Viewing the diff\n");

    print_errorf("diff not avalibal\n");

    return(2);

    FILE *fr = fopen(file_path, "r");
//    int tab_count = 0;

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

//    int c_line;
//    int lines_count = 0;
//    char line[128];
//
//    while (fgets(line, sizeof line, fr) != NULL) {
//        lines_count++;
//        for (c_line = 0; c_line <= strlen(line); c_line++) {
//            if (line[c_line] == '\t') {
//                printf("\nTAB on line: %s:%i\n", file_path, lines_count);
//                printf("%s:%i:%s--%s%s", file_path, lines_count, RED, line, COLOR_RESET);
//                printf("%s:%i:%s++%s%s", file_path, lines_count, GREEN, remove_tab_line(line, spaces_set), COLOR_RESET);
//                ret[0] = '\0';
//                tab_count++;
//            }
//        }
//    }
//    fclose(fr);
//
//    printf("\n");
//    print_verbosef("Total tabs in %s: %i\n", file_path, tab_count);
//
    return(0);
}

int convert_spaces_to_tabs(char* file_path, int spaces_set) {
    print_verbosef("Converting %i spaces to tabs\n", spaces_set);

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

    int c_line;
    int lines_count = 0;
    char line[128];
    FILE *fw;
    int start_spaces = 0;

    char new_line[256];
    new_line[0] = '\0';
    int tabs = 0;
    int did_start = 0;
    int done_line = 0;
    int total_tab_count = 0;

    fw = fopen(TMP_FILE, "a");

    while (fgets(line, sizeof line, fr) != NULL) {
        lines_count++;
        for (c_line = 0; c_line <= strlen(line); c_line++) {
            if ((c_line == 0) && (line[0] == ' ')) {
                did_start = 1;
            }
            if ((did_start != 0) && (line[c_line] == ' ')) {
                start_spaces++;
            }

            if (line[c_line] != ' ') {
                did_start = 0;
                start_spaces = 0;
                done_line = 1;
            }

            if (done_line != 0) {
                add_char_to_string(new_line, line[c_line]);
            }

            if (start_spaces >= spaces_set) {
                tabs = start_spaces / spaces_set;
                if (tabs > 0) {
                    for (int i = 0; i < tabs; i++) {
                        add_char_to_string(new_line, '\t');
                        total_tab_count++;
                    }
                }
                start_spaces = 0;
                tabs = 0;
            }
        }

//        fw = fopen(TMP_FILE, "a");
   	    fputs(new_line, fw);
//       	fclose(fw);

        new_line[0] = '\0';
        done_line = 0;

    }
    fclose(fr);
    fclose(fw);
//    remove(file_path);
    rename(file_path, "/tmp/tabspaces_build.bck");
    rename(TMP_FILE, file_path);

    print_verbosef("Total tabs added: %i\n", total_tab_count);
    
    printf("Done: %s\n", file_path);

    return(0);
}

// tabs_to_spaces ...
int spaces_to_tabs(char* file_path, int spaces_set, int diff_view) {
    if (diff_view != 0) {
        return(tabs_view_diff(file_path, spaces_set));
    }

    return(convert_spaces_to_tabs(file_path, spaces_set));

}

//
// End spaces-tabs.c
//
