
#include "c-utils/c-utils.h"

void add_char_to_string(char* s, char c) {
    int len = strlen(s);
    s[len] = c;
    s[len+1] = '\0';
}

