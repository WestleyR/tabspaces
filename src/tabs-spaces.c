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

#include "main-tabspaces.h"
#include "tabs-spaces.h"

#include "logger/logger.h"

FILE *check_file_fr;

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

int view_diff(const char* file_path, int spaces_set) {
    print_verbosef("Viewing the diff\n");

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

    int c;
    int spaces = 0;
    int charRead = 0;
//    int ch = 0;
//    char line[200];


//    FILE *fw;
//    FILE *fr;
    int exited = 0;

//    if (check_file(file_path) != 0) {
//        print_errorf("theres a problome with: %s\n", file_path);
//        return(10);
//    }
//
//    if (check_file_fr == NULL) {
//        print_errorf("file is NULL\n");
//        return(12);
//    }

//    printf("FILE: %c\n", check_file_fr);

    int lines = 0;

    while ((c = fgetc(fr)) != EOF) {
//    while ((c = fgetc(check_file_fr)) != EOF) {

//        if (exited == 1) {
//            spaces++;
//            if (spaces == charRead) {
//                spaces = 0;
//                exited = 0;
//            }
//            continue;
//        }

        charRead++;

//        printf("cc %c\n", c);


        if (c == '\t') {
//            printf("INFO:C: %c\n", c);
//            printf("charRead: %i\n", charRead);
//            printf("spaces: %i\n", spaces);
            printf("TAB on line: %i\n", lines+1);
//            for (int i = spaces; i < spaces_set; i++) {
//                line[ch++] = ' ';
//            }
            spaces = 0;
        } else {
//            printf("NOT A TAB: %c\n", c);
            spaces++;
            if (spaces == 4) {
                spaces = 0;
            }
//            line[ch++] = c;
        }

        if (c == '\n') {
            lines++;
//            line[ch] = '\0';
//            spaces = 0;
//            ch = 0;
        }


/*        if (c == '\n') {
            line[ch] = '\0';
            spaces = 0;
            ch = 0;

            fclose(check_file_fr);

            printf("IINNFFOO:: %s\n", line);

            fw = fopen(TMP_FILE, "a");
            fputs(line, fw);
            fclose(fw);

            fr = fopen(file_path, "r");
            exited = 1;
        }*/
    }
//    fclose(fr);

    return(0);
}

int convert_tabs_to_spaces(char* file_path, int spaces_set) {
    int c;
    int spaces = 0;
    int charRead = 0;
    int ch = 0;
    char line[200];

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

//    if (check_file(file_path) != 0) {
//        print_errorf("there was a problome with: %s\n", file_path);
//        return(1);
//    }

    FILE *fw;
//    FILE *fr;
    int exited = 0;

    if (check_file_fr == NULL) {
        print_errorf("file is NULL\n");
        return(10);
    }

    while ((c = fgetc(fr)) != EOF) {
//    while ((c = fgetc(check_file_fr)) != EOF) {
        if (exited == 1) {
            spaces++;
            if (spaces == charRead) {
                spaces = 0;
                exited = 0;
            }
            continue;
        }
        charRead++;

        printf("cc %c\n", c);

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
            line[ch] = '\0';
            spaces = 0;
            ch = 0;

            fclose(check_file_fr);

            printf("IINNFFOO:: %s\n", line);

            fw = fopen(TMP_FILE, "a");
            fputs(line, fw);
            fclose(fw);

            fr = fopen(file_path, "r");
            exited = 1;
        }
    }

    fclose(fr);

    remove(file_path);
    rename(TMP_FILE, file_path);
    printf("Done: %s\n", file_path);

    return(0);
}

// tabs_to_spaces ...
int tabs_to_spaces(char* file_path, int spaces_set, int diff_view) {
    if (diff_view != 0) {
        return(view_diff(file_path, spaces_set));
    }

    return(convert_tabs_to_spaces(file_path, spaces_set));

}

//
// End tabs-spaces.c
//
