#include <mpi.h>
#include <omp.h>
#include <iostream>
#include <ctime>

using namespace std;

int main(int argc, char** argv){
    MPI_Init(&argc, &argv);

    int rank, num_processos;
    MPI_Comm_rank( MPI_COMM_WORLD , &rank);
    MPI_Comm_size( MPI_COMM_WORLD,  &size);

    const int N = 10;
    int data[N][N];

    if(rank == 0){
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                data[i][j] = i + j;
            }
        }
    }


    int chunk_size = N / num_processos;
    int local_data[chunk_size][N];
    MPI_Scatter( data , chunk_size * N , MPI_INT , data , chunk_size * N, MPI_INT , 0 , MPI_COMM_WORLD);

    double tempo_inicio = MPI_Wtime();

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < chunk_size; i++){
        for(int j = 0; j < N; j++) {
            local_data[i][j] *= local_data[i][j];
        }
    }

    MPI_Gather( local_data , chunk_size * N , MPI_INT , data , chunk_size * N , MPI_INT , 0 , MPI_COMM_WORLD);

    double tempo_fim = MPI_Wtime();
    double tempo_local = tempo_fim - tempo_inicio;

    double tempo_maximo;
    MPI_Reduce(&tempo_local, &tempo_maximo, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        for (int i = 0; i < N; i++){
            for (int j = 0; j < N; j++){
                cout << data[i][j] << " ";
            }
            cout << endl;
        }

        double media_tempo = tempo_maximo / num_processos;
        cout << "---------------- USANDO PARALELIZAÇÃO COM OPENMP ----------------" << endl;
        cout << "Tempo gasto: " << media_tempo << endl;
        cout << "Tamanho da matriz: " << N << endl;
    }

    MPI_Finalize();
    return 0;

}