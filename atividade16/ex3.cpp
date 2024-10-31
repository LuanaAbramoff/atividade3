#include <mpi.h>
#include <omp.h>
#include <iostream>
#include <vector>
#include <algorithm>  
#include <cstdlib>   
#include <ctime>  

using namespace std;

int main(int argc, char** argv){
    MPI_Init(&argc, &argv);

    int rank, num_processos;
    MPI_Comm_rank( MPI_COMM_WORLD , &rank);
    MPI_Comm_size( MPI_COMM_WORLD,  &size);

    const int tamanho_array = 1000;
    int segmento_tamanho = tamanho_array / num_processos;
    vector<float> array;
    vector<float> segmento(segmento_tamanho);

    float max_val = 0.0;

    if(rank == 0){
        array.resize(tamanho_array);
        srand(time(0));

        for(int i = 0; i < tamanho_array; i++){
            array[i] = static_cast<float>(rand() % 100);
        }

        #pragma omp parallel for reduction(max:max_val)
        for (int i = 0; i < tamanho_array; i++){
            max_val = max(max_val, array[i]);
        }
        cout << "Processo raiz encontrou o valor máximo: " << max_val << endl;
    }

    MPI_Bcast( &max_val , 1 , MPI_FLOAT , 0 , MPI_COMM_WORLD);

    MPI_Scatter(array.data() , segmento_tamanho , MPI_FLOAT , segmento.data() ,segmento_tamanho , MPI_FLOAT , 0 , MPI_COMM_WORLD);

    for(int i = 0; i < segmento_tamanho; i++){
        segmento[i] /= max_val;
    }

    MPI_Gather( segmento.data() , segmento_tamanho , MPI_FLOAT , array.data() , segmento_tamanho , MPI_FLOAT , 0 , MPI_COMM_WORLD);

    if(rank == 0){
        cout << "Array normalizado: ";
        for(float val: array){
            cout << val << " ";
        }
        cout << endl;
    }

    MPI_Finalize();
    return 0;
}