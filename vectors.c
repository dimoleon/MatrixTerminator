double dot_product(struct matrix *A, struct matrix *B)
{
double dp = 0;
if((A->cols)!= 1 || (B->cols)!= 1 || (A->cols)!=(B->cols))   //Checks if operation can be done
    {   printf("The Dot product only reffers to vectors! Meaning singular number of columns!");
        goto somewhere;
    }
for(int i = 0; i<A->rows; i++)
    {dp = dp + (A->pin[i]*B->pin[i]);}

return dp;
}

void cross_product(struct matrix *A, struct matrix *B, struct matrix *CP)
{
if( A->rows != 3 || B->rows != 3 || (A->cols)!= 1 || (B->cols)!= 1)
    {   
        printf("The cross product is only defined for vectors in 3D space,\n # of rows = 3\n # of cols = 1");
    }
else
    {
        (CP->pin)[0] = (A->pin)[1]*(B->pin[2])-(A->pin)[2]*(B->pin[1]);
        (CP->pin)[1] = (A->pin)[2]*(B->pin[0])-(A->pin)[0]*(B->pin[2]);
        (CP->pin)[2] = (A->pin)[0]*(B->pin[1])-(A->pin)[1]*(B->pin[0]);
    }
}


double mixed_product(struct matrix *A, struct matrix *B, struct matrix *C, struct matrix *MP)
{
if( A->rows != 3 || B->rows != 3 || C->rows != 3 || (A->cols)!= 1 || (B->cols)!= 1 || (A->cols)!= 1)
  {printf("All matrices must be vectors of 3D space! Try again..");}

struct matrix *temp;
cross_product(*B, *C, *temp);
return dot_product(*A, *temp);
}
