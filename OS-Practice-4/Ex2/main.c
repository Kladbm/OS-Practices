#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Використання: %s <ім'я_змінної_оточення>\n", argv[0]);
        return 1;
    }

    const char *env_name = argv[1];
    char *env_value = getenv(env_name);

    if (env_value == NULL) {
        printf("Змінна оточення з ім'ям \"%s\" не існує.\n", env_name);
    } else if (env_value[0] == '\0') {
        printf("Змінна оточення з ім'ям \"%s\" існує, але її значення не встановлено.\n", env_name);
    } else {
        printf("Змінна оточення \"%s\" має значення: %s\n", env_name, env_value);
    }

    return 0;
}