//Implement: Array of matrices, Product, Reduced Row Echelon Form, Dot Product, Cross Product, Determinant,
//Show matrices in memory, Load from file, 

//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include <assert.h>

#define mxdim 20 
#define mxname 15
#define mxinput 10

struct matrix {
    char id[mxname];
    int rows;
    int cols; 
    int **pin;
};

struct memvect {
    size_t size; 
    struct matrix index[]; 
};

int insertmat(struct memvect **memr, struct matrix new); 

void querynew(int *rp, int *cp);   
//void newmatrix(struct matrix *ptr, int r, int c); 
void deletematrix(struct matrix *ptr); 

struct matrix *find(); //

void transpose(struct matrix *transp, const struct matrix orig); 
void sum(struct matrix *sum, const struct matrix A, const struct matrix B); 
void diff(struct matrix *diff, const struct matrix A, const struct matrix B); 
void prod(struct matrix *prod, const struct matrix left, const struct matrix right);  

int main() {
    int r, c; 
    struct matrix new; 
//    for(int i = 0; i < new.rows; i++) {
//        for(int j = 0; j < new.cols + 1; j++) {
//            new.pin[i][j] = rand()%20;
//            printf("%3d ", new.pin[i][j]); 
//        }
//        putchar('\n'); 
//    }
    printf("%li\n", sizeof(struct matrix)); 
   return 0; 
}


int insertmat(struct memvect **memr, struct matrix new) {
    //size_t x = memr ? memr->size : 0; 
    // size_t y = x + 1;
    return 0; 
}

void querynew(int *rp, int *cp) {
    printf("Give matrix rows: "); 
    scanf("%d", rp); 
    printf("Give matrix columns: ");
    scanf("%d", cp); 
}

//int newmatrix(struct matrix **ptr, int r, int c) {
//    printf("Give new matrix name: "); 
//    scanf("%s", (*ptr)->id); 
//    (*ptr)->rows = r;
//    (*ptr)->cols = c; 
//}

void deletematrix(struct matrix *ptr) {
    for(int i = 0; i < ptr->rows; i++)
        free(ptr->pin[i]); 
    free(ptr->pin); 
    free(ptr);  //needs check
}

void transpose(struct matrix *transp, const struct matrix orig) {
    for(int i = 0; i < orig.rows; i++)
        for(int j = 0; j < orig.cols; j++)
            (transp->pin)[j][i] = orig.pin[i][j];
}

void sum(struct matrix *sum, const struct matrix A, const struct matrix B) {
    for(int i = 0; i < A.rows; i++) 
        for(int j = 0; j < A.cols; j++)
            (sum->pin)[i][j] = A.pin[i][j] + B.pin[i][j]; 
}

void diff(struct matrix *diff, const struct matrix A, const struct matrix B) {
    for(int i = 0; i < A.rows; i++) 
        for(int j = 0; j < A.cols; j++)
            (diff->pin)[i][j] = A.pin[i][j] - B.pin[i][j]; 
}

void prod(struct matrix *prod, const struct matrix left, const struct matrix right) {
    for(int i = 0; i < left.rows; i++) {
        for(int j = 0; j < right.cols; j++) {
            int summ = 0; 
            for(int p = 0; p < left.cols; p++) 
                summ += left.pin[i][p] + right.pin[p][j];
            (prod->pin)[i][j] = summ; 
        }
    }
}


