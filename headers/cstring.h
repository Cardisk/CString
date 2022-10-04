#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
//
// Created by Matteo Cardinaletti on 29/09/22.
//

#ifndef CSTRING_CSTRING_H
#define CSTRING_CSTRING_H

#define TYPE char
#include "darray.h"

#include <string.h>
#include <ctype.h>

#define MIN(a, b) ((a) > (b)) ? (b) : (a)

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
    // TODO: sto modificando la stringa stessa, guarda strncpy
    if (string.size > 0) {
        string.string.arr[0] = !isupper(string.string.arr[0]) ? string.string.arr[0] - 32 : string.string.arr[0];
        return string.string.arr;
    }

    return NULL;
}

TYPE* casefold(String string) {
    // TODO: sto modificando la stringa stessa, guarda strncpy
    if (string.size > 0) {
        for (int i = 0; i < string.size; ++i) {
            string.string.arr[i] = isupper(string.string.arr[i]) ? string.string.arr[i] + 32 : string.string.arr[i];
        }
        return string.string.arr;
    }

    return NULL;
}

TYPE* chars(String string) {
    return string.string.arr;
}

TYPE charAt(String string, int index) {
    if (index < - string.size + 1 || index > string.size - 1) return '\0';

    if (index < 0) return string.string.arr[string.size + index];
    return string.string.arr[index];
}

int compare(String s1, String s2) {
    for ( ; *s1.string.arr == *s2.string.arr; ++s1.string.arr, ++s2.string.arr) {
        if (*s1.string.arr == '\0') return 0;
    }

    return *s1.string.arr - *s2.string.arr;
}

String create(TYPE chars[]) {
    String s;
    init_(&s.string);
    set(&s, chars);
    return s;
}

#endif //CSTRING_CSTRING_H

#pragma clang diagnostic pop