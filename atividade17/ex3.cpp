#include <mpi.h>
#include <omp.h>
#include <iostream>
#include <vector>
#include <numeric>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, num_processos;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_processos);

    const int N = 10;  // Tamanho do vetor
    std::vector<int> vetor;
    int tamanho_local = N / num_processos;
    int soma_local = 0;

    // Inicializa o vetor no processo 0
    if (rank == 0) {
        vetor.resize(N);
        srand(time(0));
        for (int i = 0; i < N; ++i) {
            vetor[i] = rand() % 100;
        }
    }

    // Cria um vetor local para receber a parte distribuída
    std::vector<int> parte_local(tamanho_local);

    // Distribui partes iguais do vetor para cada processo
    MPI_Scatter(vetor.data(), tamanho_local, MPI_INT, parte_local.data(), tamanho_local, MPI_INT, 0, MPI_COMM_WORLD);

    // Cada processo calcula a soma parcial usando OpenMP
    #pragma omp parallel for reduction(+:soma_local)
    for (int i = 0; i < tamanho_local; ++i) {
        soma_local += parte_local[i];
    }


    // Coleta todas as somas parciais no processo 0
    int soma_total = 0;
    MPI_Reduce(&soma_local, &soma_total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Processo 0 calcula a média
    if (rank == 0) {
        double media = static_cast<double>(soma_total) / N;
        std::cout << "A média do vetor é: " << media << std::endl;
        cout << "O tamanho do vetor é " << N << endl;
    }

    MPI_Finalize();
    return 0;
}
