#include <stdio.h>
#include "../headers/cstring.h"

int main() {
    String s1 = create("abc");
    String s2 = create("aaa");

    char* output_1;
    char* output_2;
    char* output_3;

    // TO_CHARS
    output_1 = to_chars(s1);
    printf("CHARS: %s\n", output_1);
    free(output_1);

    // CASEFOLD
    set(&s1, "HelLO");
    output_1 = to_chars(s1);
    output_2 = casefold(s1);
    printf("CASEFOLD: %s -> %s\n", output_1, output_2);
    free(output_1);
    free(output_2);

    // CAPITALIZE
    set(&s1, "test");
    output_1 = to_chars(s1);
    output_2 = capitalize(s1);
    printf("CAPITALIZE: %s -> %s\n", output_1, output_2);
    free(output_2);

    // UPPER
    output_2 = upper(s1);
    printf("UPPER: %s -> %s\n", output_1, output_2);
    free(output_2);

    // COMPARE
    output_2 = to_chars(s2);
    printf("COMPARE: %s, %s -> %d\n", output_1, output_2, compare(s1, s2));
    free(output_2);

    // CONCAT
    set(&s2, "concat");
    output_2 = to_chars(s2);
    output_3 = concat(s1, s2);
    printf("CONCAT: %s, %s -> %s\n", output_1, output_2, output_3);
    free(output_2);
    free(output_3);

    // IS_EMPTY
    printf("ISEMPTY: %s -> %d\n", output_1, isEmpty(s1));

    // INDEX_OF
    printf("INDEXOF: %s, %c -> %d\n", output_1, 's', indexOf(s1, 's'));

    // INDEX_OF_SUB_STR
    printf("INDEXOFSUBSTR: %s, %s -> %d\n", output_1, "es", indexOfSubStr(s1, "es"));

    // CONTAINS
    printf("CONTAINS: %s, %s -> %d\n", output_1, "t", contains(s1, "t"));

    // ENDS_WITH
    printf("ENDSWITH: %s, %s -> %d\n", output_1, "st", endsWith(s1, "st"));

    // STARTS_WITH
    printf("STARTSWITH: %s, %s -> %d\n", output_1, "t", startsWith(s1, "t"));

    // EQUALS
    output_2 = to_chars(s2);
    printf("EQUALS: %s, %s -> %d\n", output_1, output_2, equals(s1, s2));
    free(output_2);

    // MATCHES
    printf("MATCHES: %s, %s -> %d\n", output_1, "[0-9]", matches(s1, "[0-9]"));

    // REPLACE
    output_2 = replace(s1, 's', 'S');
    printf("REPLACE: %s, %c, %c -> %s\n", output_1, 's', 'S', output_2);
    free(output_1);
    free(output_2);

    // TRIM
    set(&s1, "  test  ");
    output_1 = to_chars(s1);
    output_2 = trim(s1);
    printf("TRIM: \'%s\' -> \'%s\'\n", output_1, output_2);
    free(output_1);
    free(output_2);

    // SUBSTRING_BEGIN (SUBSTRING_BEGIN_END)
    set(&s1, "test");
    output_1 = to_chars(s1);
    output_2 = substring_begin(s1, 1);
    printf("SUBSTRING: %s -> %s\n", output_1, output_2);
    free(output_1);
    free(output_2);

    // SPLIT
    set(&s1, "test test");
    output_1 = to_chars(s1);
    int members = 0;
    printf("SPLIT: \'%c\', '%s' -> ", ' ', output_1);
    free(output_1);
    char** slices = split(s1, " ", &members);
    for (int i = 0; i < members; ++i) {
        printf("'%s' ", slices[i]);
        if (i < members - 1) printf("- ");
        free(slices[i]);
    }
    printf("\n");
    free(slices);

    destroy(&s1);
    destroy(&s2);
    return EXIT_SUCCESS;
}
