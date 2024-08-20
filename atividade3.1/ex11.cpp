#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <map>


int main(){

    using namespace std;
    string n_arquivo_entrada = "entrada.txt";
    string n_arquivo_saida = "saida.txt";

    fstream Arquivo_Entrada(n_arquivo_entrada);

    string linha;

    int total_linhas = 0;
    int total_palavras = 0;
    map<string, int> contagem;

    while(getline(Arquivo_Entrada, linha)){

        total_linhas++;
        stringstream linha_separada (linha);
        string palavra;

        while (linha_separada >> palavra){
            total_palavras++;
            contagem[palavra]++;
        }
    }

    Arquivo_Entrada.close();

    int palavras_linha = total_palavras/total_linhas;
    
    //busca pela palavra mais frequente
    string palavra_mais_frequente;
    int maior_frequencia = 0;

    for (const auto& par : contagem){
        if (par.second > maior_frequencia){
            maior_frequencia = par.second;
            palavra_mais_frequente = par.first;
        }
    }

    //escrita de estatísticas no arquivo

    ofstream Arquivo_Saida(n_arquivo_saida);

    Arquivo_Saida << "Número total de palavras é: " << total_palavras << endl;
    Arquivo_Saida << "Número total de linhas é: "   << total_linhas << endl;
    Arquivo_Saida << "Número médio de palavras por linha é: " << palavras_linha << endl;
    Arquivo_Saida << "A palavra mais frequente é: " << palavra_mais_frequente << endl;

    Arquivo_Saida.close();

    return 0;


}