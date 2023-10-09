#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>

int main() {
    char hostname[256];
    struct utsname sys_info;

    // Отримуємо ім'я мережі комп'ютера
    if (gethostname(hostname, sizeof(hostname)) == 0) {
        printf("Ім'я мережі комп'ютера: %s\n", hostname);
    } else {
        perror("Помилка отримання імені мережі");
        return 1;
    }

    // Отримуємо додаткову інформацію про комп'ютер за допомогою uname
    if (uname(&sys_info) == 0) {
        printf("Операційна система: %s %s\n", sys_info.sysname, sys_info.release);
        printf("Архітектура: %s\n", sys_info.machine);
        printf("Версія ядра: %s\n", sys_info.version);
        printf("Опис комп'ютера: %s\n", sys_info.nodename);
    } else {
        perror("Помилка отримання інформації про систему");
        return 1;
    }

    return 0;
}
