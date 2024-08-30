#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <chrono>     // Inclui a biblioteca para medição de tempo.

using namespace std;

struct Objeto{
    int peso;
    int valor;
};

void lerArquivo(const std::string& nomeArquivo, std::vector<Objeto>& itens, int& W){

    std::ifstream arquivo_leitura(nomeArquivo);

    int N;
    string linha;

    getline(arquivo_leitura, linha);
    stringstream linha_separada(linha);
    linha_separada >> N >> W;

    while (getline(arquivo_leitura, linha)){
        int peso, valor;
        stringstream linha_separada(linha);
        linha_separada >> peso >> valor;

        Objeto obj;
        obj.peso = peso;
        obj.valor = valor;

        itens.push_back(obj);
    }

    arquivo_leitura.close();
}

int melhorMochila (std::vector<Objeto>& itens, int W, int indice){
    
    if (indice == itens.size() || W == 0){
        return 0;
    }

    if (itens[indice].peso > W){
        return melhorMochila(itens, W, indice + 1);
    }

    int sem_incluir = melhorMochila(itens, W, indice + 1);

    int com_incluir = itens[indice].valor + melhorMochila(itens, W - itens[indice].peso, indice + 1);

    return max(sem_incluir, com_incluir);


}

int main() {
    
    auto start_global = std::chrono::high_resolution_clock::now(); 

    vector<Objeto> itens;
    int W;

    //lê arquivo e preenche vetor com cada valor e peso dos objetos no arquivo
    lerArquivo("in4.txt", itens, W);

    //auto start = std::chrono::high_resolution_clock::now(); 

    int valor_maximo = melhorMochila(itens, W, 0);

    //auto end = std::chrono::high_resolution_clock::now(); 

    auto end_global = std::chrono::high_resolution_clock::now(); 

    std::chrono::duration<double> duration = end_global - start_global;
    double exec_time = duration.count();

    cout << "Valor máximo que pode ser carregado na mochila: " << valor_maximo << endl;

    cout << "O tempo de execução da global foi: " << exec_time << " segundos" << endl;

    // Retorna 0, indicando que o programa terminou com sucesso.
    return 0;
}
