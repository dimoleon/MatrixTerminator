#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#define mxid 10
const int mxdim = 20;

//fundamental definition of the matrix structure 
struct matrix {
    char id[mxid];  //name
    int rows;       //# of rows 
    int cols;       //# of columns 
    int pin[];      //array of values 2D, disguised as 1D (follows the pin[i*cols + j] format)
};

//dynamic array of matrices structure (wanna be)
struct matrix_list {
    size_t size; 
    struct matrix *e[]; 
};

//matrix initialization, given rows and columns and id; allocate memory 
int init_matrix(struct matrix **ptr, int r, int c, char name[mxid]) {
    void *temp = malloc(sizeof **ptr + r*c*sizeof(int));
    if(!temp)
        return 1;
    *ptr = temp; 
    strcpy(ptr[0]->id, name); 
    ptr[0]->rows = r;
    ptr[0]->cols = c;
    return 0;
}

//delete matrix (needs check)
void delete_matrix(struct matrix **ptr) {
    free(*ptr);
    *ptr = NULL; 
}

//insert matrix in memory array (super cool), double size of memory if it doesn't fit. 
int insert(struct matrix *m, struct matrix_list **mem) {
    size_t x = *mem ? mem[0]->size : 0;
    size_t y = x + 1; 
    if((x & y) == 0) {
        void *temp = realloc(*mem, sizeof **mem + (x + y)*sizeof mem[0]->e[0]);
        if(!temp)
            return 1;
        *mem = temp; 
    }
    mem[0]->e[x] = m;
    mem[0]->size = y; 
    return 0; 
} 


//find index of matrix, given name; else return -1; 
int search_id(char s[mxid], const struct matrix_list *v) {
    for(int i = 0; i < v->size; i++) {
        if(v->e[i])
            if(strcmp(s, (v->e[i])->id) == 0)
                return i; 
    }
    return -1;
}

//ask matrix id, user input; needs character limit without termination probably fgets?; 
//need to check if in database; (seperate function above, search_id) DONE!
void query_id(char s[mxid], const struct matrix_list *v) {
    printf("Give matrix name (max 10 characters, no spaces): "); 
    scanf("%s", s);
    fflush(stdin);
    if(v) {
        while(search_id(s, v) != -1) {
            puts("Duplicate names not allowed! Try again."); 
            printf("Give matrix name (max 10 characters, no spaces): "); 
            scanf("%s", s); 
            fflush(stdin); 
        }
    }
}

//ask dimensions, user input; problematic if user inputs characters!
void query_dim(int *pr, int *pc) {
    do {
        fflush(stdin); 
        printf("Give number of rows: ");
        scanf("%d", pr); 
        if(*pr > mxdim || *pr < 1)
            printf("Dimensions must be positive and less than %d\n", mxdim+1); 
    } while(*pr > mxdim || *pr < 1);

    do {
        fflush(stdin); 
        printf("Give number of cols: ");
        scanf("%d", pc); 
        if(*pc > mxdim || *pc < 1)
            printf("Dimensions must be positive and less than %d\n", mxdim+1); 
    } while(*pc > mxdim || *pc < 1);
}

//ask values, user input
void query_values(struct matrix *empty) {
    for(int i = 0; i < empty->rows; i++) {
        for(int j = 0; j < empty->cols; j++) {
            printf("Give value of %s[%d][%d]: ", empty->id, i+1, j+1); 
            scanf("%d", &empty->pin[i*empty->cols + j]); 
        }
    }
}


//show fundamental values of given matrix 
void show_matrix(struct matrix *mat) {
    puts(mat->id); 
    printf("%d %d\n", mat->rows, mat->cols);
    for(int i = 0; i < mat->rows; i++) {
        for(int j = 0; j < mat->cols; j++) {
            printf("%d\t", mat->pin[i*(mat->cols) + j]);
        }
        putchar('\n');
    }
}

//transpose matrix
void transpose(struct matrix *transp, const struct matrix *orig) {
    for(int i = 0; i < orig->rows; i++)
        for(int j = 0; j < orig->cols; j++)
            (transp->pin)[j*orig->rows + i] = orig->pin[i*orig->cols  + j];
}

//matrix addition
void sum(struct matrix *sum, const struct matrix *A, const struct matrix *B) {
    for(int i = 0; i < A->rows; i++) 
        for(int j = 0; j < A->cols; j++)
            (sum->pin)[i*A->cols + j] = A->pin[i*A->cols + j] + B->pin[i*B->cols + j]; 
}

//matrix substraction
void difference(struct matrix *diff, const struct matrix *A, const struct matrix *B) {
    for(int i = 0; i < A->rows; i++) 
        for(int j = 0; j < A->cols; j++)
            (diff->pin)[i*A->cols + j] = A->pin[i*A->cols + j] - B->pin[i*B->cols + j]; 
}

//matrix multiplication
void product(struct matrix *prod, const struct matrix *left, const struct matrix *right) {
    assert(left->cols == right->rows); 
    //int common = left->cols; 
    for(int i = 0; i < prod->rows; i++) {
        for(int j = 0; j < prod->cols; j++) {
            int summ = 0; 
            for(int p = 0; p < left->cols; p++) 
                summ += left->pin[i*left->cols + p] * right->pin[p*right->cols + j];
            prod->pin[i*right->cols + j] = summ; 
        }
    }
}
