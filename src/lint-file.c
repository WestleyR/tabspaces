// Created by: WestleyR
// email: westleyr@nym.hush.com
// Date: Mat 18, 2019
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

int linter_file(char* path) {
    printf("this function is not yet developt\n");

    return(2);
}

int lint_file(char* path, int diff_view) {
    if (diff_view != 0) {
        printf("diff view is not avalibal\n");
        return(3);
    }
    return(linter_file(path));
}

//
// End lint-file.c
//
