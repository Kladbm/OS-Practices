#ifndef ENVIRON_FUNCTIONS_H
#define ENVIRON_FUNCTIONS_H

void print_environment();
void print_help();
void print_variable(const char *variable);
void set_variable(const char *variable, const char *value);
void delete_variable(const char *variable);
void assign_variable(const char *variable, const char *value);
void clear_environment();

#endif
