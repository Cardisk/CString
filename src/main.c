#include <stdio.h>
#include "../headers/cstring.h"

int main() {
    String s1 = create("abc");
    printf("CHARS: %s\n", chars(s1));

    set(&s1, "HelLO");
    printf("CASEFOLD: %s -> %s\n", chars(s1), casefold(s1));

    set(&s1, "test");
    printf("CAPITALIZE: %s -> %s\n", chars(s1), capitalize(s1));

    printf("UPPER: %s -> %s\n", chars(s1), upper(s1));

    String s2 = create("aaa");
    printf("COMPARE: %s, %s -> %d\n", chars(s1), chars(s2), compare(s1, s2));

    set(&s2, "concat");
    printf("CONCAT: %s, %s -> %s\n", chars(s1), chars(s2), concat(s1, s2));

    printf("ISEMPTY: %s -> %d\n", chars(s1), isEmpty(s1));

    printf("INDEXOF: %s, %c -> %d\n", chars(s1), 's', indexOf(s1, 's'));

    printf("INDEXOFSUBSTR: %s, %s -> %d\n", chars(s1), "es", indexOfSubStr(s1, "es"));

    printf("CONTAINS: %s, %s -> %d\n", chars(s1), "t", contains(s1, "t"));

    printf("ENDSWITH: %s, %s -> %d\n", chars(s1), "st", endsWith(s1, "st"));

    printf("STARTSWITH: %s, %s -> %d\n", chars(s1), "t", startsWith(s1, "t"));

    printf("EQUALS: %s, %s -> %d\n", chars(s1), chars(s2), equals(s1, s2));

    printf("MATCHES: %s, %s -> %d\n", chars(s1), "[0-9]", matches(s1, "[0-9]"));

    printf("REPLACE: %s, %c, %c -> %s\n", chars(s1), 's', 'S', replace(s1, 's', 'S'));

    set(&s1, "  test  ");
    printf("TRIM: \'%s\' -> \'%s\'\n", chars(s1), trim(s1));

    destroy(&s1);
    destroy(&s2);
    return EXIT_SUCCESS;
}
