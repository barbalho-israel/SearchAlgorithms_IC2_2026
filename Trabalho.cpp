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

    int quantidade;
    int idGlobal = 1;
    int qtdCadastrada = 0;
    int capacidade = 5;
    Produtos* produtos = new Produtos[capacidade];

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

void insertionSortPorNome (Produtos* produtos, int qtdCadastrada) {
    
    for (int i = 1; i <= qtdCadastrada; i++) {
        int n =  produtos[i].nome;
        int j = i - 1;


        while (j >= 0 && produtos[j].nome) {
            produtos[j + 1].nome = produtos[j].nome;
            j++;
        }
        produtos[j+1].nome = n;
    }
}

int buscaBinaria(Produtos* produtos, int n, int esq, int dir) {
    while (esq <= dir) {
        int meio = esq + (dir - esq) / 2;
        if (produtos[meio].nome == n) {
            return meio + 1;
        } else if (produtos[meio].nome < n) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }
    }
    return esq;
}

void InsertionSortBinariaPorNome(Produtos* produtos, int qtdCadastrada) {
    
    for (int i = 1; i < qtdCadastrada; i++) {
        int n = produtos[i].nome;
        int posicao = buscaBinaria(produtos.nome, n, 0, i - 1);

        for (int j = i - 1; j >= posicao; --j) {
            produtos[j + 1].nome = produtos[j].nome;
        }
        arr[posicao] = n;
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
void bubbleSort(Produtos* produtos, int qtdCadastrada) {
    int n = qtdCadastrada;
    for (int i = 0; i < n - 1; i++) {
        bool trocou = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (produtos[j].nome > produtos[j + 1].nome) {
                swap(produtos[j].nome, produtos[j + 1].nome);
            }
        }
   
        if (!trocou) {
            break;
        } 
    }
}

void exibirTodos(Produtos* produtos, int qtdCadastrada) {
    for (int i = 0; i < qtdCadastrada; i++) {
        cout << "\nNome: " << produtos[i].nome << endl;
        cout << "Tipo: " << produtos[i].tipo << endl;
        cout << "Valor: " << produtos[i].valor << endl;
        cout << "Valor promocional: " << produtos[i].valorPromocional << endl;
    }
}



void menu(){
cout << R"(
        =============================
            MENU PRINCIPAL
        =============================
        
        1. Cadastrar produto
        2. Ordenar por quicksort
        3. Ordenar por inserção direta
        4. Ordenar por inserção binária
        5. Ordenar por bubblesort
        6. Ordenar por selecao
        7. Ordenar por Heapsort
        8. Ordenar por Mergesort
        9. Mostrar todos

        0. Sair")";
}

int opcoes(){
    int opcao;
    cout <<"    : ";
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
                quickSortNOME(produtos, 0, qtdCadastrada - 1);
                break;
            }
            case 3: {
                InsertionSortPorNome(produtos, qtdCadastrada - 1);
                break;
            }
            case 4: {
                InsertionSortBinaria(produtos, qtdCadastrada - 1);
                break;
                
            }
            case 5: {
                bubbleSort(produtos, qtdCadastrada - 1);
                break;
            }
            
            case 9: {
                if (qtdCadastrada == 0) {
                    cout << "Nenhum produto cadastrado.\n";
                } else {
                    exibirTodos(produtos, qtdCadastrada);
                }
                break;
            }
            case 0:{
                cout << "   Saindo...\n";
                return -1;
                break;
            }
            default:
                cout << "Opcao invalida!\n";
                break;
        }
    return 0;
}

int main() {
   
    do {menu();} while (opcoes() == 0);

    delete[] produtos;

    return 0;
}