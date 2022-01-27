#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#define mxid 10
const int mxdim = 20;
bool interactive = true; 

FILE * reader; //reader pointer
#define READP (interactive) ? (stdin) : (reader)

FILE * writer; //writer pointer
#define WRITEP (interactive) ? (stdout) : (writer) 
    
//fundamental definition of the matrix structure 
struct matrix {
    char id[mxid];      //name
    int rows;           //# of rows 
    int cols;           //# of columns 
    float pin[];        //array of values 2D, disguised as 1D (follows the pin[i*cols + j] format)
};

//dynamic array of matrices structure (wanna be)
struct matrix_list {
    size_t size;        //current array size 
    struct matrix *e[]; //array of pointers to struct matrix
};

//matrix initialization, given rows and columns and id; allocate memory 
int init_matrix(struct matrix **ptr, int r, int c, char name[mxid]) {
    void *temp = malloc(sizeof **ptr + r*c*sizeof(float));
    if(!temp)
        return 1;
    *ptr = temp; 
    strcpy(ptr[0]->id, name); 
    ptr[0]->rows = r;
    ptr[0]->cols = c;
    return 0;
}

//delete matrix, free memory and 'disable' the pointer;  
void delete_matrix(struct matrix **ptr) {
    free(*ptr);
    *ptr = NULL; 
}

//insert matrix in memory vector (super cool), double size of memory if it doesn't fit. 
int insert(struct matrix *m, struct matrix_list **v) {
    size_t x = *v ? v[0]->size : 0;
    size_t y = x + 1; 
    if((x & y) == 0) {
        void *temp = realloc(*v, sizeof **v + (x + y)*sizeof v[0]->e[0]);
        if(!temp)
            return 1;
        *v = temp; 
    }
    v[0]->e[x] = m;
    v[0]->size = y; 
    return 0; 
} 


//find index of matrix, given name; else return -1; 
int search_id(char s[mxid], const struct matrix_list *v) {
    for(size_t i = 0; i < v->size; i++) {
        if(v->e[i])
            if(strcmp(s, (v->e[i])->id) == 0)
                return i; 
    }
    return -1;
}

//ask matrix id, user input; 
//need to check if in database; (seperate function above, search_id) DONE!
void query_id(char s[mxid], const struct matrix_list *v) {
    if(interactive)
        printf("Give new matrix name (max 10 characters, no spaces): "); 

    fscanf(READP, "%s", s);
    if(v) {
        while(search_id(s, v) != -1) {
            puts("Duplicate names not allowed! Try again."); 
            printf("Give matrix name (max 10 characters, no spaces): "); 
            scanf("%s", s); 
        }
    }
}

//asks for matrix id for the task in message string and returns the matrix index in the memory vector; 
int indexing(struct matrix_list *v, char message[200]) {
    char help[mxid]; 
    int index; 
    do {
        printf("%s", message); 
        scanf("%s", help); 
        index = search_id(help, v);  
        if(index == -1)
            puts("Name not found, try again."); 
    } while(index == -1);
    return index; 
}

//ask dimensions (for new matrix creation), user input; 
void query_dim(int *pr, int *pc) {
    do {
        if(interactive) 
            printf("Give number of rows: ");

        fscanf(READP, "%d", pr); 
        if(*pr > mxdim || *pr < 1)
            printf("Dimensions must be positive and less than %d\n", mxdim+1); 
    } while(*pr > mxdim || *pr < 1);

    do {
        if(interactive) 
            printf("Give number of cols: ");

        fscanf(READP, "%d", pc); 
        if(*pc > mxdim || *pc < 1)
            printf("Dimensions must be positive and less than %d\n", mxdim+1); 
    } while(*pc > mxdim || *pc < 1);
}

//ask values (for new matrix), user input
void query_values(struct matrix *empty) {
    for(int i = 0; i < empty->rows; i++) {
        for(int j = 0; j < empty->cols; j++) {
            if(interactive)
                printf("Give value of %s[%d][%d]: ", empty->id, i+1, j+1); 
            fscanf(READP, "%f", &empty->pin[i*empty->cols + j]); 
        }
    }
}


//show fundamental values of given matrix, uses the WRITEP macro, can write to stdout or export file
//depending on the value of interactive; 
void show_matrix(struct matrix *mat) {
    fputs(mat->id, WRITEP); 
    fputc('\n', WRITEP); 
    fprintf(WRITEP, "%d %d\n", mat->rows, mat->cols);
    for(int i = 0; i < mat->rows; i++) {
        for(int j = 0; j < mat->cols; j++) {
            fprintf(WRITEP, "%.2f\t", mat->pin[i*(mat->cols) + j]);
        }
        fputc('\n', WRITEP);
    }
    fputc('\n', WRITEP); 
}

//transpose matrix
void transpose(struct matrix *transp, const struct matrix *orig) {
    assert(transp->rows == orig->cols && transp->cols == orig->rows); 
    for(int i = 0; i < orig->rows; i++)
        for(int j = 0; j < orig->cols; j++)
            (transp->pin)[j*orig->rows + i] = orig->pin[i*orig->cols  + j];
}

//matrix addition
void sum(struct matrix *sum, const struct matrix *A, const struct matrix *B) {
    assert(A->rows == B->rows && A->cols == B->cols);
    for(int i = 0; i < A->rows; i++) 
        for(int j = 0; j < A->cols; j++)
            (sum->pin)[i*A->cols + j] = A->pin[i*A->cols + j] + B->pin[i*B->cols + j]; 
}

//matrix substraction
void difference(struct matrix *diff, const struct matrix *A, const struct matrix *B) {
    assert(A->rows == B->rows && A->cols == B->cols);
    for(int i = 0; i < A->rows; i++) 
        for(int j = 0; j < A->cols; j++)
            (diff->pin)[i*A->cols + j] = A->pin[i*A->cols + j] - B->pin[i*B->cols + j]; 
}

//matrix multiplication O(rowsleft * colsright * common);
void product(struct matrix *prod, const struct matrix *left, const struct matrix *right) { 
    assert(left->cols == right->rows); 
    //int common = left->cols; 
    for(int i = 0; i < prod->rows; i++) {
        for(int j = 0; j < prod->cols; j++) {
            float summ = 0; 
            for(int p = 0; p < left->cols; p++) 
                summ += left->pin[i*left->cols + p] * right->pin[p*right->cols + j];
            prod->pin[i*right->cols + j] = summ; 
        }
    }
}

//scalar multiplication, modifies matrix, doesn't create new matrix; 
void scalar(struct matrix *m) {
    float sc; 
    puts("Attention! Multiplication by scalar doesn't create a new matrix, but it modifies the given one.");
    printf("Give the value of the scalar: ");
    scanf("%f", &sc); 
    for(int i = 0; i < m->rows; i++) 
        for(int j = 0; j < m->cols; j++) 
            m->pin[i*m->cols + j] *= sc; 
} 

//copies values of old matrix to new matrix, similar to strcpy;
void copy_matrix(struct matrix *kid, const struct matrix *parent) {
    assert(kid->rows == parent->rows && kid->cols == parent->cols);
    for(int i = 0; i < kid->rows; i++)
        for(int j = 0; j < kid->cols; j++)
            kid->pin[i*kid->rows + j] = parent->pin[i*parent->rows + j]; 
} 


//sane reduced row echelon form on a 2D array, gaussian elimination;
//probably works; returns number of row exchanges; O(rowc^2 * colc) ????
int realrref(float **p, int rowc, int colc) {
    //pivot column coordinate, number of row exchanges; used in determinant; 
    int lead = 0, count = 0; 

    //find current pivot coordinates
    for(int r = 0; r < rowc; r++) {
        if(colc <= lead)
            return count; 
        int i = r;
        while(p[i][lead] == 0) {
            i++;
            if(rowc == i) {
                i = r;
                lead++; 
                if(colc == lead) 
                    return count; 
            }
        }
        //exchange rows if pivot not in current row
        if(i != r) {
            count++; 
            for(int j = 0; j < colc; j++) {
                float temp = p[i][j];
                p[i][j] = p[r][j];
                p[r][j] = temp; 
            }
        }
        //perform the elimination (downwards and upwards)
        for(int h = 0; h < rowc; h++) {
            if(h != r) {
                float treason = p[h][lead]; 
                for(int j = 0; j < colc; j++) 
                    p[h][j] -= (p[r][j]/p[r][lead])*treason;
            }
        }
        //next column
        lead++; 
    }

    return count; 
}

//creates a 2D array, copies the values of the matrix, passes to realrref, and copies back the new values; 
void rref(struct matrix *m) {
    int rowc = m->rows, colc = m->cols;
    float **p; 
    p = (float **) malloc(rowc * sizeof(float)); 
    assert(p); 
    for(int row = 0; row < rowc; row++) {
        p[row] = (float *) malloc(colc * sizeof(float)); 
        assert(p[row]);
    }

    for(int i = 0; i < rowc; i++) 
        for(int j = 0; j < colc; j++) 
            p[i][j] = m->pin[i*colc + j]; 

    realrref(p, rowc, colc);    
    
    for(int i = 0; i < rowc; i++)
        for(int j = 0; j < colc; j++) 
            m->pin[i*colc + j] = p[i][j]; 

    for(int row = 0; row < rowc; row++)
        free(p[row]); 
    free(p); 
} 

//returns the determinant of square matrix; time complexity same as realrref;
float determinant(struct matrix *m) {

    int rowc = m->rows, colc = m->cols;
    assert(rowc == colc); 

    float **p; 
    p = (float **) malloc(rowc * sizeof(float)); 
    assert(p); 
    for(int row = 0; row < rowc; row++) {
        p[row] = (float *) malloc(colc * sizeof(float)); 
        assert(p[row]);
    }

    for(int i = 0; i < rowc; i++) 
        for(int j = 0; j < colc; j++) 
            p[i][j] = m->pin[i*colc + j]; 

    int coeffexp = realrref(p, rowc, colc) % 2;    

    float det = 1;
    for(int i = 0; i < rowc; i++) {
        det *= p[i][i];
    }

    for(int row = 0; row < rowc; row++)
        free(p[row]); 
    free(p);

    if(coeffexp == 1)
        det *= -1; 

    return det;
}

//returns the rank of the matrix; time complexity same as realrref; 
int rank(struct matrix *m) {
    int rowc = m->rows, colc = m->cols;

    float **p; 
    p = (float **) malloc(rowc * sizeof(float)); 
    assert(p); 
    for(int row = 0; row < rowc; row++) {
        p[row] = (float *) malloc(colc * sizeof(float)); 
        assert(p[row]);
    }

    for(int i = 0; i < rowc; i++) 
        for(int j = 0; j < colc; j++) 
            p[i][j] = m->pin[i*colc + j]; 

    realrref(p, rowc, colc);  


    for(int row = 0; row < rowc; row++)
        free(p[row]); 
    free(p);

    int rank = rowc; 
    for(int i = 0; i < rowc; i++) {
        bool allzero = true; 
        for(int j = 0; j < colc; j++) {
            if(p[i][j] != 0) {
                allzero = false; 
                break;
            }
        }

        if(allzero)
            rank--;
    }

    return rank; 
}

//returns the dot product of the two marices in the form of a double;
double dot_product(struct matrix *A, struct matrix *B)
{
    assert((A->cols) == 1 && (B->cols) == 1 && (A->rows) == (B->rows));
    double dp = 0;
    for(int i = 0; i<A->rows; i++)
        {
            dp = dp + ((A->pin[i]) * (B->pin[i]));
        }

    return dp;
}

//Cross Product;
void cross_product(struct matrix *A, struct matrix *B, struct matrix *CP)
{
    assert(A->rows == 3 && B->rows == 3 && (A->cols) == 1 && (B->cols) == 1);

    CP->pin[0] = (A->pin[1] * B->pin[2]) - (A->pin[2] * B->pin[1]);
    CP->pin[1] = (A->pin[2] * B->pin[0]) - (A->pin[0] * B->pin[2]);
    CP->pin[2] = (A->pin[0] * B->pin[1]) - (A->pin[1] * B->pin[0]);
}

//Mixed product;
double mixed_product(struct matrix *A, struct matrix *B, struct matrix *C)
{
    assert(A->rows == 3 && B->rows == 3 && C->rows == 3 && (A->cols) == 1 && (B->cols) == 1 && (C->cols) == 1);

    struct matrix *temp;
    char sth[mxid] = "temp"; 
    init_matrix(&temp, 3, 1, sth);
    cross_product(B, C, temp);
    double res = dot_product(A, temp); 
    delete_matrix(&temp); 

    return res; 
}

//edits elements of given matrix, one by one until users escapes; 
void edit(struct matrix *A)
{
    int i, j;
    float new_value;        
    do{
        printf("Whats the position of the element you want to edit?\n(To exit the loop insert 0 for any dimension)\nFormat: (rows)<SPACE>(cols).\n");
        scanf("%d %d", &i, &j);

        if(i == 0 || j == 0)
            break;
       
        if(i >= A->rows + 1 || j >= A->cols + 1) {
            puts("Cell coordinates out of bounds. Try again..."); 
            continue; 
        }
        printf("What's the value you want to change it to?\n");
        scanf("%f", &new_value);
        A->pin[(i-1)*(A->cols) +j-1] = new_value;
    } while(i != 0 && j != 0);
}

//merge two arrays, sorted;
void merge(float *p, int left, int mid, int right) {
    int i, j, k; //indexing
    int sizeleft = mid - left + 1; 
    int sizeright = right - mid; 

    //helper arrays; 
    float L[sizeleft], R[sizeright]; 

    //copy elements
    for(int c = 0; c < sizeleft; c++)
        L[c] = p[left + c]; 
    for(int c = 0; c < sizeright; c++) 
        R[c] = p[mid + c + 1];  

    //initial merging 
    i = 0, j = 0, k = left; 
    while(i < sizeleft && j < sizeright) {
        if(L[i] <= R[j]) {
            p[k] = L[i]; 
            i++; 
        }
        else {
            p[k] = R[j]; 
            j++; 
        }
        k++;
    }

    //copy remaining elements from the left array or from the right array, cannot happen simultaneously;
    while(i < sizeleft) {
        p[k] = L[i];
        i++; 
        k++; 
    }
    while(j < sizeright) {
        p[k] = R[j];
        j++; 
        k++; 
    }
}

//mergesort, recursively break in halves and merge sorted subarrays; O(nlogn)
void mergesort(float *p, int left, int right) {
    if(left < right) {
        //avoiding overflow
        int mid = left + (right - left)/2;

        mergesort(p, left, mid); 
        mergesort(p, mid + 1, right); 
        merge(p, left, mid, right); 
    }
}

