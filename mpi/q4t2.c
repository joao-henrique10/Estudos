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

int main(int argc, char **argv){
    int rank, size, tamLinhaColuna = 5;

    int A[tamLinhaColuna][tamLinhaColuna];
    int B[tamLinhaColuna][tamLinhaColuna];
    int C[tamLinhaColuna][tamLinhaColuna];

    MPI_Init( &argc , &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(size != 5){
        if (rank == 0){
            printf("Devem ter exatamente 5 processos\n");
        }
        MPI_Finalize();
        return 0;
    }

    if (rank == MASTER){
        // inicializo a matriz A
        printf("Matriz A:\n");
        for (int i = 0; i < tamLinhaColuna; i++){
            for (int j = 0; j < tamLinhaColuna; j++){
                A[i][j] = i + 10;
                printf("%d ",A[i][j]);
            }
            printf("\n");
        }

        printf("\n");
        // inicializo a matriz B
        printf("Matriz B:\n");
        for (int i = 0; i < tamLinhaColuna; i++){
            for (int j = 0; j < tamLinhaColuna; j++){
                B[i][j] = i + 10;
                printf("%d ",B[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        for (int i = 1; i < tamLinhaColuna; i ++){
            if(i == size - 1){
                MPI_Send( &A[i - 1][0] , 10 , MPI_INT , i , TAGA , MPI_COMM_WORLD);
                MPI_Send( &B[i - 1][0] , 10 , MPI_INT , i , TAGB , MPI_COMM_WORLD);
                MPI_Recv( &C[i - 1][0] , 10 , MPI_INT , i , TAGC , MPI_COMM_WORLD , MPI_STATUS_IGNORE);
            }
            else{
                MPI_Send( &A[i - 1][0] , 5 , MPI_INT , i , TAGA , MPI_COMM_WORLD);
                MPI_Send( &B[i - 1][0] , 5 , MPI_INT , i , TAGB , MPI_COMM_WORLD);
                MPI_Recv( &C[i - 1][0] , 5 , MPI_INT , i , TAGC , MPI_COMM_WORLD , MPI_STATUS_IGNORE);
            }
        }

        // printando o C
        printf("Matriz C:\n");
        for (int i = 0; i < tamLinhaColuna; i++){
            for(int j = 0; j < tamLinhaColuna; j++){
                printf("%d ",C[i][j]);
            }
            printf("\n");
        }

    }
    else{
        if (rank == size - 1){
            MPI_Recv( &A[rank - 1] , 10 , MPI_INT , MASTER , TAGA , MPI_COMM_WORLD , MPI_STATUS_IGNORE);
            MPI_Recv( &B[rank - 1] , 10 , MPI_INT , MASTER , TAGB , MPI_COMM_WORLD , MPI_STATUS_IGNORE);

            // definir os valores de C
            for (int i = rank - 1; i < tamLinhaColuna; i ++){
                for (int j = 0; j < tamLinhaColuna; j++){
                    C[i][j] = A[i][j] + B[i][j];
                }
            }

            // envio C para MASTER
            MPI_Send( &C[rank - 1][0] , 10 , MPI_INT , MASTER , TAGC , MPI_COMM_WORLD);
        }
        else{
            MPI_Recv( &A[rank - 1] , 5 , MPI_INT , MASTER , TAGA , MPI_COMM_WORLD , MPI_STATUS_IGNORE);
            MPI_Recv( &B[rank - 1] , 5 , MPI_INT , MASTER , TAGB , MPI_COMM_WORLD , MPI_STATUS_IGNORE);

            // definir os valores de C
            for (int j = 0; j < tamLinhaColuna; j++){
                C[rank - 1][j] = A[rank-1][j] + B[rank-1][j];
            }

            // envio C para MASTER
            MPI_Send( &C[rank - 1][0] , 5 , MPI_INT , MASTER , TAGC , MPI_COMM_WORLD);
        }

    }


    MPI_Finalize();
    return 0;
}