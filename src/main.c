#include <stdio.h>
#include "../headers/cstring.h";

int main() {
    String s = create("abc");
    printf("%d, %s\n", s.size, toString(s));

    set(&s, "hello");
    printf("%d, %s", s.size, toString(s));

    return EXIT_SUCCESS;
}
