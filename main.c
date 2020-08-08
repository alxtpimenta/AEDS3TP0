#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main(int argc, char *argv[])
{
    FILE *InputFile = fopen(argv[1],"r");

    if (InputFile == NULL)
    {
        printf("Erro ao abrir o arquivo de entrada!\n");
        return 0;
    }

    FILE *OutputFile = fopen(argv[2],"w");
    fclose(OutputFile);
    OutputFile = fopen(argv[2],"a");

    if (OutputFile == NULL)
    {
        printf("Erro ao abrir o arquivo de saida!\n");
        return 0;
    }

    int Instancias,i,j,x,y,inst=0;
    //MATRIZES A SEREM MULTIPLICADAS EM CADA INSTANCIA
    Matrix Matrix1;
    Matrix Matrix2;
    //MATRIZ FINAL (JÁ MULTIPLICADA)
    Matrix OutputMatrix;
    //ACUMULADOR PARA A MULTIPLIAÇÃO DE MATRIZES
    complexNumber sum;
    //STRING PARA ARMAZENAR AS INFORMAÇÕES LIDAS DO ARQUIVO INPUT
    char str[STR_MAX];
    //POINTEIRO PARA FUNÇÃO STRTOD
    char *pointer;

    //INÍCIO DA LEITURA DO ARQUIVO
    fgets(str,STR_MAX,InputFile);

    Instancias = atoi(str);

    printf("Numero de instancias: %d\n",Instancias);

    //LOOP DE INSTANCIAS
    while(Instancias > 0)
    {
        printf("----------Instancia %d----------\n",inst+1);
        //LER A PRIMEIRA MATRIZ
        fgets(str,STR_MAX,InputFile);
        Matrix1.L = atoi(strtok(str," "));
        Matrix1.C = atoi(strtok(NULL," "));
        printf("Matriz 1: Qtd. Linhas: %d Qtd. Colunas: %d\n",Matrix1.L,Matrix1.C);
        Matrix1.Body = (complexNumber*)malloc(Matrix1.L * Matrix1.C * sizeof(complexNumber));
        //PERCORRE AS STRINGS, PREENCHENDO OS VALORES NAS COLUNAS DA MATRIZ
        //USANDO STRTOK E STRTOD EM CONJUNTO, O STRTOK FRAGMENTA A STRING EM TOKENS, E O STRTOD LÊ OS NÚMEROS NOS TOKENS
        for(i=0;i<Matrix1.L;i++)
        {
            fgets(str,STR_MAX,InputFile);
            for(j=0;j<Matrix1.C;j++)
            {
                if(j==0)
                {
                    Matrix1.Body[matrixOffset(Matrix1.C,i,j)].X = strtod(strtok(str," "),&pointer);
                }
                else
                    Matrix1.Body[matrixOffset(Matrix1.C,i,j)].X = strtod(strtok(NULL," "),&pointer);

                Matrix1.Body[matrixOffset(Matrix1.C,i,j)].Y = strtod(pointer,NULL);
                //IMPRIME NO STDOUT O RESULTADO DA LEITURA
                if(Matrix1.Body[matrixOffset(Matrix1.C,i,j)].Y >= 0)
                    printf("Matriz 1 Corpo[%d][%d]: %g+%gi\n",i,j,Matrix1.Body[matrixOffset(Matrix1.C,i,j)].X,Matrix1.Body[matrixOffset(Matrix1.C,i,j)].Y);
                else
                    printf("Matriz 1 Corpo[%d][%d]: %g%gi\n",i,j,Matrix1.Body[matrixOffset(Matrix1.C,i,j)].X,Matrix1.Body[matrixOffset(Matrix1.C,i,j)].Y);
            }
        }
        //LER A SEGUNDA MATRIZ
        fgets(str,STR_MAX,InputFile);
        Matrix2.L = atoi(strtok(str," "));
        Matrix2.C = atoi(strtok(NULL," "));
        printf("Matriz 2: Qtd. Linhas: %d Qtd. Colunas: %d\n",Matrix2.L,Matrix2.C);
        Matrix2.Body = (complexNumber*)malloc(Matrix2.L * Matrix2.C * sizeof(complexNumber));
        //PERCORRE AS STRINGS, PREENCHENDO OS VALORES NAS COLUNAS DA MATRIZ
        //USANDO STRTOK E STRTOD EM CONJUNTO, O STRTOK FRAGMENTA A STRING EM TOKENS, E O STRTOD LÊ OS NÚMEROS NOS TOKENS
        for(i=0;i<Matrix2.L;i++)
        {
            fgets(str,STR_MAX,InputFile);
            for(j=0;j<Matrix2.C;j++)
            {
                if(j==0)
                {
                    Matrix2.Body[matrixOffset(Matrix2.C,i,j)].X = strtod(strtok(str," "),&pointer);
                }
                else
                    Matrix2.Body[matrixOffset(Matrix2.C,i,j)].X = strtod(strtok(NULL," "),&pointer);

                Matrix2.Body[matrixOffset(Matrix2.C,i,j)].Y = strtod(pointer,NULL);
                //IMPRIME NO STDOUT O RESULTADO DA LEITURA
                if(Matrix2.Body[matrixOffset(Matrix2.C,i,j)].Y >= 0)
                    printf("Matriz 2 Corpo[%d][%d]: %g+%gi\n",i,j,Matrix2.Body[matrixOffset(Matrix2.C,i,j)].X,Matrix2.Body[matrixOffset(Matrix2.C,i,j)].Y);
                else
                    printf("Matriz 2 Corpo[%d][%d]: %g%gi\n",i,j,Matrix2.Body[matrixOffset(Matrix2.C,i,j)].X,Matrix2.Body[matrixOffset(Matrix2.C,i,j)].Y);
            }
        }
        //TÉRMINO DE LEITURA DE MATRIZES
        //VERIFICA SE O NUMERO DE COLUNAS DA PRIMEIRA MATRIZ É IGUAL AO NUMERO DE LINHAS DA SEGUNDA MATRIZ
        if(Matrix1.C != Matrix2.L)
        {
            printf("Erro: Impossivel multiplicar as matrizes.\n");
            return 0;
        }
        //ALOCA O ESPAÇO PARA A MATRIX DE SAÍDA
        OutputMatrix.L = Matrix1.L;
        OutputMatrix.C = Matrix2.C;
        OutputMatrix.Body = (complexNumber*)malloc((OutputMatrix.L * OutputMatrix.C) * sizeof(complexNumber));
        //INICIO DA OPERAÇÃO DE MULTIPLICAÇÃO
        for(y=0;y<Matrix1.L;y++)
        {
            for(x=0;x<Matrix2.C;x++)
            {
                sum.X = 0;
                sum.Y = 0;
                for(i=0;i<Matrix1.C;i++)
                {
                    sum = addComplexNumber(sum,multiplyComplexNumber(Matrix1.Body[matrixOffset(Matrix1.C,y,i)],Matrix2.Body[matrixOffset(Matrix2.C,i,x)]));
                }
                OutputMatrix.Body[matrixOffset(OutputMatrix.C,y,x)] = sum;
            }
        }

        //IMPRIMIR A MATRIZ DE SAÍDA NO ARQUIVO DE OUTPUT E NO STDOUT
        printf("---Instancia %d: Matriz de saida---\n",inst+1);
        printMatrix(OutputMatrix,OutputFile);
        printMatrixSTDOUT(OutputMatrix);

        Instancias--;
        inst++;

        //DESALOCA O ESPAÇO DAS MATRIZES, PARA REALIZAR OUTRA INSTÂNCIA, OU PARA O FIM DO PROGRAMA
        free(Matrix1.Body);
        free(Matrix2.Body);
        free(OutputMatrix.Body);
    }

    fclose(InputFile);
    fclose(OutputFile);

    return 1;
}
