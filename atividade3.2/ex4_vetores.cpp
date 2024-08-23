#include <iostream>
#include <vector>

class Vector {
public:
    Vector(int tamanho)
    : tam(tamanho), capacidade(tamanho), dados(new int[tamanho]) {}

    ~Vector() {
        delete[] dados; // Libera a memória alocada
    }
    
    void inicializa(int valor){
        for (int i = 0; i < tam; ++i){
            dados[i] = valor;
        }
    }

    inline int get(int index) const{
        if (index >= 0 && index < tam){
            return dados[index];
        }
        else{
            std::cerr << "Índice fora do intervalo!" << std::endl;
            return -1; // Valor de erro
        }
    }

    inline void set(int index, int valor){
        if (index >= 0 && index < tam){
            dados[index] = valor;
        }
        else{
            std::cerr << "Índice fora do intervalo!" << std::endl;
        }
    }

    void inserir (int index, int valor){
        if (index >=0 && index <= tam){
            if (tam >= capacidade){
                redimensiona (2 * capacidade);
            }
            
            for (int i = tam; i > index; --i){
                dados[i] = dados [i-1];
            }
            
            dados[index] = valor;
            tam++;
        }
        else{
            std::cerr << "Índice fora do intervalo!" << std::endl;
        }
    }

    void remover (int index){
        if (index >= 0 && index < tam){
            for (int i = index; i < tam - 1; ++i){
                dados[i] = dados[i+1];
            }
            tam--;
        }
        else{
            std::cerr << "Índice fora do intervalo!" << std::endl;
        }
    }

    void imprime() const{

        for (int i = 0; i < tam; i++){
            std::cout << dados[i] << " ";
        }
        std::cout << std::endl;
    }

    inline int tamanho() const{
        return tam;
    } 

private:
    int* dados;
    int tam;
    int capacidade;
    void redimensiona(int novaCapacidade){
        int* novosDados = new int[novaCapacidade];
        for(int i = 0; i < tam; i++){
            novosDados[i] = dados[i];
        }
        delete[] dados;
        dados = novosDados;
        capacidade = novaCapacidade;
    }
};

// Implementação das funções...

int main() {
    Vector vec(5);
    vec.inicializa(0);
    vec.imprime();

    vec.set(2, 1);
    std::cout << "Modificando o elemento de índice 2 para 1 ";
    vec.imprime();

    vec.inserir(2, 18);
    std::cout << "Inserindo o elemento 18 no índice 2 ";
    vec.imprime();

    vec.remover(3);
    std::cout << "Removendo o quarto elemento ";
    vec.imprime();

    std::cout << "O tamanho do vetor no final é:  " << vec.tamanho() << std::endl;



    return 0;
}