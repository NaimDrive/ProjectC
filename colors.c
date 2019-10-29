#include <stdio.h>

void red() {
    printf("\033[1;31m ");
}

void green() {
    printf("\033[1;32m ");
}

void resetColor() {
    printf("\033[0m ");
}