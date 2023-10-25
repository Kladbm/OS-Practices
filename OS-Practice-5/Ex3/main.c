#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DEFAULT_BUFFER_SIZE 127

void printWelcomeMessage(char *username) {
    printf("Ласкаво просимо, %s!\n", username);
    printf("[%s]$: ", username);
}

void printHelp() {
    printf("Командний процесор на C\n");
    printf("Доступні команди:\n");
    printf("1. stop - завершити роботу програми\n");
    printf("Доступні опції:\n");
    printf("-h або --help - вивести цю довідку\n");
    printf("-b або --buffer <розмір> - визначити розмір буфера для команд (за замовчуванням %d)\n", DEFAULT_BUFFER_SIZE);
}

int main(int argc, char *argv[]) {
    char username[256];  // Рядок для зберігання імені користувача
    char inputBuffer[DEFAULT_BUFFER_SIZE];  // Буфер для команд користувача
    int buffer_size = DEFAULT_BUFFER_SIZE;
    int help_requested = 0;

    // Перевірка опцій командного рядка
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
       	    printHelp();
	    return 0;
        } else if ((strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--buffer") == 0) && i + 1 < argc) {
            buffer_size = atoi(argv[i + 1]);
	    return 0;
        }
    }

    // Отримання імені користувача
    printf("Будь ласка, введіть ваше ім'я: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';  // Видалення символу нового рядка

    // Вивід привітання
    printWelcomeMessage(username);

    while (1) {
        // Отримання команди користувача
        if (fgets(inputBuffer, buffer_size, stdin) == NULL) {
            perror("Помилка при зчитуванні команди");
            break;
        }

        // Видалення символу нового рядка з команди
        inputBuffer[strcspn(inputBuffer, "\n")] = '\0';

        // Виконання команди
        if (strcmp(inputBuffer, "stop") == 0) {
            break;  // Завершення програми
        } else {
            // Виконання команди через системний виклик
            int result = system(inputBuffer);
            if (result != 0) {
                printf("Помилка виконання команди\n");
            }
        }

        // Вивід повідомлення та очищення екрану
        printf("Завершення роботи...\n");
        sleep(3);
        system("clear");
        printf("[%s]$: ", username);
    }

    return 0;
}
