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

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
//#include <unistd.h>

#include "c-utils/c-utils.h"

FILE *check_file_fr;

//int check_file(const char* filepath);
int check_file(const char*);
int remove_tab_line(char* ret, char* line, int spaces_set);

//
// End utils.h
//
