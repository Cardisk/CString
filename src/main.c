#include <stdio.h>
#include "../headers/cstring.h"

int main() {
    String s1 = create("abc");
    printf("%zu, %s\n", s1.size, chars(s1));

    set(&s1, "HelLO");
    printf("%zu, %s\n", s1.size, casefold(s1));

    set(&s1, "test");
    printf("%zu, %s\n", s1.size, capitalize(s1));

    String s2 = create("aaa");
    printf("Compare: %d\n", compare(s1, s2));

    set(&s2, "concat");
    printf("Concat: %s\n", concat(s1, s2));

    printf("isEmpty: %d\n", isEmpty(s1));

    printf("IndexOf: %d\n", indexOf(s1, 's'));
    return EXIT_SUCCESS;
}
