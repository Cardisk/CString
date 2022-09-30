//
// Created by Matteo Cardinaletti on 29/09/22.
//

#ifndef CSTRING_CSTRING_H
#define CSTRING_CSTRING_H

#define TYPE char
#include "darray.h"

#include <string.h>

typedef struct String {
    DArray string;
    size_t size;
} String;

void set(String* string, TYPE chars[]) {
    // TODO: string->string.arr != NULL

    for (int i = 0; i < strlen(chars); ++i) {
        add_(&string->string, chars[i]);
    }

    string->size = string->string.size;
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
