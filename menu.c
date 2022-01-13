#include <stdio.h>
#include <stdlib.h>
char a, b, c , d, input[1023];
int main (void) 
{
  
	printf ("What do you want the program to do? (Type 'm' for the main menu.)\n");
	start:
	fgets(input, 1024, stdin); 
	a = input[0]; 
	if (a == 'm')		    //Main Menu.
    
    {Main_Menu:
      printf
	("The program can do the following:\n-Create Matrix(1)\n-Load Matrix(2)\n-Edit Matrix(3)"
    "\n-View Existing Matrix(4)\n-Write(5)\n-Do Operations with Matrices(6)"
    "\n\n-You can always press (q) to quit and (m) for the main menu.\nJust press the code of the command you want to use!\n");
	goto start;
    }
      
	else if (a == '1')		// Create Matrix.
	{ 	printf("-Create new Matrix(1)\n-Copy other Matrix.(2)\n-Pull values from other matrix in the form of rows and columns.(3)\n");
    	opi1:
		fgets(input, 1024, stdin);
		c = input[0];
    	if (c == '1'){} 		                     //Create New.
    	if (c == '2'){}			                     // Copy other.
    	if (c == '3'){}			                     //Pull Values.
		if (c == 'q')                                //Quit.
        {printf("Goodbye!");           
        exit(0);}   
		if (c == 'm')
		{goto Main_Menu;}			                 // Main Menu.
    	if( c != 1 && c != 2 && c != 3)
		{printf("Invalid input! Try again..1\n\n");
    	goto opi1;}
	}
      
	else if (a == '2')		// Load Matrix.
	{	printf("Give path to import file");
	}
      
	else if (a == '3')		// Edit Matrix.
	{
	}
      
	else if (a == '4')		// View Existing Matrices.
	{	
		printf("Do you want to show all matrices (0) or a single?(1).\n");
        opi4:
		fgets(input, 1024, stdin);
		b = input[0];
		if(b == '0'){}		        // Show all.
		else if(b == '1'){}		    //Show single.
		else if(b == 'm')		    //Main Menu.
			{goto Main_Menu;} 
		else if(b == 'q')		    //Quit.
			{printf("Goodbye!");
        	exit(0);}
        else                        //Invalid input.
        	{printf("Invalid input! Try again.."); 
        	goto opi4;}
	}

	else if (a == '5')		// Write.
	{

	}                   

	else if (a == '6')		// Do Operations with Matrices.
	{
	  printf
	    ("These are the operation codes:\n-Addition(0).\n-Subtraction(1).\n-Multiplication(2).\n-Transposition(3)."
        "\n-Scalar Multiplication(4). \n-Determinant(5).\n-Row Echelon form(6).\n\n ~The following are for vectors only~"
        "\n\n-Dot product(7).\n-Cross product(Only 3D)(8).\n-Mixed product(Only 3D)(9).\n");
		opi6:
		fgets(input, 1024, stdin);
		d = input[0];	  
		if (d == '0')		    // Addition.
	    {
	    }
		else if (d == '1')		// Subtraction.
	    {
	    }
		else if (d == '2')		// Multiplication.
	    {
	    }
		else if (d == '3')		// Transposition.
	    {
	    }
		else if (d == '4')		// Scalar Multiplication.
	    {
	    }
		else if (d == '5')		// Determinant.
	    {
	    }
		else if (d == '6')		// Row echelon form.
	    {
	    }
		else if (d == '7')		// Dot product.
	    {
	    }
		else if (d == '8')		// Cross product.
	    {
	    }
		else if (d == '9')		// Mixed product.
	    {
	    }
		else if (d == 'm')		// Main Menu.
	    {goto Main_Menu;
	    }
		else if (d == 'q')		// Quit.
	    {printf("Goodbye!");
        exit(0);
	    }	
		else                    //Invalid Input.
		{	printf("Invalid Input! Try again..2");
			goto opi6;
		}
	}

	else if (a == 'q')		//Quit.
	{printf("Goodbye!");
    exit(0);}

	else	                //Invalid input.
	{printf("Invalid input! Try again..(Maybe type 'm' for th main menu.\n\n");
	goto start;
	}
	return 0;
}
//Be careful with the comments after if statements, they may end up after the {} brackets..
