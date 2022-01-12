#include <stdio.h>
#include <stdlib.h>
char i, j, k , l, input[1023];
int main (void) 
{
  
	printf ("What do you want the program to do? (Type 'm' for the main menu.)\n");
	start:
	fgets(input, 1024, stdin); 
	i = input[0]; 
	if (i == 'm')		    //Main Menu.
    
    {Main_Menu:
      printf
	("The program can do the following:\n-Create Matrix(1)\n-Load Matrix(2)\n-Edit Matrix(3)"
    "\n-View Existing Matrix(4)\n-Write(5)\n-Do Operations with Matrices(6)"
    "\n\n-You can always press (q) to quit and (m) for the main menu.\nJust press the code of the command you want to use!\n");
	goto start;
    }
      
	else if (i == '1')		// Create Matrix.
	{ 	printf("-Create new Matrix(1)\n-Copy other Matrix.(2)\n-Pull values from other matrix in the form of rows and columns.(3)\n");
    	opi1:
		fgets(input, 1024, stdin);
		k = input[0];
    	if (k == '1'){} 		                     //Create New.
    	if (k == '2'){}			                     // Copy other.
    	if (k == '3'){}			                     //Pull Values.
		if (k == 'q')                                //Quit.
        {printf("Goodbye!");           
        exit(0);}   
		if (k == 'm')
		{goto Main_Menu;}			                 // Main Menu.
    	if( k != 1 && k != 2 && k != 3)
		{printf("Invalid input! Try again..1\n\n");
    	goto opi1;}
	}
      
	else if (i == '2')		// Load Matrix.
	{	printf("Give path to import file");
	}
      
	else if (i == '3')		// Edit Matrix.
	{
	}
      
	else if (i == '4')		// View Existing Matrices.
	{	
		printf("Do you want to show all matrices (0) or a single?(1).\n");
        opi4:
		fgets(input, 1024, stdin);
		j = input[0];
		if(j == '0'){}		        // Show all.
		else if(j == '1'){}		    //Show single.
		else if(j == 'm')		    //Main Menu.
			{goto Main_Menu;} 
		else if(j == 'q')		    //Quit.
			{printf("Goodbye!");
        	exit(0);}
        else                        //Invalid input.
        	{printf("Invalid input! Try again.."); 
        	goto opi4;}
	}

	else if (i == '5')		// Write.
	{

	}                   

	else if (i == '6')		// Do Operations with Matrices.
	{
	  printf
	    ("These are the operation codes:\n-Addition(0).\n-Subtraction(1).\n-Multiplication(2).\n-Transposition(3)."
        "\n-Scalar Multiplication(4). \n-Determinant(5).\n-Row Echelon form(6).\n\n ~The following are for vectors only~"
        "\n\n-Dot product(7).\n-Cross product(Only 3D)(8).\n-Mixed product(Only 3D)(9).\n");
		opi6:
		fgets(input, 1024, stdin);
		l = input[0];	  
		if (l == '0')		    // Addition.
	    {
	    }
		else if (l == '1')		// Subtraction.
	    {
	    }
		else if (l == '2')		// Multiplication.
	    {
	    }
		else if (l == '3')		// Transposition.
	    {
	    }
		else if (l == '4')		// Scalar Multiplication.
	    {
	    }
		else if (l == '5')		// Determinant.
	    {
	    }
		else if (l == '6')		// Row echelon form.
	    {
	    }
		else if (l == '7')		// Dot product.
	    {
	    }
		else if (l == '8')		// Cross product.
	    {
	    }
		else if (l == '9')		// Mixed product.
	    {
	    }
		else if (l == 'm')		// Main Menu.
	    {goto Main_Menu;
	    }
		else if (l == 'q')		// Quit.
	    {printf("Goodbye!");
        exit(0);
	    }	
		else                    //Invalid Input.
		{	printf("Invalid Input! Try again..2");
			goto opi6;
		}
	}

	else if (i == 'q')		//Quit.
	{printf("Goodbye!");
    exit(0);}

	else	                //Invalid input.
	{printf("Invalid input! Try again..(Maybe type 'm' for th main menu.\n\n");
	goto start;
	}
	return 0;
}
