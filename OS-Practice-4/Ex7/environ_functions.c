#include <stdio.h>
#include <stdlib.h>

// Вивести інформацію про поточне оточення
void print_environment() {
    extern char **environ;
    char **env = environ;
    while (*env) {
        printf("%s\n", *env);
        env++;
    }
}

// Вивести інформацію про роботу з програмою
void print_help() {
    printf("Usage: environ [options]\n");
    printf("Options:\n");
    printf("  -h, --help           Display this help message\n");
    printf("  -i, --info <variable> Display the value of the specified variable\n");
    printf("  -s, --set <variable=value> Set the value of the specified variable\n");
    printf("  -d, --del <variable> Delete the specified variable\n");
    printf("  -a, --assign <variable> --value <value> Assign a new value to the specified variable\n");
    printf("  -c, --clear          Clear the environment\n");
}

// Вивести значення зазначеної змінної або повідомити, що її немає
void print_variable(const char *variable) {
    char *value = getenv(variable);
    if (value) {
        printf("%s=%s\n", variable, value);
    } else {
        printf("Variable %s is not set.\n", variable);
    }
}

// Встановити значення змінної в оточенні і вивести його
void set_variable(const char *variable, const char *value) {
    setenv(variable, value, 1);
    printf("%s=%s\n", variable, value);
}

// Видалити змінну з оточення
void delete_variable(const char *variable) {
    unsetenv(variable);
}

// Набути нового значення для змінної і вивести його
void assign_variable(const char *variable, const char *value) {
    if (value) {
        setenv(variable, value, 1);
        printf("%s=%s\n", variable, value);
    } else {
        printf("No value specified for assignment.\n");
    }
}

// Очистити оточення
void clear_environment() {
    clearenv();
}
