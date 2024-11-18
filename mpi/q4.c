// Ulizando a biblioteca MPI, elabore um programa mul-processos para somar
// os elementos de duas matrizes A e B, quadradas (int ou oat), para gerar a
// matriz C, seguindo as seguintes regras: (i) O programa deve conter um processo
// master e quatro processos workers que deverão trabalhar em conjunto para
// garanr a realização de soma dos elementos das matrizes A e B; (ii) Supor que
// as matrizes são de 16 posições e as matrizes A e B devem ser inicializadas com
// números randômicos; (iii) As operações de soma devem ser distribuídas
// uniformemente entre os workers; (iv) Ao nal, a matriz C resultante deve ser
// impressa (em colunas, formato de matriz) pelo processo master

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define MASTER 0
#define TAGA 0
#define TAGB 1
#define TAGC 2
#define TAGA2 3
#define TAGB2 4


int main(int argc, char ** argv){
    int rank, size, slaves, matrizSize = 5;
    int A [matrizSize][matrizSize];
    int B [matrizSize][matrizSize];
    int C [matrizSize][matrizSize];


    MPI_Init( &argc , &argv);
    MPI_Comm_size( MPI_COMM_WORLD , &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    slaves = size - 1;

    if (rank == 0){
        //Matriz A
        printf("Matriz A:\n");
        for (int i = 0; i < matrizSize; i++){
            for (int j = 0; j < matrizSize; j++){
                A[i][j] = i + 10;
                printf("%d ", A[i][j]);
            }
            printf("\n");
        }

        //Matriz B
        printf("Matriz B:\n");
        for (int i = 0; i < matrizSize; i++){
            for (int j = 0; j < matrizSize; j++){
                B[i][j] = i + 10;
                printf("%d ", B[i][j]);
            }
            printf("\n");
        }

        // rank 1
        MPI_Send( &A[0][0] , 5 , MPI_INT , 1 , TAGA , MPI_COMM_WORLD);
        MPI_Send( &B[0][0] , 5 , MPI_INT , 1 , TAGB , MPI_COMM_WORLD);

        // rank 2

        MPI_Send( &A[1][0] , 5 , MPI_INT , 2 , TAGA , MPI_COMM_WORLD);
        MPI_Send( &B[1][0] , 5 , MPI_INT , 2 , TAGB , MPI_COMM_WORLD);

        // rank 3

        MPI_Send( &A[2][0] , 5 , MPI_INT , 3 , TAGA , MPI_COMM_WORLD);
        MPI_Send( &B[2][0] , 5 , MPI_INT , 3 , TAGB , MPI_COMM_WORLD);

        // rank 4

        MPI_Send( &A[3][0] , 10 , MPI_INT , slaves , TAGA , MPI_COMM_WORLD);
        MPI_Send( &B[3][0] , 10 , MPI_INT , slaves , TAGB , MPI_COMM_WORLD);

        // recebe do rank 4
        MPI_Recv( &C[3][0] , 10 , MPI_INT , slaves , TAGC , MPI_COMM_WORLD , MPI_STATUS_IGNORE);

        // recebe dos outros ranks
        for (int i = 1; i < slaves; i ++){
            MPI_Recv( &C[i - 1][0] , 5 , MPI_INT , i , TAGC , MPI_COMM_WORLD , MPI_STATUS_IGNORE);
        }

        printf("Matriz C recebida:\n");
        for (int i = 0; i < matrizSize; i++){
            for (int j = 0; j < matrizSize; j++){
                printf("%d ", C[i][j]);
            }
            printf("\n");
        }


    }
    else{
        if(rank == slaves){
            MPI_Recv( &A[3][0] , 10 , MPI_INT , MASTER , TAGA , MPI_COMM_WORLD , MPI_STATUS_IGNORE);
            MPI_Recv( &B[3][0] , 10 , MPI_INT , MASTER , TAGB , MPI_COMM_WORLD , MPI_STATUS_IGNORE);

            for (int i = 3; i < matrizSize; i ++){
                for(int j = 0; j < matrizSize; j++){
                    C[i][j] = A[i][j] + B[i][j];
                }
            }
            MPI_Send( &C[3][0] , 10 , MPI_INT , MASTER , TAGC , MPI_COMM_WORLD);
        }
        else{
            MPI_Recv( &A[rank - 1][0] , 5 , MPI_INT , MASTER , TAGA , MPI_COMM_WORLD , MPI_STATUS_IGNORE);
            MPI_Recv( &B[rank - 1][0] , 5 , MPI_INT , MASTER , TAGB , MPI_COMM_WORLD , MPI_STATUS_IGNORE);

            for (int j = 0; j < matrizSize; j++){
                C[rank - 1][j] = A[rank - 1][j] + B[rank - 1][j];
            }
            MPI_Send( &C[rank - 1][0] , 5 , MPI_INT , MASTER , TAGC , MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}