#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int randGen(int n)
{
    int output;
    output = rand()%n;
    return output;
}

int main()
{
    FILE *Output = fopen("testeout.txt","w");
    fclose(Output);
    Output = fopen("testeout.txt","a");

    srand((unsigned)time(NULL));

    int Instancias = 1000000; //NÚMERO DE INSTÂNCIAS A SEREM CRIADAS

    int MaxLinhas = 10; //NÚMERO MAXIMO DE LINHAS (ARBITRÁRIO)
    int MaxColunas = 10; //NÚMERO MÁXIMO DE COLUNAS (ARBITRÁRIO)
    int i,j,k;

    int colsMatriz1,linMatriz1,colsMatriz2,linMatriz2;

    int maxNum = 20; //NÚMERO MAXIMO A SER PREENCHIDO NAS MATRIZES (ARBITRÁRIO)

    //IMPRIME O NÚMERO DE INSTÂNCIAS NO ARQUIVO
    fprintf(Output,"%d\n",Instancias);

    for(i=0;i<Instancias;i++)
    {
        //GERAR DIMENSÔES DA MATRIZ 1
        colsMatriz1 = randGen(MaxColunas)+1;
        linMatriz1 = randGen(MaxLinhas)+1;

        //GERAR DIMENÕES DA MATRIZ 2
        colsMatriz2 = randGen(MaxColunas)+1;
        linMatriz2 = colsMatriz1;

        //IMPRIMIR DIMENSÕES DA MATRIZ 1
        fprintf(Output,"%d %d\n",linMatriz1,colsMatriz1);

        for(j=0;j<linMatriz1;j++)
        {
            for(k=0;k<colsMatriz1;k++)
            {
                //IMPRIME DAS LINHAS DA MATRIZ 1
                fprintf(Output,"%d+%di ",randGen(maxNum),randGen(maxNum));
            }
            fprintf(Output,"\n");
        }

        //IMPRIME AS DIMENSÔES DA MATRIZ 2
        fprintf(Output,"%d %d\n",linMatriz2,colsMatriz2);

        for(j=0;j<linMatriz2;j++)
        {
            for(k=0;k<colsMatriz2;k++)
            {
                //IMPRIME AS LINHAS DA MATRIZ 2
                fprintf(Output,"%d+%di ",randGen(maxNum),randGen(maxNum));
            }
            fprintf(Output,"\n");
        }
    }

    //FIM DO PROGRAMA

    fclose(Output);
    return 0;
}
