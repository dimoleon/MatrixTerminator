#include <stdio.h>
#include <stdlib.h> 

struct int_list {
    size_t size; 
    int value[]; 
};

int push_back(struct int_list **fubar, int value) {
    size_t x = *fubar ? fubar[0]->size : 0, y = x + 1;

    if((x&y) == 0) {
        void *temp = realloc(*fubar, sizeof **fubar + (x + y)*sizeof fubar[0]->value[0]);
        if(!temp)
            return 1;
        *fubar = temp; 
    }
    fubar[0]->value[x] = value; 
    fubar[0]->size = y;
    return 0; 
}

int main() {
    struct int_list *array = NULL;
    for(int i = 0; i < 10; i++) 
        if(!push_back(&array, rand()%20)) 
            printf("%d\n", array->value[i]); 
    //size_t mem = sizeof *array + (array->size)*sizeof array->value[0]; 
    //printf("%li %li %li %li %li\n", sizeof *array, sizeof array, sizeof &array, mem, sizeof(int)); 
//    printf("%li %li\n", sizeof *array, sizeof array);
}

