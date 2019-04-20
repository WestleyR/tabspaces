// Created by: WestleyR
// email: westleyr@nym.hush.com
// Date: Apr 1, 2019
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

#define SPACES_SET_FLAG "--spaces="
#define DEFAULT_SPACES 4

#include "main-tabspaces.h"
#include "tabs-spaces.h"
#include "spaces-tabs.h"

#include "arglib/arglib.h"
#include "logger/logger.h"

char* SCRIPT_NAME;

void help_menu() {
    printf("DESCRIPTION:\n");
    printf("  Convert tabs to spaces and spaces to tabs\n");
    printf("  in source code and text files.\n");
    printf("\n");
    printf("USAGE:\n");
    printf("  $ %s [option] <file>\n", SCRIPT_NAME);
    printf("\n");
    printf("OPTIONS:\n");
    printf("  -h, --help    : print help menu.\n");
    printf("  -v, --verbose : verbose.\n");
    printf("  -d, --diff    : only print the diff.\n");
    printf("  -t, --tab     : convert spaces (default 4) to tabs.\n");
    printf("  -V, --version : print version.\n");
    printf("\n");
    printf("VARS:\n");
    printf("  --spaces=int  : set how many spaces when converting\n");
    printf("                  tabs to spaces (default 4)\n");
    printf("\n");
    printf("EXAMPLES:\n");
    printf("  $ %s --spaces=2 -v file.go\n", SCRIPT_NAME);
    printf("  $ %s -vt file.go\n", SCRIPT_NAME);
    printf("\n");
    printf("This software is licensed under a Clear BSD License.\n");
    printf("Copyright (c) 2019 WestleyR, All rights reserved.\n");
    printf("Source code: https://github.com/WestleyR/tabspaces\n");
    return;
}

void version_print() {
    printf("%s\n", TABSPACES_VERSION);
    return;
}

int main(int argc, char **argv) {
    SCRIPT_NAME = argv[0];

    if (argc <= 1) {
        help_menu();
        return(1);
    }

    int SPACES_SET = DEFAULT_SPACES;
    char *path = NULL;
    int diff_view = 0;
    int verbose_print = 0;
    int sp_t = 0;

// loop throught all the arguments
    for (int i=1; i < argc; i++) {
        // get the output of `--out=`
        char* var;

        var = get_val(argv[i], SPACES_SET_FLAG);
        if (var != NULL) {
            SPACES_SET = atoi(var);
            print_verbosef("Setting spaces to: %d\n", SPACES_SET);
            printf("SPACES:  %d\n", SPACES_SET);
        }

        // check if arguments are: sort, or long args
        if (check_flag(argv[i], "", "--help") == 0) {
            help_menu();
            return(0);
        } else if (check_flag(argv[i], "", "--diff") == 0) {
            diff_view = 1;
        } else if (check_flag(argv[i], "", "--tabs") == 0) {
            sp_t = 1;
        } else if (check_flag(argv[i], "", "--verbose") == 0) {
            verbose_print = 1;
        } else if (check_flag(argv[i], "", "--version") == 0) {
            version_print();
            return(0);
        } else if ((strstr(argv[i], "--") == argv[i]) && (strstr(argv[i], SPACES_SET_FLAG) != argv[i])) {
            print_errorf("%s: option not found\n", argv[i]);
            return(2);
        } else if (strstr(argv[i], "-") != argv[i]) {
            path = argv[i];
        }

        // all the possible short args, will automatically print error
        // for example, $ ./your-code -lds --out=file
        if (check_small_args(argv[i], "hvdtV") != 0) {
            print_errorf("-%s: option not found\n", argv[i]);
            return(1);
        }

        if (find_args(argv[i], "h") == 0) {
            help_menu();
            return(0);
        }

        // if `v` is in the sort argument group
        if (find_args(argv[i], "v") == 0) {
            verbose_print = 1;
//            version_print();
//            return(0);
        }
        if (find_args(argv[i], "d") == 0) {
            diff_view = 1;
        }
        if (find_args(argv[i], "t") == 0) {
            sp_t = 1;
        }
        if (find_args(argv[i], "V") == 0) {
            version_print();
            return(0);
        }
    }

//    char* err;

    set_verbose(verbose_print);

    if (path == NULL) {
        print_errorf("No file specifyed\n");
        return(1);
    }
//    printf("PATH: %s\n", path);
    //int err;

    if (sp_t != 0) {
        int err = spaces_to_tabs(path, SPACES_SET, diff_view);
        if (err != 0) {
            print_errorf("Unable to convert spaces to tabs\n");
            return(4);
        }
        return(0);
    }

    int err = tabs_to_spaces(path, SPACES_SET, diff_view);
    if (err != 0) {
        print_errorf("Unable to convert tabs-to-spaces\n");
        return(4);
    }

    return(0);
}

//
// End main-tabspaces.c
//
