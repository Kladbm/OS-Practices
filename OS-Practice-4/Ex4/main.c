#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        // Видалити всі змінні з оточення, якщо не вказано ім'я змінної
        if (clearenv() == 0) {
            printf("Оточення було очищено.\n");
        } else {
            perror("Помилка при очищенні оточення");
        }
    } else if (argc == 2) {
        // Видалити вказану змінну з оточення
        if (unsetenv(argv[1]) == 0) {
            printf("Змінна '%s' була видалена з оточення.\n", argv[1]);
        } else {
            perror("Помилка при видаленні змінної з оточення");
        }
    } else {
        printf("Спробуйте знову: %s [ім'я_змінної]\n", argv[0]);
    }

    // Вивести поточне оточення
    char **env = environ;
    while (*env) {
        printf("%s\n", *env);
        env++;
    }

    return 0;
}
