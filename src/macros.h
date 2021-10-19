#ifndef MACROS_H
#define MACROS_H

#include <stdio.h>

#define RETURN_SUCCESS 0
#define RETURN_FAILURE 1
#define N_ASCII 128
#define CHAR_LIMIT 50
#define COLOR_BLACK "\033[30m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN "\033[36m"
#define COLOR_WHITE "\033[37m"
#define COLOR_RESET "\033[0m"
#define PRINT_ERROR(msg) fprintf(stderr, "%s%s%s", COLOR_RED, msg, COLOR_RESET);

#endif