#include <mpi.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, num_processos;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_processos);

    const int tamanho_array = 1000; 
    int segmento_tamanho = tamanho_array / num_processos;
    vector<float> array;
    vector<float> segmento(segmento_tamanho);

    if (rank == 0) {
        array.resize(tamanho_array);
        srand(time(0));
        for (int i = 0; i < tamanho_array; ++i) {
            array[i] = static_cast<float>(rand() % 100);  
        }
    }

    MPI_Scatter(array.data(), segmento_tamanho, MPI_FLOAT, segmento.data(), segmento_tamanho, MPI_FLOAT, 0, MPI_COMM_WORLD);

    float soma_local = 0.0;
    for (int i = 0; i < segmento_tamanho; ++i) {
        soma_local += segmento[i];
    }
    float media_local = soma_local / segmento_tamanho;

    float variancia_local = 0.0;
    for (int i = 0; i < segmento_tamanho; ++i) {
        variancia_local += (segmento[i] - media_local) * (segmento[i] - media_local);
    }
    variancia_local /= segmento_tamanho;

    vector<float> medias(num_processos);
    vector<float> variancias(num_processos);
    MPI_Gather(&media_local, 1, MPI_FLOAT, medias.data(), 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Gather(&variancia_local, 1, MPI_FLOAT, variancias.data(), 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        float media_global = 0.0;
        for (float m : medias) {
            media_global += m;
        }
        media_global /= num_processos;

        float variancia_global = 0.0;
        for (int i = 0; i < num_processos; ++i) {
            variancia_global += variancias[i] + (medias[i] - media_global) * (medias[i] - media_global);
        }
        variancia_global /= num_processos;

        float desvio_padrao_global = sqrt(variancia_global);
        cout << "Desvio padrão global: " << desvio_padrao_global << endl;
    }

    MPI_Finalize();
    return 0;
}