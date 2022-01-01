#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int *p = malloc(10*sizeof(int)); 
    free(p); 
    p = NULL; 
    if(!p) {
        puts("Hell");
    }
}
