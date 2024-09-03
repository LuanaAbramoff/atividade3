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

pair<int, int> melhorMochila (std::vector<Objeto>& itens, std::vector<Objeto>& mochila, int& W){
    
    int peso_total = 0;
    int valor_total = 0;

    random_device rd;
    mt19937 gen(rd());

    uniform_real_distribution<>dis(0.0,1.0);

    for (int i = 0; i < itens.size(); i++){
        double prob = dis(gen);
        if (itens[i].peso + peso_total <= W){
            if(prob > 0.5){
                mochila.push_back(itens[i]);
                itens.pop_back();
                peso_total += itens[i].peso;
                valor_total += itens[i].valor;
            }
        }
    }

    return make_pair(peso_total, valor_total);

}


pair<int, int> buscaLocal (std::vector<Objeto>& itens, std::vector<Objeto>& mochila, int& W, int& peso_atual, int& valor_atual){
    
    int peso_total = 0;
    int valor_total = 0;


    for (int i = 0; i < itens.size(); i++){
        if (itens[i].peso + peso_total + peso_atual <= W){
            mochila.push_back(itens[i]);
            valor_total += itens[i].valor;
            peso_total += itens[i].peso;
        }
    }

    peso_total += peso_atual;
    valor_total += valor_atual;


    return make_pair(peso_total, valor_total);

}


int main() {
    
    auto start_global = std::chrono::high_resolution_clock::now(); 

    vector<Objeto> itens;
    vector<Objeto> mochila;
    int W;

    //lê arquivo e preenche vetor com cada valor e peso dos objetos no arquivo
    lerArquivo("Entrada_1.txt", itens, W);

    //auto start = std::chrono::high_resolution_clock::now(); 

    pair<int, int> resultado = melhorMochila(itens, mochila, W);
    int peso_maximo  = resultado.first;
    int valor_maximo = resultado.second; 

    pair<int, int> resultado_final = buscaLocal(itens, mochila, W, peso_maximo, valor_maximo);
    int peso_final = resultado_final.first;
    int valor_final = resultado_final.second;
    //auto end = std::chrono::high_resolution_clock::now(); 

    auto end_global = std::chrono::high_resolution_clock::now(); 

    std::chrono::duration<double> duration = end_global - start_global;
    double exec_time = duration.count();

    cout << "Peso ocupado: "  << peso_maximo << " Kg" << endl;
    cout << "Valor alcançado: " << valor_maximo << " dinheiros" << endl;

    cout << "Peso ocupado depois da busca local: "  << peso_final << " Kg" << endl;
    cout << "Valor alcançado depois da busca local: " << valor_final << " dinheiros" << endl;
    cout << "O tempo de execução da global foi: " << exec_time << " segundos" << endl;

    // Retorna 0, indicando que o programa terminou com sucesso.
    return 0;
}
