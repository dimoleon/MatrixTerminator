/* 
MATRIX TERMINATOR ::)
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "matrixheader.h"

//quick ERROR macro; primarily used for memory allocation checks; //stupidity at its finest; 
#define ERROR(A) if(A) {puts("ERROR. Abort ship!"); break;}

int main(void) {


    //memory vector
    struct matrix_list *v = NULL; 

    //helper variables; 
    struct matrix *new = NULL;
    char name[mxid]; 
    int r, c, real = 0, index, first, second, third; //real -> real count of matrices in memory vector; size of memory vector cannot be reduced;    
    char a, b, f, d, input[1024];  
    bool shouldask = true; 

    while(true) {

        interactive = true; 
        putchar('\n'); 
        printf("What do you want the program to do? (Type 'm' for the main menu.)\n");

        if(shouldask) {
            fgets(input, 1024, stdin); 
            a = input[0]; 
        } 

        input[strlen(input) - 1] = '\0';  

        if(a == 'm') 
        {

            printf("The program can do the following:\n-Create Matrix(1)\n-Load Matrices(2)\n-Edit Matrix(3)"
            "\n-View Existing Matrix(4)\n-Write(5)\n-Do Operations with Matrices(6)\n-Delete matrix(7)"
            "\n\n-You can always press (q) to quit and (m) for the main menu.\nJust press the code of the command you want to use!\n");

            shouldask = true; 

        } 
        else if(a == '1') 
        {

opi1: 

            printf("-Create new matrix(1)\n-Copy other matrix.(2)\n-Extract row or column of a matrix to create separate vector.(3)\n");

            fgets(input, 1024, stdin); 
            f = input[0]; 
            input[strlen(input) - 1] = '\0';  

            if(f == '1') //new matrix
            {
                query_id(name, v);
                query_dim(&r, &c); 

                ERROR(init_matrix(&new, r, c, name))
                
                query_values(new); 

                show_matrix(new); 

                ERROR(insert(new, &v))
                
                new = NULL; 
                real++;
                getchar();
            }
            else if(f == '2') //copy matrix
            {
                if(!v || real == 0) {
                    puts("There is currently no other matrix stored in memory. Going back..."); 
                    continue; 
                }

                query_id(name, v);  
                index = indexing(v, "Give the name of the matrix you want to copy: "); 

                ERROR(init_matrix(&new, (v->e[index])->rows, (v->e[index])->cols, name)) //lol you little...

                copy_matrix(new, v->e[index]);

                ERROR(insert(new, &v))

                new = NULL; 
                real++; 
                getchar();
            }
            else if(f == '3') //Extract row or column to create vector; 
            {
                if(!v || real == 0) {
                    puts("There is currently no other matrix stored in memory. Going back..."); 
                    continue; 
                }

                index = indexing(v, "Give the name of the matrix you will be extracting from: "); 

                show_matrix(v->e[index]); 
                getchar(); 

                int vecsize, dimcount; 
                bool roworcol;
                char detail[7]; 

                while(true) {
                    printf("Do you want to extract a row or a column? (Type 'r' for row, 'c' for column): "); 
                    fgets(input, 1024, stdin); 
                    char sel = input[0]; 
                    input[strlen(input) - 1] = '\0';
                    if(sel == 'r') {
                        roworcol = true;
                        break;
                    }
                    else if(sel == 'c') {
                        roworcol = false;
                        break;
                    }
                    else if(sel == '0')
                        goto opi1;
                    else
                        puts("Invalid input. Try again..."); 
                }

                if(roworcol) {
                    vecsize = (v->e[index])->cols; 
                    strcpy(detail, "row"); 
                    dimcount = (v->e[index])->rows; 
                } 
                else {
                    vecsize = (v->e[index])->rows; 
                    strcpy(detail, "column"); 
                    dimcount = (v->e[index])->cols; 
                }

                int n; 
                while(true) {        
                    printf("Give the number of the %s you want to extract: ", detail); 
                    scanf("%d", &n); 
                    if(1 <= n && n <= dimcount)
                        break;
                    puts("Out of bounds. Try again..."); 
                }
                n--;
                query_id(name, v); 
                ERROR(init_matrix(&new, vecsize, 1, name))

                if(roworcol) 
                    for(int i = 0; i < vecsize; i++) 
                        new->pin[i] = (v->e[index])->pin[n*(v->e[index])->cols + i]; 
                else
                    for(int i = 0; i < vecsize; i++) 
                        new->pin[i] = (v->e[index])->pin[i*(v->e[index])->cols + n]; 

                ERROR(insert(new, &v))

                new = NULL; 
                real++; 
                getchar(); 
            }
            else if(f == 'q') //quit
            {
                break; 
            }
            else if(f == 'm') //menu 
            {
                shouldask = false; 
                a = 'm'; 
            }
            else
            {
                printf("Invalid input! Try again...\n\n");
                goto opi1;
            }
        }
        else if(a == '2')   //Load Matrix; 
        {
            interactive = false; 

            printf("Give path to import file: "); 
            char loadpath[1024]; 
            fgets(loadpath, 1024, stdin); 
            loadpath[strlen(loadpath) - 1] = '\0'; 

            reader = fopen(loadpath, "r"); 
            if(!reader) {
                puts("File not found. Going back...");
                continue; 
            }

            int num;
            fscanf(reader, "%d", &num); 
            for(int i = 0; i < num; i++) {
                fscanf(reader, "%s", name); 
                if(v) 
                    if(search_id(name, v) != -1)
                        continue;

                query_dim(&r, &c); 
                init_matrix(&new, r, c, name);
                query_values(new); 
                
                ERROR(insert(new, &v))
                real++; 
            }

            fclose(reader); 
            if(num == 1)
                printf("%d Matrix loaded successfully.\n", num); 
            else 
                printf("%d Matrices loaded successfully.\n", num); 

        }
        else if(a == '3')   //Edit Matrix;
        {
            first = indexing(v, "Give the name of the matrix you want to edit: ");  

            show_matrix(v->e[first]);

            edit(v->e[first]);
            show_matrix(v->e[first]);

            getchar(); 
        }
        else if(a == '4')   //View Existing Matrices; 
        {   
            if(!v || real == 0) {
                puts("There is currently no matrix stored in memory");
                continue; 
            }
            printf("Do you want to show all matrices (0) or a single?(1).\n");

opi4: 

            fgets(input, 1024, stdin); 
            b = input[0]; 
            input[strlen(input) - 1] = '\0';  

            if(b == '0')    //Show all; 
            {
                for(int i = 0; i < v->size; i++) 
                    if(v->e[i]) 
                        show_matrix(v->e[i]); 
            }
            else if(b == '1')    //Show single; 
            {
                index = indexing(v, "Give the name of the matrix you want to show: "); 
                show_matrix(v->e[index]); 
                getchar();
            }
            else if(b == 'm')   //Main Menu; 
            {
                shouldask = false; 
                a = 'm'; 
            }
            else if(b == 'q')    //Quit
            {
                break; 
            }
            else
            {
                printf("Invalid input! Try again..."); 
                goto opi4;
            }

        }
        else if(a == '5')   //Write to memory; 
        {
            interactive = false; 
            if(!v || real == 0) {
                puts("There is currently no matrix stored in memory.");
                continue; 
            }

            printf("Give path to export file: "); 
            char writepath[1024]; 
            fgets(writepath, 1024, stdin); 
            writepath[strlen(writepath) - 1] = '\0';

            writer = fopen(writepath, "w"); 
            if(!writer) {
                puts("Unable to find or create file. Going back..."); 
                continue; 
            }

            fprintf(writer, "%d\n\n", real); 
            for(int i = 0; i < v->size; i++) 
                if(v->e[i]) 
                    show_matrix(v->e[i]);

            fclose(writer); 
            puts("Successful export."); 

        }
        else if(a == '6')   //Do Operations with Matrices;
        {
            if(!v || real == 0) {
                puts("There is currently no matrix stored in memory.");
                continue; 
            }     

            printf("These are the operation codes:\n-Addition(0).\n-Subtraction(1).\n-Multiplication(2).\n-Transposition(3)."
            "\n-Scalar Multiplication(4). \n-Determinant(5).\n-Rank(6).\n-Row Echelon form(7).\n\n ~The following are for vectors only~"
            "\n\n-Dot product(a).\n-Cross product(Only 3D)(b).\n-Mixed product(Only 3D)(c).\n");

opi6: 

            fgets(input, 1024, stdin); 
            d = input[0];
            input[strlen(input) - 1] = '\0';  

            if(d == '0')    //Addition; 
            {
                puts("Add two matrices. They must have the same dimensions!"); 

                first = indexing(v, "Give the name of the first matrix you want to add: "); 
                show_matrix(v->e[first]); 

                second = indexing(v, "Give the name of the second matrix you want to add: "); 
                show_matrix(v->e[second]); 

                if((v->e[first])->cols != (v->e[second])->cols || (v->e[first])->rows != (v->e[second])->cols) {
                    puts("These matrices don't have the same dimensions. Going back..."); 
                    getchar(); 
                    continue;
                }

                query_id(name, v); 
                ERROR(init_matrix(&new, (v->e[first])->rows, (v->e[first])->cols, name))

                sum(new, v->e[first], v->e[second]); 
                show_matrix(new); 

                ERROR(insert(new, &v))

                real++; 
                new = NULL;
                getchar(); 
            }
            else if(d == '1')   //Substraction; 
            {

                puts("Substract two matrices. They must have the same dimensions!"); 

                first = indexing(v, "Give the name of the substrahend matrix: "); 
                show_matrix(v->e[first]); 

                second = indexing(v, "Give the name of the substractor matrix: "); 
                show_matrix(v->e[second]);

                if((v->e[first])->cols != (v->e[second])->cols || (v->e[first])->rows != (v->e[second])->cols) {
                    puts("These matrices don't have the same dimensions. Going back..."); 
                    getchar(); 
                    continue; 
                }

                query_id(name, v); 
                ERROR(init_matrix(&new, (v->e[first])->rows, (v->e[first])->cols, name))

                difference(new, v->e[first], v->e[second]); 
                show_matrix(new); 

                ERROR(insert(new, &v))

                real++; 
                new = NULL;
                getchar(); 
            }
            else if(d == '2')   //Multiplication; 
            {
                 
                puts("Multiply two matrices. The number of columns of the first must be equal to the number of rows of the second!"); 

                first = indexing(v, "Give the name of the first multiplier matrix: "); 
                show_matrix(v->e[first]); 

                second = indexing(v, "Give the name of the second multiplier matrix: "); 
                show_matrix(v->e[second]); 

                if((v->e[first])->cols != (v->e[second])->rows) {
                    puts("These matrices don't meet the dimension requirements for multiplication! Going back..."); 
                    getchar(); 
                    continue; 
                }

                query_id(name, v); 
                ERROR(init_matrix(&new, (v->e[first])->rows, (v->e[second])->cols, name))

                product(new, v->e[first], v->e[second]); 
                show_matrix(new);

                ERROR(insert(new, &v))

                real++; 
                new = NULL;
                getchar(); 
            }
            else if(d == '3')   //Transposition; 
            {
                puts("Produce the transpose of a matrix."); 

                index = indexing(v, "Give the name of the matrix to be transposed: "); 
                show_matrix(v->e[index]); 

                query_id(name, v); 
                ERROR(init_matrix(&new, (v->e[index])->cols, (v->e[index])->rows, name))
                transpose(new, v->e[index]); 
                show_matrix(new); 

                ERROR(insert(new, &v))

                real++;
                new = NULL; 
                getchar();
            }
            else if(d == '4')   //Scalar Multiplication; 
            {
                index = indexing(v, "Give the name of the matrix to be scaled: ");

                scalar(v->e[index]); 
                show_matrix(v->e[index]); 

                getchar(); 
            }
            else if(d == '5')   //Determinant; 
            {   
                puts("Find the determinant of a square matrix. BETA ALGORITHM"); 

                index = indexing(v, "Give the name of the square matrix: "); 
                show_matrix(v->e[index]); 

                if((v->e[index])->rows != (v->e[index])->cols) {
                    puts("This is not a square matrix. Going back..."); 
                    getchar(); 
                    continue; 
                }

                printf("The determinant is: %.2f\n", determinant(v->e[index])); 

                getchar(); 
            }
            else if(d == '6')   //Rank; 
            {
                puts("Find the rank of a  matrix. BETA ALGORITHM"); 

                index = indexing(v, "Give the name of the matrix: "); 
                show_matrix(v->e[index]); 

                printf("The rank is: %d\n", rank(v->e[index])); 

                getchar(); 
            }
            else if(d == '7')   //Reduced Row echelon form; 
            {
                puts("Attention! Reducing to row echelon form doesn't create a new matrix, but it modifies the given one. BETA ALGORITHM");

                index = indexing(v, "Give the name of the matrix to be reduced to row echelon form: "); 

                rref(v->e[index]); 
                show_matrix(v->e[index]); 

                getchar();
            }
            else if(d == '8')   //Sort row or column of matrix;
            {
                puts("Attention! Sorting a row or column doesn't create a new matrix, but it modifies the given one."); 

                index = indexing(v, "Give the name of the matrix whose row or column you want to sort: "); 
                getchar(); 

                show_matrix(v->e[index]); 
                 
                bool roworcol;
                char detail[7]; 
                int vecsize, dimcount; 

                while(true) {
                    printf("Do you want to sort a row or a column? (Type 'r' for row, 'c' for column or '0' to go back): "); 
                    fgets(input, 1024, stdin); 
                    char sel = input[0]; 
                    input[strlen(input) - 1] = '\0';
                    if(sel == 'r') {
                        roworcol = true;
                        break;
                    }
                    else if(sel == 'c') {
                        roworcol = false;
                        break;
                    }
                    else if(sel == '0')
                        goto opi6;
                    else
                        puts("Invalid input. Try again..."); 
                }

                if(roworcol) {
                    vecsize = (v->e[index])->cols; 
                    strcpy(detail, "row"); 
                    dimcount = (v->e[index])->rows;
                } 
                else {
                    vecsize = (v->e[index])->rows; 
                    strcpy(detail, "column"); 
                    dimcount = (v->e[index])->cols;
                }
                
                int n; 
                while(true) {        
                    printf("Give the number of the %s you want to sort: ", detail); 
                    scanf("%d", &n); 
                    if(1 <= n && n <= dimcount)
                        break;
                    puts("Out of bounds. Try again..."); 
                }
                n--;

                getchar();

                bool ascdesorder; 
                while(true) {
                    printf("Do you want to sort in ascending or descending order? (Type 'a' for ascending, 'd' for descending): "); 
                    fgets(input, 1024, stdin); 
                    char sel = input[0]; 
                    input[strlen(input) - 1] = '\0';
                    if(sel == 'a') {
                        ascdesorder = true;
                        break;
                    }
                    else if(sel == 'd') {
                        ascdesorder = false;
                        break;
                    }
                    else
                        puts("Invalid input. Try again..."); 
                }
                
                float tobesorted[mxdim];
                if(roworcol) {
                    for(int i = 0; i < vecsize; i++)
                        tobesorted[i] = (v->e[index])->pin[n*(v->e[index])->cols + i];
                    mergesort(tobesorted, 0, vecsize - 1); 
                    if(ascdesorder) {
                        for(int i = 0; i < vecsize; i++)
                            (v->e[index])->pin[n*(v->e[index])->cols + i] = tobesorted[i];
                    }
                    else {
                        for(int i = 0; i < vecsize; i++)
                            (v->e[index])->pin[n*(v->e[index])->cols + i] = tobesorted[vecsize - 1 - i];
                    }
                }
                else {
                    for(int i = 0; i < vecsize; i++) 
                        tobesorted[i] = (v->e[index])->pin[i*(v->e[index])->cols + n];
                    mergesort(tobesorted, 0, vecsize - 1); 
                    if(ascdesorder) {
                        for(int i = 0; i < vecsize; i++)
                            (v->e[index])->pin[i*(v->e[index])->cols + n] = tobesorted[i];
                    }
                    else {
                        for(int i = 0; i < vecsize; i++)
                            (v->e[index])->pin[i*(v->e[index])->cols + n] = tobesorted[vecsize - 1 - i];
                    }
                }

                show_matrix(v->e[index]); 
            }
            else if(d == 'a')   //Dot product; got me there for a sec;  
            {
                puts("To get the dot product of two column matrices, or vectors, they must have the same number of rows!");

                first = indexing(v, "Give the name of the first vector of the dot product: "); 

                show_matrix(v->e[first]);

                second = indexing(v, "Give the name of the second vector of the dot product: "); 

                show_matrix(v->e[second]);

                if((v->e[first])->cols != 1 || (v->e[second])->cols != 1 || (v->e[first])->rows != (v->e[second])->rows)
                {       
                    puts("These matrices don't qualify for dot product. Going back..."); 
                    getchar(); 
                    continue; 
                }

                printf("The Dot product is %.2lf", dot_product(v->e[first], v->e[second]));

                getchar(); 
            }
            else if(d == 'b')   //Cross product; 
            {
                puts("For the cross product both matrices must be vectors (column matrices) of 3D space.\nRemember, order matters!");

                first = indexing(v, "Give the name of the first matrix: "); 
                show_matrix(v->e[first]);

                second = indexing(v, "Give the name of the second matrix: "); 
                show_matrix(v->e[second]);

                if((v->e[first])->rows != 3 || (v->e[second])->rows != 3 || (v->e[first])->cols != 1 || (v->e[second])->cols != 1) {
                    printf("The cross product is only defined for vectors in 3D space,\n # of rows = 3.\n # of cols = 1.");
                    getchar(); 
                    continue;
                } 

                query_id(name, v); 
                ERROR(init_matrix(&new, 3, 1, name))

                cross_product(v->e[first], v->e[second], new); 
                show_matrix(new);

                ERROR(insert(new, &v))

                real++; 
                new = NULL;
                getchar(); 
            }
            else if(d == 'c')   //Mixed product; 
            {
                puts("All matrices must be vectors of 3D space!\nThe second and third vectors will be cross multiplied and the result will be dot multiplied by the first!");

                first = indexing(v, "Give the name of the first multiplier matrix: "); 
                show_matrix(v->e[first]); 

                second = indexing(v, "Give the name of the second multiplier matrix: ");
                show_matrix(v->e[second]);

                third = indexing(v, "Give the name of the third multiplier matrix: "); 
                show_matrix(v->e[third]);

                if( (v->e[first])->rows != 3 || (v->e[second])->rows != 3 || (v->e[third])->rows != 3 ||(v->e[first])->cols != 1 || (v->e[second])->cols != 1 || (v->e[third])->cols != 1) {
                    printf("The cross product is only defined for vectors in 3D space,\n # of rows = 3.\n # of cols = 1.");
                    getchar(); 
                    continue; 
                }

                printf("The Mixed Product of the three matrices is %.2lf", mixed_product(v->e[first], v->e[second], v->e[third]));

                getchar(); 
            }
            else if(d == 'm')   //Main Menu; 
            {
                shouldask = false; 
                a = 'm'; 
            }
            else if(d == 'q')   //Quit; 
            {
                break; 
            }
            else
            {
                printf("Invalid input! Try again...");
                goto opi6;             
            }

        }
        else if(a == '7')    //Delete matrix; 
        {   
            if(!v || real == 0) {
                puts("There is currently no matrix stored in memory. Try again..."); 
                continue; 
            }
            printf("Are you sure you want to delete a matrix? ('y' for yes, 'n' for no): "); 

            fgets(input, 1024, stdin); 
            char confirm = input[0]; 
            if(confirm != 'y') {
                puts("Going back..."); 
                continue; 
            }

            index = indexing(v, "Give the name of the matrix you want to delete: "); 

            puts("Deleting matrix: "); 
            show_matrix(v->e[index]); 

            delete_matrix(&v->e[index]);

            real--; 
            getchar(); 
        } 
        else if(a == 'q')    //Quit; 
        {
            break; 
        }
        else
        {
            printf("Invalid input! Try again..(Maybe type 'm' for the main menu.\n\n");
        }
    }

    if(v) {
        for(int i = 0; i < v->size; i++) 
            if(v->e[i])
                delete_matrix(&v->e[i]); 
        free(v); 
    }

    return 0; 
}

