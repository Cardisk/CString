//
// Created by Matteo Cardinaletti on 29/09/22.
//

#ifndef CSTRING_CSTRING_H
#define CSTRING_CSTRING_H

#define TYPE char
#include "darray.h"

#include <string.h>
#include <ctype.h>

typedef struct String {
    DArray string;
    size_t size;
} String;

void set(String* string, TYPE chars[]) {
    if (string->size > 0) {
        reset_(&string->string);
    }

    for (int i = 0; i < strlen(chars); ++i) {
        add_(&string->string, chars[i]);
    }

    string->size = string->string.size;
}

TYPE* capitalize(String string) {
    if (string.size > 0) {
        string.string.arr[0] = !isupper(string.string.arr[0]) ? string.string.arr[0] - 32 : string.string.arr[0];
        return string.string.arr;
    }

    return NULL;
}

TYPE* casefold(String string) {
    if (string.size > 0) {
        for (int i = 0; i < string.size; ++i) {
            string.string.arr[i] = isupper(string.string.arr[i]) ? string.string.arr[i] + 32 : string.string.arr[i];
        }

        return string.string.arr;
    }

    return NULL;
}

TYPE* toString(String string) {
    return string.string.arr;
}

String create(TYPE chars[]) {
    String s;
    init_(&s.string);
    set(&s, chars);
    return s;
}

#endif //CSTRING_CSTRING_H
