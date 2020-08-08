// ESTE DEFINE � PARA A FUN��O fgets, PARA DETERMINAR A QUANTIDADE DE CARACTERES LIDOS A CADA LEITURA
#define STR_MAX 200
// O X REPRESENTA A PARTE REAL DO N�MERO COMPLEXO, E Y A PARTE IMAGIN�RIA
typedef struct complexNumber
{
    double X;
    double Y;
} complexNumber;

//L REPRESENTA O N�MERO DE LINHAS, E C O DE COLUNAS. O PONTEIRO *Body � ONDE A ALOCA��O DIN�MICA SER� FEITA
typedef struct Matrix
{
    complexNumber *Body;
    int L;
    int C;
} Matrix;

complexNumber multiplyComplexNumber(complexNumber A, complexNumber B);
complexNumber addComplexNumber(complexNumber A, complexNumber B);
int matrixOffset(int Colunas, int i, int j);
void printMatrix(Matrix M, FILE *file);
void printMatrixSTDOUT(Matrix M);
