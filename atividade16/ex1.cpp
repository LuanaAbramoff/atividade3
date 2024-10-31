#include <mpi.h>
#include <iostream>
#include <vector>
#include <cstdlib>  
#include <ctime>    

using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, num_processos;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);           
    MPI_Comm_size(MPI_COMM_WORLD, &num_processos);  

    const int tamanho_array = 100;
    int subarray_tamanho = tamanho_array / num_processos;
    vector<int> array;
    vector<int> subarray(subarray_tamanho);

    if (rank == 0) {

        srand(time(0));
        array.resize(tamanho_array);
        for (int i = 0; i < tamanho_array; i++) {
            array[i] = rand() % 100;  
        }
        cout << "Array inicializado no processo raiz: ";
        for (int val : array) cout << val << " ";
        cout << endl;
    }

    MPI_Scatter(array.data(), subarray_tamanho, MPI_INT, subarray.data(), subarray_tamanho, MPI_INT, 0, MPI_COMM_WORLD);

    double media_local = 0.0;
    for (int val : subarray) {
        media_local += val;
    }
    media_local /= subarray_tamanho;

    cout << "Processo " << rank << " - Média local: " << media_local << endl;

    vector<double> medias_locais;
    if (rank == 0) {
        medias_locais.resize(num_processos);
    }
    MPI_Gather(&media_local, 1, MPI_DOUBLE, medias_locais.data(), 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        double media_global = 0.0;
        for (double media : medias_locais) {
            media_global += media;
        }
        media_global /= num_processos;
        cout << "Média global calculada no processo raiz: " << media_global << endl;
    }

    MPI_Finalize();
    return 0;
}
