#include <stdio.h> 
#include "matrixheader.h"

int main() {
    float p[] = {3, 1, 2, 4, 45, 13, 23}; 
    mergesort(p, 0, 6); 
    for(int i = 0; i < 7; i++) {
        printf("%4.0f", p[i]); 
    }
    putchar(10); 
}

