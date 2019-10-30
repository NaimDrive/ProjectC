#include <stdio.h>

void red() {
    printf("\033[1;31m");
}

void green() {
    printf("\033[1;32m");
}

void white() {
    printf("\033[1;97m");
}

void resetColor() {
    printf("\033[0m");
}