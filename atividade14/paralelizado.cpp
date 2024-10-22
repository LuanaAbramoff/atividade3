#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <omp.h>

// Função para gerar um número aleatório entre 0 e 1
double randomDouble() {
    return static_cast<double>(rand()) / RAND_MAX;
}

int main() {
    int numPontos; // Número total de pontos a serem gerados
    int dentroCirculo = 0; // Contador de pontos dentro do círculo

    std::cout << "Digite o número de pontos para a aproximação de pi: ";
    std::cin >> numPontos;

    // Inicializa o gerador de números aleatórios
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Paraleliza o laço for para que várias threads trabalhem simultaneamente
    #pragma omp parallel for reduction(+:dentroCirculo)
    for (int i = 0; i < numPontos; ++i) {
        double x = randomDouble(); // Coordenada x
        double y = randomDouble(); // Coordenada y

        // Verifica se o ponto (x, y) está dentro do círculo de raio 1
        if (x * x + y * y <= 1.0) {
            ++dentroCirculo;
        }
    }

    // Calcula a aproximação de pi
    double piAproximado = 4.0 * static_cast<double>(dentroCirculo) / numPontos;

    // Exibe o resultado
    std::cout << "Aproximação de pi: " << piAproximado << std::endl;

    return 0;
}
