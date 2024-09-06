#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <chrono>     // Inclui a biblioteca para medição de tempo.
#include <random>
#include <algorithm>


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

pair<int, int> calcularMochila (std::vector<Objeto>& itens, std::vector<int>& vetor_binario, int& W){
    
    int peso_total = 0;
    int valor_total = 0;


    for (int i = 0; i < itens.size(); i++){
        if (itens[i].peso + peso_total <= W){
            if (vetor_binario[i] == 1){
                peso_total  += itens[i].peso;
                valor_total += itens[i].valor;
            }
        }
    }

    return make_pair(peso_total, valor_total);

}

vector<int> gerarVizinho (const vector<int>& vetor_binario, int posicao){
    vector<int> vizinho = vetor_binario;
    vizinho[posicao] = 1 - vizinho[posicao];
    return vizinho;
}

pair<int, int> hillClimbing (std::vector<Objeto>& itens, std::vector<int>& vetor_binario, int& W){

    vector<int> vetor_binario_atual = vetor_binario;
    pair<int, int> resultado_atual = calcularMochila(itens, vetor_binario_atual, W);

    bool melhora = true; 

    while (melhora){

        melhora = false;

        for (int i = 0; i < vetor_binario_atual.size(); i++){
            vector<int> vetor_vizinho = gerarVizinho(vetor_binario_atual, i);
            pair<int, int> resultado_vizinho = calcularMochila(itens, vetor_vizinho, W);

            if(resultado_vizinho.second > resultado_atual.second && resultado_vizinho.first <= W){
                vetor_binario_atual = vetor_vizinho;
                resultado_atual = resultado_vizinho;
                melhora = true;
            }
        }
    }

    return resultado_atual;

}


int main () {

    auto start_global = std::chrono::high_resolution_clock::now(); 

    vector<Objeto> itens;
    int W;

    //lê arquivo e preenche vetor com cada valor e peso dos objetos no arquivo
    lerArquivo("Entrada_3.txt", itens, W);

    int melhor_valor = 0;
    pair<int , int> melhor_resultado = {0,0};

    for (int i = 0; i < 10; i++){

        vector<int> vetor_binario(itens.size(), 0);
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<>dis(0, 1);

        for (int j = 0; j < itens.size(); j++){
            vetor_binario[j] = dis(gen);
        }

        pair <int, int> resultado = hillClimbing(itens, vetor_binario, W);

        if(resultado.second > melhor_valor){
            melhor_valor = resultado.second;
            melhor_resultado = resultado;
        }
    }

    auto end_global = std::chrono::high_resolution_clock::now(); 

    std::chrono::duration<double> duration = end_global - start_global;
    double exec_time = duration.count();

    cout << "Melhor valor obtido: " << melhor_valor << " dinheiros" << endl;
    cout << "Peso correspondente " << melhor_resultado.first << " kg" << endl;
    cout << "O tempo de execução foi: " << exec_time << " segundos" << endl;


    return 0;
}