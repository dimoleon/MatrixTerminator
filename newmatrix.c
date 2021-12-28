/* 
MATRIX OPERATOR 
*/

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <assert.h>

#define mxid 10
const int mxdim = 20;

//fundamental definition of the matrix structure 
struct matrix {
    char id[mxid];  //name
    int rows;       //# of rows 
    int cols;       //# of columns 
    int pin[];      //array of values 2D, disguised as 1D (follows the pin[i*cols + j] format)
};

//dynamic array structure of matrices
struct matr_list {
    size_t size; 
    struct matrix **elem[]; 
};

//matrix initialization, given rows and columns; allocate memory and ask id
int init_matrix(struct matrix **ptr, int r, int c) {
    void *temp = malloc(sizeof **ptr + r*c*sizeof(int));
    if(!temp)
        return 1;
    *ptr = temp; 
    printf("Give matrix name: ");
    scanf("%s", ptr[0]->id); 
    ptr[0]->rows = r;
    ptr[0]->cols = c;
    return 0;
}

//delete matrix
void delete_matrix(struct matrix **ptr) {
    free(*ptr);
    free(ptr); //needs check 
}

//ask dimensions, user input
void query_dim(int *pr, int *pc) {
    do {
        printf("Give number of rows: ");
        scanf("%d", pr); 
        if(*pr > mxdim || *pr < 1)
            printf("Dimensions must be positive and less than %d\n", mxdim+1); 
    } while(*pr > mxdim || *pr < 1);

    do {
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
    printf("%d %d\n", mat->rows, mat->cols);
    puts(mat->id); 
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

int main() {
    struct matrix *left = NULL, *right = NULL;  
    int r, c;
    query_dim(&r, &c);
    if(init_matrix(&left, r, c))
        puts("Houston"); 
    query_values(left);
    show_matrix(left); 

    query_dim(&r, &c); 
    if(init_matrix(&right, r, c))
        puts("Houston"); 
    query_values(right); 
    show_matrix(right); 

    struct matrix *prod = NULL; 
    if(left->cols == right->rows) {
        if(init_matrix(&prod, left->rows, right->cols))
            puts("Houston");
        product(prod, left, right); 
        show_matrix(prod);
    }
    
/*
    for(int i = 0; i < new->rows; i++) {
        for(int j = 0; j < new->cols; j++) 
            new->pin[i*(new->cols) + j] = rand()%20; 
    }
*/
    return 0; 
}

