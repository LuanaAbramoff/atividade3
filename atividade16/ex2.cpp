#include <mpi.h>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, num_processos;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  
    MPI_Comm_size(MPI_COMM_WORLD, &num_processos); 

    int num_iteracoes = 1000; 

    if (rank == 0) {
        num_iteracoes = 300;  
        cout << "Processo raiz define o número de iterações: " << num_iteracoes << endl;
    }

    MPI_Bcast(&num_iteracoes, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int resultado_local = 0;
    for (int i = 0; i < num_iteracoes; ++i) {
        resultado_local += i + rank; 
    }

    std::cout << "Processo " << rank << " - Resultado local após " 
              << num_iteracoes << " iterações: " << resultado_local << std::endl;

    MPI_Finalize();
    return 0;
}
