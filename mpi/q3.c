// Elabore um programa MPI que imprima um vetor de 100 posições (de po int),
// considerando o seguinte:
// • O vetor deve ser impresso da posição 0 até a posição 99, nesta ordem
// • O master deve inicializar o vetor de 100 posições da seguinte forma: v[i]=i
// • O master deve distribuir a impressão entre os workers de modo que todos
// possam imprimir pelo menos uma porção do vetor
// • Cada worker, uma vez acionado, deve imprimir o vetor a parr do ponto de
// impressão recebido do master
// • Considerar que este programa pode ser executado por, no máximo, 6
// processos (1 master e 5 workers)
// • O número de posições a serem impressas pelo worker deve obedecer a
// um oset dinâmico, ou seja, um valor randômico – menor que 15 – que é
// calculado por cada processo, no momento em que é acionado para imprimir
// o vetor
// • O programa deve controlar a impressão de modo que o vetor inteiro seja
// impresso, mas nenhuma posição seja impressa mais de uma vez. Por
// exemplo, se o worker anterior imprimiu até a posição 18 e o oset dinâmico
// calculado foi 10, a thread atual deve imprimir da posição 19 considerando
// 10 posições adiante
// • A ação dos workers e do master acaba quando o vetor de 100 posições ver
// sido todo impresso.

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define TAG 0
#define MASTER 0

int main(int argc, char** argv){
    int rank, size, chunk, slaves, tamvet = 100;
    int *vetor;
    int *vetorRecebimento;

    MPI_Init( &argc , &argv);
    MPI_Comm_size( MPI_COMM_WORLD , &size);
    MPI_Comm_rank( MPI_COMM_WORLD , &rank);

    slaves = size - 1;
    chunk = tamvet / slaves;
    if (rank == slaves){
        chunk = chunk + (tamvet % slaves);
    }

    if (rank == MASTER){
        //INICIALIZANDO O VETOR
        vetor = (int*)malloc(sizeof(int) * tamvet);
        for (int i = 0; i < tamvet; i++){
            vetor[i] = i;
        }

        for(int i = 1; i < size; i++){
            int inicio = (i - 1) * chunk;
            if(i == slaves){
                MPI_Send( &vetor[inicio] , chunk + (tamvet % slaves) , MPI_INT , i , TAG , MPI_COMM_WORLD);
            }
            else{
                MPI_Send( &vetor[inicio] , chunk , MPI_INT , i , TAG , MPI_COMM_WORLD);
            }
        }
        free(vetor);
    }
    else{
        vetorRecebimento = (int*)malloc(sizeof(int) * chunk);

        MPI_Recv( vetorRecebimento , chunk , MPI_INT , MASTER , TAG , MPI_COMM_WORLD , MPI_STATUS_IGNORE);

        printf("Vetor recebido no processo %d: ", rank);
        for(int i = 0; i < chunk; i++){
            printf("%d ", vetorRecebimento[i]);
        }
        printf("\n");

        free(vetorRecebimento);
    }

    MPI_Finalize();
    return 0;
}