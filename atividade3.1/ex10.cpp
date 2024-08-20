#include <iostream>
#include <vector>
#include <string>

struct Item {
    std::string nome;
    int quantidade;
};

void adicionarItem(std::vector<Item>& estoque) {
    Item novoItem;
    std::cout << "Digite o nome do item: ";
    std::cin >> novoItem.nome;
    std::cout << "Digite a quantidade: ";
    std::cin >> novoItem.quantidade;

    // Verifica se o item já existe no estoque
    for (auto& item : estoque) {
        if (item.nome == novoItem.nome) {
            item.quantidade += novoItem.quantidade;
            std::cout << "Quantidade atualizada no estoque.\n";
            return;
        }
    }

    estoque.push_back(novoItem);
    std::cout << "Item adicionado ao estoque.\n";
}

void removerItem(std::vector<Item>& estoque) {
    std::string nome;
    int quantidade;
    std::cout << "Digite o nome do item a ser removido: ";
    std::cin >> nome;
    std::cout << "Digite a quantidade a ser removida: ";
    std::cin >> quantidade;

    for (auto& item : estoque) {
        if (item.nome == nome) {
            if (item.quantidade >= quantidade) {
                item.quantidade -= quantidade;
                std::cout << "Quantidade removida do estoque.\n";
                if (item.quantidade == 0) {
                    estoque.erase(std::remove(estoque.begin(), estoque.end(), item), estoque.end());
                    std::cout << "Item removido completamente do estoque.\n";
                }
            } else {
                std::cout << "Quantidade insuficiente em estoque.\n";
            }
            return;
        }
    }

    std::cout << "Item não encontrado no estoque.\n";
}

void visualizarEstoque(const std::vector<Item>& estoque) {
    std::cout << "\nEstoque atual:\n";
    for (const auto& item : estoque) {
        std::cout << "Item: " << item.nome << " | Quantidade: " << item.quantidade << "\n";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<Item> estoque;
    int opcao;

    do {
        std::cout << "Sistema de Controle de Estoque\n";
        std::cout << "1. Adicionar Item\n";
        std::cout << "2. Remover Item\n";
        std::cout << "3. Visualizar Estoque\n";
        std::cout << "4. Sair\n";
        std::cout << "Escolha uma opcao: ";
        std::cin >> opcao;

        switch (opcao) {
            case 1:
                adicionarItem(estoque);
                break;
            case 2:
                removerItem(estoque);
                break;
            case 3:
                visualizarEstoque(estoque);
                break;
            case 4:
                std::cout << "Saindo do programa.\n";
                break;
            default:
                std::cout << "Opcao invalida! Tente novamente.\n";
                break;
        }
    } while (opcao != 4);

    return 0;
}
