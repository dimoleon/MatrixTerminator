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
    int r, c, real = 0, index, first, second, third;
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
        printf("-Create new Matrix(1)\n-Copy other Matrix.(2)\n-Pull values from other matrix in the form of rows and columns.(3)\n");

opi1: 

        fgets(input, 1024, stdin); 
        f = input[0]; 
        input[strlen(input) - 1] = '\0';  

        if(f == '1') 
        {
            query_id(name, v);
            query_dim(&r, &c); 

            init_matrix(&new, r, c, name); 
            query_values(new); 

            insert(new, &v); 
            new = NULL; 
            real++;
            getchar();
            goto start; 
        }

        if(f == '2') 
        {
            if(!v || real == 0) {
                puts("There is currently no other matrix stored in memory. Try again"); 
                goto opi1; 
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

            init_matrix(&new, (v->e[index])->rows, v->e[index]->cols, name);
            copy_matrix(new, v->e[index]);

            insert(new, &v); 
            new = NULL; 
            real++; 
            getchar();
            goto start; 
        }

        if(f == '3')
        {

        }

        if(f == 'q')
        {
            goto end;  
        }

        if(f == 'm')
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

        }
        else if(d == '1')   //Substraction; 
        {

        }
        else if(d == '2')   //Multiplication; 
        {
            
        }
        else if(d == '3')   //Transposition; 
        {
            
        }
        else if(d == '4')   //Scalar Multiplication; 
        {
            
        }
        else if(d == '5')   //Determinant; 
        {
            
        }
        else if(d == '6')   //Rank; 
        {
            
        }
        else if(d == '7')   //Row echelon form; 
        {
            
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

