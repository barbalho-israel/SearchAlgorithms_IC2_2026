#include <iostream>
#include <string>
#include <cmath>
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
    qtdAtual++;

    cout << "Produto cadastrado com sucesso!\n";
}

void removerPorNome(Produtos* produtos, int& qtdAtual, const string& nomeParaRemover) {
    bool encontrado = false;

    for (int i = 0; i < qtdAtual; i++) {
        if (produtos[i].nome == nomeParaRemover) {
            encontrado = true;
            for (int j = i; j < qtdAtual - 1; j++) {
                produtos[j] = produtos[j + 1];
            }
            qtdAtual--;
            i--;
        }
    }

    if (encontrado) {
        cout << "Produto removido com sucesso!" << endl;
    } else {
        cout << "Produto nao encontrado." << endl;
    }
}

int particaoArray(Produtos* produtos, int v0, int vN) {
    string pivot = produtos[vN].nome;
    int i = v0 - 1;
    Produtos temp;

    for (int j = v0; j < vN; j++) {
        if (pivot > produtos[j].nome) {
            i++;
            if (i != j) {
                temp = produtos[i];
                produtos[i] = produtos[j];
                produtos[j] = temp;
            }
        }
    }

    int prox_i = i + 1;
    if (prox_i != vN) {
        temp = produtos[prox_i];
        produtos[prox_i] = produtos[vN];
        produtos[vN] = temp;
    }

    return prox_i;
}

void quickSortNOME(Produtos* produtos, int inicio, int fim) {
    if (inicio < fim) {
        int pivot = particaoArray(produtos, inicio, fim);
        quickSortNOME(produtos, inicio, pivot - 1);
        quickSortNOME(produtos, pivot + 1, fim);
    }
}
void buscaBinariaPorNome(Produtos* produtos, string nomeBuscado, int inicio, int fim) {
    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;

        if (produtos[meio].nome == nomeBuscado) {
            cout << "Produto encontrado: " << endl;
            cout << "Nome: " << produtos[meio].nome << endl;
            cout << "Tipo: " << produtos[meio].tipo << endl;
            cout << "Valor: " << produtos[meio].valor << endl;
            cout << "Valor promocional: " << produtos[meio].valorPromocional << endl;
            return;
        }

        if (produtos[meio].nome < nomeBuscado) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    cout << "Produto nao encontrado." << endl;
}
void exibirTodos(Produtos* produtos, int qtdCadastrada) {
    for (int i = 0; i < qtdCadastrada; i++) {
        cout << "\nNome: " << produtos[i].nome << endl;
        cout << "Tipo: " << produtos[i].tipo << endl;
        cout << "Valor: " << produtos[i].valor << endl;
        cout << "Valor promocional: " << produtos[i].valorPromocional << endl;
    }
}

void exibirTodosTipo(Produtos* produtos, int qtdCadastrada, string tipo) {
    int qtdExibida = 0;

    for (int i = 0; i < qtdCadastrada; i++) {
        if (tipo == produtos[i].tipo) {
            cout << "\nNome: " << produtos[i].nome << endl;
            cout << "Tipo: " << produtos[i].tipo << endl;
            cout << "Valor: " << produtos[i].valor << endl;
            cout << "Valor promocional: " << produtos[i].valorPromocional << endl;
            qtdExibida++;
        }
    }

    if (qtdExibida == 0) {
        cout << "Nenhum produto desse tipo foi encontrado." << endl;
    }
}

int main() {
    int opcao;
    int quantidade;
    int idGlobal = 1;
    int qtdCadastrada = 0;
    int capacidade;
    cout << "Digite a capacidade do seu estoque\n";
    cin >> capacidade;
    
    Produtos* produtos = new Produtos[capacidade];

    do {
        cout << "\nEscolha uma opcao:\n 1. Cadastrar produto\n 2. Excluir produto por nome\n 3. Busca através do nome\n 4. Exibir todos os produtos \n 5. Exibir produtos de apenas um tipo\n 0. Sair\n";
        cin >> opcao;

        switch (opcao) {
            case 1:
                cout << "Quantos produtos deseja cadastrar? ";
                cin >> quantidade;
                
                if (qtdCadastrada + quantidade > capacidade) {
                    cout << "Erro: Capacidade maxima do estoque excedida!\n";
                    break;
                }

                for (int i = 0; i < quantidade; i++) {
                    cout << "\nCadastro do Produto " << (i + 1) << "\n";
                    adicionar(produtos, qtdCadastrada, idGlobal);
                }
                quickSortNOME(produtos, 0, qtdCadastrada - 1);
                break;

            case 2: {
                string nomeExcluir;
                cout << "Digite o nome do produto que deseja excluir: ";
                cin.ignore();
                getline(cin, nomeExcluir);

                removerPorNome(produtos, qtdCadastrada, nomeExcluir);
                break;
            }
            case 3: {
                if (qtdCadastrada == 0) {
                    cout << "Nenhum produto cadastrado.\n";
                    break;
                }
                string nomePProcurar;
                cout << "Digite o nome do produto que deseja buscar: ";
                cin.ignore();
                getline(cin, nomePProcurar);
                buscaBinariaPorNome(produtos, nomePProcurar, 0, qtdCadastrada - 1);
                break;
            }
            case 4: {
                if (qtdCadastrada == 0) {
                    cout << "Nenhum produto cadastrado.\n";
                } else {
                    exibirTodos(produtos, qtdCadastrada);
                }
                break;
            }
            case 5: {
                if (qtdCadastrada == 0) {
                    cout << "Nenhum produto cadastrado.\n";
                    break;
                }
                string tipoPProcurar;
                cout << "Digite o tipo: ";
                cin.ignore();
                getline(cin, tipoPProcurar);
                exibirTodosTipo(produtos, qtdCadastrada, tipoPProcurar);
                break;
            }
            case 0:{
                cout << "Saindo...\n";
                break;
            }
            default:
                cout << "Opcao invalida!\n";
                break;
        }
    } while (opcao != 0);

    delete[] produtos;

    return 0;
}