#include <iostream>
#include <string>

using namespace std;

struct Produtos {
    string nome;
    string tipo;
    double valor;
    double valorPromocional;
    double porcentagemPromocao;
    int id;
};


void adicionar(Produtos* produtos, int& qtdAtual, int& idAtual) {
    cout << "Digite o nome: " << endl;
    cin.ignore();
    getline(cin, produtos[qtdAtual].nome);

    cout << "Digite o tipo: " << endl;
    getline(cin, produtos[qtdAtual].tipo);

    cout << "Digite o valor: " << endl;
    cin >> produtos[qtdAtual].valor;

    int promocao;
    cout << "Tem promocao? Digite 1 para sim e 0 para nao." << endl;
    cin >> promocao;

    if (promocao == 1) {
        produtos[qtdAtual].porcentagemPromocao = -1;
        while (produtos[qtdAtual].porcentagemPromocao <= 0 || produtos[qtdAtual].porcentagemPromocao >= 1) {
            cout << "Digite a porcentagem da promocao (entre 0 e 1, ex: 0.10): " << endl;
            cin >> produtos[qtdAtual].porcentagemPromocao;
        }
        produtos[qtdAtual].valorPromocional = produtos[qtdAtual].valor - (produtos[qtdAtual].valor * produtos[qtdAtual].porcentagemPromocao);
    } else {
        produtos[qtdAtual].valorPromocional = produtos[qtdAtual].valor;
        produtos[qtdAtual].porcentagemPromocao = 0;
    }

    produtos[qtdAtual].id = idAtual++;
    qtdAtual++
    cout << "Produto cadastrado com sucesso!\n";
}

//teste
void removerPorNome(Produtos* produtos, int& qtdAtual, const string& nomeParaRemover) {
    bool encontrado = false;

    for (int i = 0; i < qtdAtual; i++) {
        if (produtos[i].nome == nomeParaRemover) {
            encontrado = true;
            for (int j = i; j < qtdAtual - 1; j++) {
                produtos[j] = produtos[j + 1];
            }
            qtdAtual--;

        }
    }

    if (encontrado) {
        cout << "Produto removido com sucesso!"<<endl;
    } else {
        cout << "Produto nao encontrado."<<endl;
    }
}

void OrdenacaoPorTipo{
    
}

int main() {
    int opcao;
    int quantidade;
    int idGlobal = 1;
    int qtdCadastrada = 0;

    int capacidade = 100;
    Produtos* produtos = new Produtos[capacidade];

    do {
        cout << "\nEscolha uma opcao:\n1. Cadastrar produto\n2. Excluir produto por nome\n3.\n0. Sair\n";
        cin >> opcao;

        switch (opcao) {
            case 1:
                cout << "Quantos produtos deseja cadastrar? ";
                cin >> quantidade;
                for (int i = 0; i < quantidade; i++) {
                    cout << "\nCadastro do Produto " << (i + 1) << " ---\n";
                    adicionar(produtos, qtdCadastrada, idGlobal);
                }
                
                break;

            case 2: {
                string nomeExcluir;
                cout << "Digite o nome do produto que deseja excluir: ";
                cin.ignore();
                getline(cin, nomeExcluir);

                removerPorNome(produtos, qtdCadastrada, nomeExcluir);
                break;
            }
            case 3:

            case 0:
                cout << "Saindo...\n";
                break;
            default:
                cout << "Opcao invalida!\n";
                break;
        }
    } while (opcao != 0);

    delete[] produtos;

    return 0;
}