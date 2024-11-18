// Utilizando a biblioteca MPI, elabore um programa para somar os elementos de duas matrizes A e B, quadradas (int), para gerar uma
// matriz C, de acordo com as seguintes regras:
// O programa deve conter um processo master e dois workers, que deverão trabalhar em conjunto para garantir a realização de soma
// dos elementos das matrizes A e B
// Supor que as matrizes sejam de 16 posições (int) e as matrizes A e B devem ser inicializadas com valores randômicos
// As operações de soma devem ser distribuídas entre os workers, de modo que a primeira e a terceira linha das matrizes sejam
// processadas pelo primeiro worker e a segunda e a quarta linha sejam processadas pelo segundo worker
// A comunicação entre os processos master e workers deve ser feita utilizando especicamente as funções MPI_Send e MPI_Recv
// Ao nal, a matriz C resultante deve ser impressa (em colunas, formato de matriz) pelo processo master

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define MASTER 0
#define TAGA 0
#define TAGB 1
#define TAGC 2
#define TAGA2 3
#define TAGB2 3
#define TAGC2 4

int main(int argc, char ** argv){
    int rank, size, tamLinhaColuna = 4;

    int A[tamLinhaColuna][tamLinhaColuna];
    int B[tamLinhaColuna][tamLinhaColuna];
    int C[tamLinhaColuna][tamLinhaColuna];

    MPI_Init( &argc , &argv);
    MPI_Comm_size( MPI_COMM_WORLD , &size);
    MPI_Comm_rank( MPI_COMM_WORLD , &rank);

    if (rank == MASTER){

        printf("Matriz A:\n");
        for (int i = 0; i < tamLinhaColuna; i++){
            for(int j = 0; j < tamLinhaColuna; j++){
                A[i][j] = i + 10;
                printf("%d ",A[i][j]);
            }
            printf("\n");
        }

        printf("Matriz B:\n");
        for (int i = 0; i < tamLinhaColuna; i++){
            for(int j = 0; j < tamLinhaColuna; j++){
                B[i][j] = i + 10;
                printf("%d ",B[i][j]);
            }
            printf("\n");
        }

        MPI_Send( &A[0][0] , 4 , MPI_INT , 1 , TAGA , MPI_COMM_WORLD);
        MPI_Send( &B[0][0] , 4 , MPI_INT , 1 , TAGB , MPI_COMM_WORLD);
        MPI_Send( &A[1][0] , 4 , MPI_INT , 2 , TAGA , MPI_COMM_WORLD);
        MPI_Send( &B[1][0] , 4 , MPI_INT , 2 , TAGB , MPI_COMM_WORLD);

        MPI_Send( &A[2][0] , 4 , MPI_INT , 1 , TAGA2 , MPI_COMM_WORLD);
        MPI_Send( &B[2][0] , 4 , MPI_INT , 1 , TAGB2 , MPI_COMM_WORLD);
        MPI_Send( &A[3][0] , 4 , MPI_INT , 2 , TAGA2 , MPI_COMM_WORLD);
        MPI_Send( &B[3][0] , 4 , MPI_INT , 2 , TAGB2 , MPI_COMM_WORLD);

        MPI_Recv( &C[0][0] , 4 , MPI_INT , 1 , TAGC , MPI_COMM_WORLD , MPI_STATUS_IGNORE);
        MPI_Recv( &C[2][0] , 4 , MPI_INT , 1 , TAGC2 , MPI_COMM_WORLD , MPI_STATUS_IGNORE);
        MPI_Recv( &C[1][0] , 4 , MPI_INT , 2 , TAGC , MPI_COMM_WORLD , MPI_STATUS_IGNORE);
        MPI_Recv( &C[3][0] , 4 , MPI_INT , 2 , TAGC2 , MPI_COMM_WORLD , MPI_STATUS_IGNORE);

        printf("Matriz C:\n");
        for (int i = 0; i < tamLinhaColuna; i++){
            for (int j = 0; j < tamLinhaColuna; j++){
                printf("%d ", C[i][j]);
            }
            printf("\n");
        }
        
    }
    else{
        if (rank == 1){
            MPI_Recv( &A[0][0] , 4 , MPI_INT , MASTER , TAGA , MPI_COMM_WORLD , MPI_STATUS_IGNORE);
            MPI_Recv( &A[2][0] , 4 , MPI_INT , MASTER , TAGA2 , MPI_COMM_WORLD , MPI_STATUS_IGNORE);
            MPI_Recv( &B[0][0] , 4 , MPI_INT , MASTER , TAGB , MPI_COMM_WORLD , MPI_STATUS_IGNORE);
            MPI_Recv( &B[2][0] , 4 , MPI_INT , MASTER , TAGB2 , MPI_COMM_WORLD , MPI_STATUS_IGNORE);

            for (int i = 0; i < tamLinhaColuna; i++){
                C[0][i] = A[0][i] + B[0][i];
                C[2][i] = A[2][i] + B[2][i];
            }

            MPI_Send( &C[0][0] , 4 , MPI_INT , MASTER , TAGC , MPI_COMM_WORLD);
            MPI_Send( &C[2][0] , 4 , MPI_INT , MASTER , TAGC2 , MPI_COMM_WORLD);

        }
        else{
            MPI_Recv( &A[1][0] , 5 , MPI_INT , MASTER , TAGA , MPI_COMM_WORLD , MPI_STATUS_IGNORE);
            MPI_Recv( &A[3][0] , 5 , MPI_INT , MASTER , TAGA2 , MPI_COMM_WORLD , MPI_STATUS_IGNORE);
            MPI_Recv( &B[1][0] , 5 , MPI_INT , MASTER , TAGB , MPI_COMM_WORLD , MPI_STATUS_IGNORE);
            MPI_Recv( &B[3][0] , 5 , MPI_INT , MASTER , TAGB2 , MPI_COMM_WORLD , MPI_STATUS_IGNORE);   

            for (int i = 0; i < tamLinhaColuna; i++){
                C[1][i] = A[1][i] + B[1][i];
                C[3][i] = A[3][i] + B[3][i];
            }

            MPI_Send( &C[1][0] , 4 , MPI_INT , MASTER , TAGC , MPI_COMM_WORLD);
            MPI_Send( &C[3][0] , 4 , MPI_INT , MASTER , TAGC2 , MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;

}