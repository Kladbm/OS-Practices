#include <stdio.h>
#include <stdlib.h>

int main() {
    extern char **environ;

    for (char **env = environ; *env != NULL; env++) {
        printf("%s\n", *env);
    }

    return 0;
}