#include <iostream>
#include <map>
#include <vector>
#include <chrono>   
#include <random>
#include <algorithm>
#include <ctime>

using namespace std;

double geraZeroOuUm() {
    return static_cast<double>(rand()) / RAND_MAX;
}

int main() {

    int N = 100000;
    int dentroCirculo = 0;

    auto start = chrono::high_resolution_clock::now(); 

    srand(static_cast<unsigned int>(time(nullptr)));

    for(int i = 0; i < N; i ++) {
        double x = geraZeroOuUm();
        double y = geraZeroOuUm();

        cout << "X é " << x << "e" << "Y é" << y;

        if(x * x + y * y <= 1.0){
            dentroCirculo++;
        }
    }

    double piAproximado = 4.0 * static_cast<double>(dentroCirculo) / N;

    auto end = chrono::high_resolution_clock::now(); 

    std::chrono::duration<double> duration = end - start;
    double exec_time = duration.count();

    cout << "Aproximação de pi: " << piAproximado << endl;
    cout << "O tempo de execução foi: " << exec_time << " segundos" << endl;

    return 0;
}