#include <stdio.h>

int main() {
    int *ptr = NULL; // Null pointer
    *ptr = 42; // Dereferencing the null pointer will cause a segmentation fault
    return 0;
}

