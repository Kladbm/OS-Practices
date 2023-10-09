#include <stdio.h>
#include <pwd.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

int main() {

    uid_t user_id = getuid();
    struct passwd *user_info_by_uid;

    user_info_by_uid = getpwuid(user_id);
    if (user_info_by_uid == NULL) {
        perror("getpwuid");
        exit(EXIT_FAILURE);
    }

    printf("Інформація про користувача за UID %d:\n", user_id);
    printf("Ім'я користувача: %s\n", user_info_by_uid->pw_name);
    printf("Повне ім'я користувача: %s\n", user_info_by_uid->pw_gecos);
    printf("Домашній каталог користувача: %s\n", user_info_by_uid->pw_dir);
    printf("\n");

    const char *username = "root";
    struct passwd *user_info_by_name;

    user_info_by_name = getpwnam(username);
    if (user_info_by_name == NULL) {
        perror("getpwnam");
        exit(EXIT_FAILURE);
    }

    printf("Інформація про користувача за ім'ям '%s':\n", username);
    printf("UID користувача: %d\n", user_info_by_name->pw_uid);
    printf("Повне ім'я користувача: %s\n", user_info_by_name->pw_gecos);
    printf("Домашній каталог користувача: %s\n", user_info_by_name->pw_dir);

    return 0;
}
