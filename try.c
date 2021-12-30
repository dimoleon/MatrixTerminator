#include <stdio.h>
#include <string.h>


int main() {
    char a[11] = "yes"; 
    char b[10]; 
    scanf("%s", b); 
    printf("%d", strcmp(a, b)); 
}
