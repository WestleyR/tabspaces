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

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

#include "c-utils/c-utils.h"

FILE *check_file_fr;

// check_file will check a file from a path.
int check_file(const char*);

// remove_tab_line will take a string(line) and remove the tabs
// from it and replace the tab(s) with int(spaces_set), the return
// will be the first arg(char*).
int remove_tab_line(char* ret, char* line, int spaces_set);

// print_red_space will take a string(char*) and remove the last char
// (if its a space(' ')), and print that string, with a negative, red
// space after the orignal string.
void print_red_space(char*);

//
// End utils.h
//
