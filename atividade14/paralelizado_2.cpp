#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <omp.h>
#include <chrono>   
#include <random>

using namespace std;

int main() {
    int numPontos; // Número total de pontos a serem gerados
    int dentroCirculo = 0; // Contador de pontos dentro do círculo

    std::cout << "Digite o número de pontos para a aproximação de pi: ";
    std::cin >> numPontos;

    auto start = chrono::high_resolution_clock::now(); 

    // Paraleliza o laço for para que várias threads trabalhem simultaneamente
    #pragma omp parallel reduction(+:dentroCirculo)
    {
        // Cada thread terá um gerador de números aleatórios independente
        std::mt19937 gerador;
        std::uniform_real_distribution<double> distribuicao(0.0, 1.0);

        // Inicializa o gerador com uma semente única baseada no identificador da thread
        int thread_id = omp_get_thread_num();
        gerador.seed(std::time(nullptr) + thread_id);

        #pragma omp for
        for (int i = 0; i < numPontos; ++i) {
            double x = distribuicao(gerador); // Coordenada x
            double y = distribuicao(gerador); // Coordenada y

            // Verifica se o ponto (x, y) está dentro do círculo de raio 1
            if (x * x + y * y <= 1.0) {
                ++dentroCirculo;
            }
        }
    }

    auto end = chrono::high_resolution_clock::now(); 

    std::chrono::duration<double> duration = end - start;
    double exec_time = duration.count();

    // Calcula a aproximação de pi
    double piAproximado = 4.0 * static_cast<double>(dentroCirculo) / numPontos;

    // Exibe o resultado
    std::cout << "Aproximação de pi: " << piAproximado << std::endl;
    cout << "O tempo de execução foi: " << exec_time << " segundos" << endl;

    return 0;
}
