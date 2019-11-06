#include <stdio.h>

void red() {
    printf("\033[1;31m");
}

void green() {
    printf("\033[1;32m");
}

void yellow() {
    printf("\033[1;33m");
}

void blue() {
    printf("\033[1;34m");
}

void purple() {
    printf("\033[1;35m");
}

void purpleBG() {
    printf("\033[1;45m");
}

void gray() {
    printf("\033[30m");
}

void grayBG() {
    printf("\033[40m");
}

void whiteBG() {
    printf("\033[47m");
}

void white() {
    printf("\033[1;97m");
}


void resetColor() {
    printf("\033[0m");
}