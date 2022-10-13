//
// Created by Matteo Cardinaletti on 29/09/22.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"

#ifndef CSTRING_CSTRING_H
#define CSTRING_CSTRING_H

#define TYPE char
#include "darray.h"

#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <regex.h>

/// String struct representing a string.
/// DArray string - DArray struct type that contains the string
/// size_t size - size_t type that contains the length of the string
typedef struct String {
    DArray string;
    size_t size;
} String;

/// Sets a new char[] to the struct pointer passed as an argument.
/// \param string String* struct variable
/// \param chars char[] containing the string
void set(String* string, TYPE chars[]) {
    if (string->size > 0) {
        reset_(&string->string);
    }

    for (int i = 0; i < strlen(chars); ++i) {
        add_(&string->string, chars[i]);
    }

    string->size = string->string.size;
}

/// Returns a copy of the string of the struct variable passed.
/// \param string String struct variable
/// \return A copy of the string
TYPE* to_chars(String string) {
    return strndup(string.string.arr, string.size);
}

/// Returns a copy of the capitalized string of the struct variable passed.
/// If the length of the string passed is 0, it returns NULL.
/// \param string String struct variable
/// \return A copy of the string
TYPE* capitalize(String string) {
    // TODO: maybe is better to modify directly the string element instead of creating a new one.
    if (string.size > 0) {
        TYPE* chars = to_chars(string);

        chars[0] = !isupper(chars[0]) ? chars[0] - 32 : chars[0];
        return chars;
    }

    return NULL;
}

/// Returns a copy of the lower cased string of the struct variable passed.
/// If the length of the string passed is 0, it returns NULL.
/// \param string String struct variable
/// \return A copy of the string
TYPE* lower(String string) {
    // TODO: maybe is better to modify directly the string element instead of creating a new one.
    if (string.size > 0) {
        TYPE* chars = to_chars(string);

        for (int i = 0; i < string.size; ++i) {
            chars[i] = isupper(chars[i]) ? chars[i] + 32 : chars[i];
        }
        return chars;
    }

    return NULL;
}

/// Returns a copy of the upper cased string of the struct variable passed.
/// If the length of the string passed is 0, it return NULL.
/// \param string String struct variable
/// \return A copy of the string
TYPE* upper(String string) {
    // TODO: maybe is better to modify directly the string element instead of creating a new one.
    if (string.size > 0) {
        TYPE* chars = to_chars(string);

        for (int i = 0; i < string.size; ++i) {
            chars[i] = !isupper(chars[i]) ? chars[i] - 32 : chars[i];
        }

        return chars;
    }

    return NULL;
}

/// Returns the character contained inside the string of the struct variable passed, at the given index.
/// If the passed index isn't inside the string bounds, it returns \0.
/// \param string String struct variable
/// \param index Index of the desired character
/// \return The character that corresponds to the given index
TYPE charAt(String string, int index) {
    if (index < - string.size + 1 || index > string.size - 1) return '\0';

    if (index < 0) return string.string.arr[string.size + index];
    return string.string.arr[index];
}

/// Compares the two given struct variables and returns an integer value that says if the first string is >,
/// = or < (alphabetically) than the second one.
/// \param s1 String struct variable
/// \param s2 String struct variable
/// \return An integer value (int > 0: s1 < s2 | int = 0: s1 = s2 | int > 0: s1 > s2)
int compare(String s1, String s2) {
    for ( ; *s1.string.arr == *s2.string.arr; ++s1.string.arr, ++s2.string.arr) {
        if (*s1.string.arr == '\0') return 0;
    }

    return *s1.string.arr - *s2.string.arr;
}

/// Compares the two given struct variables and returns an integer value that says if the first string is >,
///// = or < (alphabetically) than the second one. It ignores the string case.
/// \param s1 String struct variable
/// \param s2 String struct variable
/// \return An integer value (int > 0: s1 < s2 | int = 0: s1 = s2 | int > 0: s1 > s2)
int compareIgnoreCase(String s1, String s2) {
    TYPE* c1 = lower(s1);
    TYPE* c2 = lower(s2);

    for ( ; *c1 == *c2; ++c1, ++c2) {
        if (*c1 == '\0') return 0;
    }

    return *c1 - *c2;
}

/// Returns a new char[] containing the two given strings concatenated.
/// \param s1 String struct variable
/// \param s2 String struct variable
/// \return An array of characters
TYPE* concat(String s1, String s2) {
    // TODO: maybe is better to modify directly the string element instead of creating a new one.
    TYPE* chars = (TYPE*) malloc((s1.size + s2.size) * sizeof(TYPE));
    strncpy(chars, s1.string.arr, s1.size);

    for (int i = 0; i < s2.size; ++i) {
        chars[i + s1.size] = s2.string.arr[i];
    }

    return chars;
}

/// Checks if the given string is empty or not.
/// \param string String struct variable
/// \return A boolean
bool isEmpty(String string) {
    return string.size == 0;
}

/// Returns the index of the given character inside the string.
/// \param string String struct variable
/// \param ch A character
/// \return The index of the given character. If not found, returns -1
int indexOf(String string, TYPE ch) {
    if (string.size == 0) return -1;

    int i = 0;
    for ( ; i < string.size; ++i) {
        if (string.string.arr[i] == ch) break;
    }
    return (i >= string.size) ? -1 : i;
}

/// Returns the index of the last occurrence of the given character inside the string.
/// \param string String struct variable
/// \param ch A character
/// \return The last index of the given character. If not found, returns -1
int lastIndexOf(String string, TYPE ch) {
    if (string.size == 0) return -1;

    int last = 0, i = 0;
    for (; i < string.size; ++i) {
        if (string.string.arr[i] == ch) last = i;
    }

    return (last == 0) ? -1 : last;
}

/// Returns the index where the passed sequence starts.
/// \param src String struct variable
/// \param seq A char[]
/// \return The index of the substring. If not found, returns -1
int indexOfSubStr_(String src, TYPE seq[]) {
    int s_seq = strlen(seq);
    if ((src.size == s_seq && s_seq == 0) || s_seq == 0) return 0;
    if (src.size == 0) return -1;

    int i = 0, j = 0;
    for (; i < src.size; ++i) {
        if (src.string.arr[i] == seq[j]) j++;
        else j = 0;

        if (j == s_seq) break;
    }
    return (j == s_seq) ? (i - (s_seq - 1)) : -1;
}

/// Returns the index where the passed sequence starts.
/// \param src A char[]
/// \param seq A char[]
/// \return The index of the substring. If not found, returns -1
int indexOfSubStr__(TYPE src[], TYPE seq[]) {
    int s_seq = strlen(seq), s_src = strlen(src);
    if ((s_src == s_seq && s_seq == 0) || s_seq == 0) return 0;
    if (s_src == 0) return -1;

    int i = 0, j = 0;
    for (; i < s_src; ++i) {
        if (src[i] == seq[j]) j++;
        else j = 0;

        if (j == s_seq) break;
    }
    return (j == s_seq) ? (i - (s_seq - 1)) : -1;
}

/// Macro with _Generic that knows the correct function has to be called.
/// Use this instead of using directly the function.
#define indexOfSubStr(x, y) _Generic(x, String: indexOfSubStr_, TYPE*: indexOfSubStr__)(x, y)

/// Contains function made as a function. Returns a boolean.
#define contains(x, y) (indexOfSubStr(x, y) != -1) ? true : false

/// Returns a boolean. Checks if the string contained into the struct variable ends with the given char[] sequence.
/// \param string String struct variable
/// \param seq A char[]
/// \return A boolean
bool endsWith(String string, TYPE seq[]) {
    int index = indexOfSubStr(string, seq);
    if (index != -1) {
        if (index + strlen(seq) == string.size) return true;
    }
    return false;
}

/// Returns a boolean. Checks if the string contained into the struct variable starts with the given char[] sequence.
/// \param string String struct variable
/// \param seq A char[]
/// \return A boolean
bool startsWith(String string, TYPE seq[]) {
    return indexOfSubStr(string, seq) == 0;
}

/// Returns a boolean. Checks if the first string is equals to the second one.
/// \param s1 String struct variable
/// \param s2 String struct variable
/// \return A boolean
bool equals(String s1, String s2) {
    return (s1.size == s2.size) && (indexOfSubStr(s1, s2.string.arr) == 0);
}

/// Returns a boolean. Checks if the first string is equals to the second one. It ignores the string case.
/// \param s1 String struct variable
/// \param s2 String struct variable
/// \return A boolean
bool equalsIgnoreCase(String s1, String s2) {
    TYPE* c1 = lower(s1);
    TYPE* c2 = lower(s2);

    return (s1.size == s2.size) && (indexOfSubStr(c1, c2) == 0);
}

/// Returns a boolean. Checks if the string of the given struct variable matches with the passed regex.
/// \param s String struct variable
/// \param reg A char[] containing a regex
/// \return A boolean
bool matches(String s, TYPE reg[]) {
    regex_t regex;
    int result;

    result = regcomp(&regex, reg, REG_EXTENDED | REG_ICASE);
    if (result) {
        printf("Unsuccessful regex compilation.");
        exit(EXIT_FAILURE);
    }
    result = regexec(&regex, s.string.arr, 0, NULL, 0);
    regfree(&regex);

    return result == 0;
}

/// Returns a copy of the string with all old_ characters replaced with the new_ ones.
/// \param string String struct variable
/// \param old_ Old char
/// \param new_ New char
/// \return A copy of the string
TYPE* replace_(String string, TYPE old_, TYPE new_) {
    TYPE* chars = to_chars(string);

    for (int i = 0; i < string.size; ++i) {
        if (chars[i] == old_) chars[i] = new_;
    }

    return chars;
}

/// Returns a copy of the string with all old_ substrings replaced with the new_ ones.
/// \param string String struct variable
/// \param old_ Old char[]
/// \param new_ New char[]
/// \return A copy of the string
TYPE* replace__(String string, TYPE old_[], TYPE new_[]) {
    int s_old = strlen(old_);
    if (s_old != strlen(new_)) return NULL;

    TYPE* chars = to_chars(string);

    int index;
    do {
        index = indexOfSubStr(chars, old_);
        for (int i = index, j = 0; i < index + s_old; ++i, ++j) {
            chars[i] = new_[j];
        }
    } while (index != -1);

    return chars;
}

/// Macro with _Generic that knows the correct function that has to be called.
/// Use this instead of using directly the function.
#define replace(x, y, z) _Generic((y, z), int: replace_, TYPE*: replace__)(x, y, z)

/// Returns a copy of the string without the leading and trailing spaces.
/// \param string String struct variable
/// \return A copy of the string
TYPE* trim(String string) {
    size_t size = string.size;

    while(isspace(string.string.arr[size - 1])) --size;
    while(*string.string.arr && isspace(*string.string.arr)) ++string.string.arr, --size;

    return strndup(string.string.arr, size);
}

/// Returns a substring of the given string that starts from the given index.
/// \param string String struct variable
/// \param beginIndex Start index of substring
/// \return A copy of the string that represent the substring
TYPE* substring_begin(String string, int beginIndex) {
    if (beginIndex < 0 || beginIndex >= string.size) return NULL;

    for (int i = 0; i < beginIndex; ++i) ++string.string.arr;

    return strndup(string.string.arr, (string.size - beginIndex));
}

/// Returns a substring of the given string that is between the given indexes.
/// \param string String struct variable
/// \param beginIndex Start index of substring
/// \param endIndex End index of substring
/// \return A copy of the string that represent the substring
TYPE* substring_begin_end(String string, int beginIndex, int endIndex) {
    if (beginIndex < 0 || beginIndex >= string.size ||
        endIndex < 0 || endIndex >= string.size || beginIndex == endIndex) return NULL;

    for (int i = 0; i < beginIndex; ++i) ++string.string.arr;

    return strndup(string.string.arr, (endIndex - beginIndex));
}

/// Returns a pointer array that contains all the substrings.
/// \param string String struct variable
/// \param separator A char[] that represent the separator
/// \param members Integer pointer where to store how many substrings there are
/// \return A matrix made of pointers
TYPE** split(String string, TYPE* separator, int* members) {
    if (!contains(string, separator) || strlen(separator) == 0 || string.size == 0) return NULL;

    int offset = 0;
    *members = 0;
    size_t length = strlen(separator);

    int index;
    while (true) {
        index = indexOfSubStr(string.string.arr + offset, separator);

        if (index == -1) {
            (*members)++;
            break;
        }

        if (index > string.size - offset) break;
        if (index > 0 || (index - offset) >= 1) (*members)++;

        offset += (index + length);

        if (offset >= string.size) break;
    }

    if ((*members) > 0) {
        TYPE** slices = malloc((*members) * sizeof(TYPE*));
        offset = 0;
        int i = 0;
        bool valid_substr = false;
        while (true) {
            index = indexOfSubStr(string.string.arr + offset, separator);

            int len = string.size - offset;
            if (index > len) break;

            if (index == -1 && offset <= string.size) {
                slices[i] = strndup(string.string.arr + offset, (string.size - offset));
                break;
            }

            if (index > 0 || (index - offset) >= 1) {
                slices[i] = strndup(string.string.arr + offset, (index > 0) ? index : (string.size - offset));
                valid_substr = true;
            }

            offset += (index + length);

            if (offset >= string.size) break;

            if (valid_substr && i < (*members)) i++;
            valid_substr = false;
        }

        return slices;
    }

    return NULL;
}

/// Creates a string struct variable.
/// \param chars A char[] containing the string
/// \return A String struct variable
String create(TYPE chars[]) {
    String s;
    init_(&s.string);
    set(&s, chars);
    return s;
}

/// Destroys a string struct variable.
/// \param string String* struct variable
void destroy(String* string) {
    string->size = 0;
    free_(&string->string);
}

#endif //CSTRING_CSTRING_H

#pragma clang diagnostic pop