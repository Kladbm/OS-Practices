#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Функція для генерації випадкового числа у діапазоні [0, 1]
double generateRandomNumber() {
    return (double)rand() / RAND_MAX;
}

int main(int argc, char *argv[]) {
    // Задана кількість дочірніх програм
    int numChildProcesses = 0;
    // Значення системної змінної FILE_NAME
    char *fileName = NULL;

    int opt;
    while ((opt = getopt(argc, argv, "n:f:")) != -1) {
        switch (opt) {
            case 'n':
                numChildProcesses = atoi(optarg);
                break;
            case 'f':
                fileName = optarg;
                break;
            default:
                fprintf(stderr, "Usage: %s -n <number of child processes> -f <file name>\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (fileName == NULL) {
        // Якщо не задано FILE_NAME, використовуємо значення за промовчанням
        fileName = "default_filename";
    }

    for (int i = 1; i <= numChildProcesses; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            // Дочірній процес
            char childFileName[100];
            sprintf(childFileName, "%s_child%d.txt", fileName, i);

            FILE *file = fopen(childFileName, "w");
            if (file == NULL) {
                perror("Failed to open file");
                exit(EXIT_FAILURE);
            }

            for (int j = 0; j < i; j++) {
                double randomNumber = generateRandomNumber();
                fprintf(file, "%.6f\n", randomNumber);
            }

            fclose(file);
            exit(EXIT_SUCCESS);
        }
    }

    // Батьківський процес чекає завершення дочірніх процесів
    for (int i = 0; i < numChildProcesses; i++) {
        wait(NULL);
    }

    return 0;
}
