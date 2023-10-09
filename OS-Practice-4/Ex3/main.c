#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <variable_name> <value>\n", argv[0]);
        return 1;
    }

    const char *variable_name = argv[1];
    const char *value = argv[2];

    // Встановлюємо змінну оточення з вказаним значенням.
    if (setenv(variable_name, value, 1) != 0) {
        perror("setenv");
        return 1;
    }

    // Отримуємо значення змінної оточення та виводимо її разом із значенням.
    char *env_value = getenv(variable_name);
    if (env_value != NULL) {
        printf("Змінна оточення %s: %s\n", variable_name, env_value);
    } else {
        printf("Змінна оточення %s не знайдена\n", variable_name);
    }

    return 0;
}
