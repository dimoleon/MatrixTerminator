#include <stdio.h>
#include <string.h>
int
main (void) 
{
  
printf ("What do you want the program to do? (Type 0 for Options)");
  
int i;

there:
scanf ("%d", &i);
  
if (i == 0)
    
    {
      printf
	("The program can do the following:\n-Create Matrix(1)\n-Load Matrix(2)\n-Edit Matrix(3)\n-View Existing Matrix(4)\n-Write(5)\n-Do Operations with Matrices(6)\n\n Just press the code of the command you want to use!");
      
goto there;
      
if (i == 1)		// Create Matrix.
	{printf("-Create new Matrix(1)\n-Copy other Matrix.(2)\n-Pull values from other matrix in the form of rows and columns.(3)");
scanf ("%d", &i);
if (i == 1){}
if (i == 2){}
if (i == 3){}
	
}
      
if (i == 2)		// Load Matrix.
	{printf("Give path to import file");
	}
      
if (i == 3)		// Edit Matrix.
	{
	}
      
if (i == 4)		// View Existing Matrices.
	{printf("Do you want to show all matrices (0) or single? (Ίσως για κωδικό το id?)");
scanf("%d", &i);
if(i =0){}
if(i == id){}
	}

if (i == 5){}           // Write.        
if (i == 6)		// Do Operations with Matrices.
{
	  printf
	    ("These are the operation codes:-Addition(1).\n-Subtraction(2).\n-Multiplication(3).\n- Transposition(4).\n- Scalar Multiplication(5). \n-Determinant(6).\n-Row Echelon from(7)\n\n ~The following are for vectors only~\n\n-Dot product(8)\n-Cross product(9)\n-(Mixed) product(10).\n");
	  
scanf ("%d", &i);
	  
if (i == 1)		// Addition.
	    {
	    }
	  
if (i == 2)		// Subtraction.
	    {
	    }
	  
if (i == 3)		// Multiplication.
	    {
	    }
	  
if (i == 4)		// Transposition.
	    {
	    }

if (i == 5)		// Scalar Multiplication.
	    {
	    }

if (i == 6)		// Determinant.
	    {
	    }

if (i == 7)		// Row echelon form.
	    {
	    }
if (i == 8)		// Dot product.
	    {
	    }
if (i == 9)		// Cross product.
	    {
	    }
if (i == 10)		// (Mixed) product.
	    {
	    }	
}
      
return 0;
    
}
  
 
 
 
 
 
