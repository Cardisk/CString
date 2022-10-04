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
    // TODO: maybe is better to modify directly the string element instead of creating a new one.
    if (string.size > 0) {
        TYPE* chars = (TYPE*) malloc(string.size * sizeof(TYPE));
        strncpy(chars, string.string.arr, string.size);

        chars[0] = !isupper(chars[0]) ? chars[0] - 32 : chars[0];
        return chars;
    }

    return NULL;
}

TYPE* casefold(String string) {
    // TODO: maybe is better to modify directly the string element instead of creating a new one.
    if (string.size > 0) {
        TYPE* chars = (TYPE*) malloc(string.size * sizeof(TYPE));
        strncpy(chars, string.string.arr, string.size);

        for (int i = 0; i < string.size; ++i) {
            chars[i] = isupper(chars[i]) ? chars[i] + 32 : chars[i];
        }
        return chars;
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

/*
 * int < 0 : s1 < s2 alphabetically
 * int = 0 : s1 = s2 alphabetically
 * int > 0 : s1 > s2 alphabetically
 */
int compare(String s1, String s2) {
    for ( ; *s1.string.arr == *s2.string.arr; ++s1.string.arr, ++s2.string.arr) {
        if (*s1.string.arr == '\0') return 0;
    }

    return *s1.string.arr - *s2.string.arr;
}

/*
 * int < 0 : s1 < s2 alphabetically
 * int = 0 : s1 = s2 alphabetically
 * int > 0 : s1 > s2 alphabetically
 */
int compareIgnoreCase(String s1, String s2) {
    TYPE* c1 = casefold(s1);
    TYPE* c2 = casefold(s2);

    for ( ; *c1 == *c2; ++c1, ++c2) {
        if (*c1 == '\0') return 0;
    }

    return *c1 - *c2;
}

String create(TYPE chars[]) {
    String s;
    init_(&s.string);
    set(&s, chars);
    return s;
}

#endif //CSTRING_CSTRING_H

#pragma clang diagnostic pop