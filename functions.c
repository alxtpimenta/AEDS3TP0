#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

complexNumber multiplyComplexNumber(complexNumber A, complexNumber B)
{
    complexNumber Output;

    Output.X = (A.X * B.X)-(A.Y * B.Y);
    Output.Y = (A.Y * B.X)+(A.X * B.Y);

    return Output;
}

complexNumber addComplexNumber(complexNumber A, complexNumber B)
{
    complexNumber Output;

    Output.X = A.X + B.X;
    Output.Y = A.Y + B.Y;

    return Output;
}

int matrixOffset(int Colunas, int i, int j)
{
    return i * Colunas + j;
}

void printMatrix(Matrix M, FILE *file)
{
    int i,j;

    for(i=0;i<M.L;i++)
    {
        for(j=0;j<M.C;j++)
        {
            if(M.Body[matrixOffset(M.C,i,j)].Y >= 0)
                fprintf(file,"%g+%gi ",M.Body[matrixOffset(M.C,i,j)].X,M.Body[matrixOffset(M.C,i,j)].Y);
            else
                fprintf(file,"%g%gi ",M.Body[matrixOffset(M.C,i,j)].X,M.Body[matrixOffset(M.C,i,j)].Y);
        }
        fprintf(file,"\n");
    }

    fprintf(file,"\n");
}

void printMatrixSTDOUT(Matrix M)
{
    int i,j;
    printf("\n");

    for(i=0;i<M.L;i++)
    {
        for(j=0;j<M.C;j++)
        {
            if(M.Body[matrixOffset(M.C,i,j)].Y >= 0)
                printf("%g+%gi ",M.Body[matrixOffset(M.C,i,j)].X,M.Body[matrixOffset(M.C,i,j)].Y);
            else
                printf("%g%gi ",M.Body[matrixOffset(M.C,i,j)].X,M.Body[matrixOffset(M.C,i,j)].Y);
        }
        printf("\n");
    }

    printf("\n");
}
