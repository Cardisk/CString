#include <stdio.h>
#include "../headers/cstring.h";

int main() {
    String s = create("abcdefg");

    printf("%s", toString(s));
    return 0;
}
