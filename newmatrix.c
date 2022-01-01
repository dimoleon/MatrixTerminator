/* 
MATRIX TERMINATOR
*/

#include "matrix.h"

//ask with this order: id, (dimensions), (values); 
int main() { 
    struct matrix *new = NULL;
    char name[mxid]; 
    int r = 0, c = 0;
    struct matrix_list *v = NULL; 
    
    for(int k = 0; k < 5; k++) {
        query_id(name, v); 
        fflush(stdin); 
        query_dim(&r, &c); 
        init_matrix(&new, r, c, name);
        for(int i = 0; i < new->rows; i++) {
            for(int j = 0; j < new->cols; j++) 
                new->pin[i*(new->cols) + j] = rand()%20; 
        }
        insert(new, &v); 
        new = NULL; 
        r = c = 0; 
    }
    for(int i = 0; i < v->size; i++) 
        show_matrix(v->e[i]); 
    delete_matrix(&v->e[2]); 
    for(int i = 0; i < v->size; i++) 
        if(v->e[i])
            show_matrix(v->e[i]); 
    for(int i = 0; i < v->size; i++)
        if(v->e[i])
            delete_matrix(&v->e[i]); 
    free(v); 
    puts("YEAH BABY"); 
/*
    for(int i = 0; i < new->rows; i++) {
        for(int j = 0; j < new->cols; j++) 
            new->pin[i*(new->cols) + j] = rand()%20; 
    }
*/
    return 0; 
}

