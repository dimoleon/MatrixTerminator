/* 
MATRIX TERMINATOR
*/

#include "matrix.h"

int main(void) {

    //memory vector
    struct matrix_list *v = NULL; 

    //helper variables; 
    struct matrix *new = NULL;
    char name[mxid]; 
    int r, c, real = 0, index, first, second, third, error = 0;
    char a, b, f, d, input[1023]; 


start:

    interactive = true; 
    putchar('\n'); 
    printf("What do you want the program to do? (Type 'm' for the main menu.)\n");

    fgets(input, 1024, stdin); 
    a = input[0]; 
    input[strlen(input) - 1] = '\0';  

    if(a == 'm') 
    {

Main_menu:

        printf("The program can do the following:\n-Create Matrix(1)\n-Load Matrices(2)\n-Edit Matrix(3)"
        "\n-View Existing Matrix(4)\n-Write(5)\n-Do Operations with Matrices(6)\n-Delete matrix(7)"
        "\n\n-You can always press (q) to quit and (m) for the main menu.\nJust press the code of the command you want to use!\n");

        goto start;

    } 
    else if(a == '1') 
    {

opi1: 

        printf("-Create new Matrix(1)\n-Copy other Matrix.(2)\n-Pull values from other matrix in the form of rows and columns.(3)\n");

        fgets(input, 1024, stdin); 
        f = input[0]; 
        input[strlen(input) - 1] = '\0';  

        if(f == '1') //new matrix
        {
            query_id(name, v);
            query_dim(&r, &c); 

            error = init_matrix(&new, r, c, name); 
            if(error) {
                puts("Error! Abort ship");
                goto end; 
            }
            query_values(new); 

            insert(new, &v); 
            new = NULL; 
            real++;

            getchar();
            goto start; 
        }

        if(f == '2') //copy matrix
        {
            if(!v || real == 0) {
                puts("There is currently no other matrix stored in memory. Going back..."); 
                goto start; 
            }

            char help[mxid]; 
            query_id(name, v);  

            do {
                printf("Give the name of the matrix you want to copy: "); 
                scanf("%s", help); 
                index = search_id(help, v);  
                if(index == -1)
                    puts("Name not found, try again."); 
            } while(index == -1);

            error = init_matrix(&new, (v->e[index])->rows, v->e[index]->cols, name);
            if(error) {
                puts("Error! Abort ship");
                goto end; 
            }
            copy_matrix(new, v->e[index]);

            insert(new, &v); 
            new = NULL; 
            real++; 
            getchar();
            goto start; 
        }

        if(f == '3') //pull values
        {

        }

        if(f == 'q') //quit
        {
            goto end;  
        }

        if(f == 'm') //menu 
        {
            goto Main_menu;
        }

        if(f != 1 && f != 2 && f != 3)
        {
            printf("Invalid input! Try again...\n\n");

            goto opi1;
        }
    }
    else if(a == '2')   //Load Matrix; 
    {
        interactive = false; 

        printf("Give path to import file: "); 
        char filepath[1023]; 
        fgets(filepath, 1024, stdin); 
        filepath[strlen(filepath) - 1] = '\0'; 

        FILE * reader; 
        reader = fopen(filepath, "r"); 

        while(!feof(reader)) {
             

        }

        fclose(reader); 
        goto start; 
    }
    else if(a == '3')   //Edit Matrix;
    {

    }
    else if(a == '4')   //View Existing Matrices; 
    {   
        if(!v || real == 0) {
            puts("There is currently no matrix stored in memory");
            goto start; 
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
            
            goto start; 
        }
        else if(b == '1')    //Show single; 
        {
            do {
                printf("Give the name of the matrix you want to show: ");
                scanf("%s", name); 
                index = search_id(name, v);  
                if(index == -1)
                    puts("Name not found, try again."); 
            } while(index == -1);
            show_matrix(v->e[index]); 

            getchar();
            goto start;
        }
        else if(b == 'm')   //Main Menu; 
        {
            goto Main_menu; 
        }
        else if(b == 'q')    //Quit
        {
            goto end;  
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
        goto start; 

    }
    else if(a == '6')   //Do Operations with Matrices;
    {
        if(!v || real == 0) {
            puts("There is currently no matrix stored in memory.");
            goto start; 
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

            do {
                printf("Give the name of the first matrix you want to add: ");
                scanf("%s", name); 
                first = search_id(name, v);  
                if(first == -1)
                    puts("Name not found, try again."); 
            } while(first == -1);

            show_matrix(v->e[first]); 

            do {
                printf("Give the name of the second matrix you want to add: ");
                scanf("%s", name); 
                second = search_id(name, v);  
                if(second == -1)
                    puts("Name not found, try again."); 
            } while(second == -1);

            show_matrix(v->e[second]); 

            if((v->e[first])->cols != (v->e[second])->cols || (v->e[first])->rows != (v->e[second])->cols) {
                puts("These matrices don't have the same dimensions. Going back..."); 
                getchar(); 
                goto start; 
            }

            query_id(name, v); 
            error = init_matrix(&new, (v->e[first])->rows, (v->e[first])->cols, name); 
            if(error) {
                puts("Error! Abort ship");
                goto end; 
            }

            sum(new, v->e[first], v->e[second]); 
            show_matrix(new); 

            insert(new, &v); 
            real++; 
            new = NULL;

            getchar(); 
            goto start;  

        }
        else if(d == '1')   //Substraction; 
        {

            puts("Substract two matrices. They must have the same dimensions!"); 

            do {
                printf("Give the name of the substrahend matrix: ");
                scanf("%s", name); 
                first = search_id(name, v);  
                if(first == -1)
                    puts("Name not found, try again."); 
            } while(first == -1);

            show_matrix(v->e[first]); 

            do {
                printf("Give the name of the substractor matrix: ");
                scanf("%s", name); 
                second = search_id(name, v);  
                if(second == -1)
                    puts("Name not found, try again."); 
            } while(second == -1);

            show_matrix(v->e[second]);

            if((v->e[first])->cols != (v->e[second])->cols || (v->e[first])->rows != (v->e[second])->cols) {
                puts("These matrices don't have the same dimensions. Going back..."); 
                getchar(); 
                goto start; 
            }

            query_id(name, v); 
            error = init_matrix(&new, (v->e[first])->rows, (v->e[first])->cols, name); 
            if(error) {
                puts("Error! Abort ship");
                goto end; 
            }

            difference(new, v->e[first], v->e[second]); 
            show_matrix(new); 

            insert(new, &v); 
            real++; 
            new = NULL;

            getchar(); 
            goto start;  
        }
        else if(d == '2')   //Multiplication; 
        {
             
            puts("Multiply two matrices. The number of columns of the first must be equal to the number of rows of the second!"); 

            do {
                printf("Give the name of the first multiplier matrix: ");
                scanf("%s", name); 
                first = search_id(name, v);  
                if(first == -1)
                    puts("Name not found, try again."); 
            } while(first == -1);

            show_matrix(v->e[first]); 

            do {
                printf("Give the name of the second multiplier matrix: ");
                scanf("%s", name); 
                second = search_id(name, v);  
                if(second == -1)
                    puts("Name not found, try again."); 
            } while(second == -1);

            show_matrix(v->e[second]); 

            if((v->e[first])->cols != (v->e[second])->rows) {
                puts("These matrices don't meet the dimension requirements for multiplication! Going back..."); 
                getchar(); 
                goto start; 
            }

            query_id(name, v); 
            error = init_matrix(&new, (v->e[first])->rows, (v->e[second])->cols, name); 
            if(error) {
                puts("Error! Abort ship");
                goto end; 
            }

            product(new, v->e[first], v->e[second]); 
            show_matrix(new);

            insert(new, &v); 
            real++; 
            new = NULL;

            getchar(); 
            goto start;  

        }
        else if(d == '3')   //Transposition; 
        {
            puts("Produce the transpose of a matrix."); 

            do {
                printf("Give the name of the matrix to be transposed: ");
                scanf("%s", name); 
                index = search_id(name, v);  
                if(index == -1)
                    puts("Name not found, try again."); 
            } while(index == -1);

            show_matrix(v->e[index]); 

            query_id(name, v); 
            error = init_matrix(&new, (v->e[index])->cols, (v->e[index])->rows, name); 
            if(error) {
                puts("Error! Abort ship"); 
                goto end; 
            }
            transpose(new, v->e[index]); 
            show_matrix(new); 

            insert(new, &v); 
            real++;
            new = NULL; 

            getchar();
            goto start; 
        }
        else if(d == '4')   //Scalar Multiplication; 
        {
            do {
                printf("Give the name of the matrix to be scaled: ");
                scanf("%s", name); 
                index = search_id(name, v);  
                if(index == -1)
                    puts("Name not found, try again."); 
            } while(index == -1);

            scalar(v->e[index]); 
            show_matrix(v->e[index]); 

            getchar(); 
            goto start;           
        }
        else if(d == '5')   //Determinant; 
        {   
            puts("Find the determinant of a square matrix. BETA ALGORITHM"); 

            do {
                printf("Give the name of the matrix: ");
                scanf("%s", name); 
                index = search_id(name, v);  
                if(index == -1)
                    puts("Name not found, try again."); 
            } while(index == -1); 

            show_matrix(v->e[index]); 

            if((v->e[index])->rows != (v->e[index])->cols) {
                puts("This is not a square matrix. Going back..."); 
                getchar(); 
                goto start; 
            }

            printf("The determinant is: %.2f\n", determinant(v->e[index])); 

            getchar(); 
            goto start; 
        }
        else if(d == '6')   //Rank; 
        {
            puts("Find the rank of a  matrix. BETA ALGORITHM"); 

            do {
                printf("Give the name of the matrix: ");
                scanf("%s", name); 
                index = search_id(name, v);  
                if(index == -1)
                    puts("Name not found, try again."); 
            } while(index == -1); 

            show_matrix(v->e[index]); 

            printf("The rank is: %d\n", rank(v->e[index])); 

            getchar(); 
            goto start;  
        }
        else if(d == '7')   //Reduced Row echelon form; 
        {
            puts("Attention! Reducing to row echelon form doesn't create a new matrix, but it modifies the given one. BETA ALGORITHM");

            do {
                printf("Give the name of the matrix to be reduced to row echelon form: ");
                scanf("%s", name); 
                index = search_id(name, v);  
                if(index == -1)
                    puts("Name not found, try again."); 
            } while(index == -1);

            rref(v->e[index]); 
            show_matrix(v->e[index]); 

            getchar();
            goto start; 
        }
        else if(d == 'a')   //Dot product; 
        {
            
        }
        else if(d == 'b')   //Cross product; 
        {
            
        }
        else if(d == 'c')   //Mixed product; 
        {

        }
        else if(d == 'm')   //Main Menu; 
        {
            goto Main_menu;  
        }
        else if(d == 'q')   //Quit; 
        {
            goto end;  
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
            goto start; 
        }

        do {
            printf("Give the name of the matrix you want to delete: ");
            scanf("%s", name); 
            index = search_id(name, v);  
            if(index == -1)
                puts("Name not found, try again."); 
        } while(index == -1);

        delete_matrix(&v->e[index]);
        real--; 
        
        getchar(); 
        goto start; 
    } 
    else if(a == 'q')    //Quit; 
    {
        goto end;  
    }
    else
    {
        printf("Invalid input! Try again..(Maybe type 'm' for th main menu.\n\n");
        goto start; 
    }

    
/*
    for(int i = 0; i < new->rows; i++) {
        for(int j = 0; j < new->cols; j++) 
            new->pin[i*(new->cols) + j] = rand()%20; 
    }
*/

end:

    if(v) {
        for(int i = 0; i < v->size; i++) 
            if(v->e[i])
                delete_matrix(&v->e[i]); 
        free(v); 
    }

    return 0; 
}

