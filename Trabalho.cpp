#include <iostream>
#include <string>
#include <cmath>
#include <chrono>
#include <utility>
#include <algorithm> 
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

void insertionSortPorNome(Produtos* produtos, int qtdCadastrada) {
    for (int i = 1; i < qtdCadastrada; i++) {
        Produtos chave = produtos[i];
        int j = i - 1;

        while (j >= 0 && produtos[j].nome > chave.nome) {
            produtos[j + 1] = produtos[j];
            j--;
        }
        produtos[j + 1] = chave;
    }
}

int buscaBinaria(Produtos* produtos, const string& chave, int esq, int dir) {
    while (esq <= dir) {
        int meio = esq + (dir - esq) / 2;
        if (produtos[meio].nome == chave) {
            return meio + 1;
        } else if (produtos[meio].nome < chave) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }
    }
    return esq;
}

void InsertionSortBinariaPorNome(Produtos* produtos, int qtdCadastrada) {
    for (int i = 1; i < qtdCadastrada; i++) {
        Produtos chave = produtos[i];
        int posicao = buscaBinaria(produtos, chave.nome, 0, i - 1);

        for (int j = i - 1; j >= posicao; --j) {
            produtos[j + 1] = produtos[j];
        }
        produtos[posicao] = chave;
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
                swap(produtos[j], produtos[j + 1]);
                trocou = true;
            }
        }

        if (!trocou) {
            break;
        }
    }
}

void selectionSortNOME(Produtos* produtos, int qtdCadastrada) {
    for (int i = 0; i < qtdCadastrada - 1; i++) {
        int menIndice = i;
        for (int j = i + 1; j < qtdCadastrada; j++) {
            if (produtos[j].nome < produtos[menIndice].nome) {
                menIndice = j;
            }
        }
        if (menIndice != i) {
            Produtos temp = produtos[i];
            produtos[i] = produtos[menIndice];
            produtos[menIndice] = temp;
        }
    }
}

void heapify(Produtos* produtos, int n, int i) {
    int maior = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;

    if (esq < n && produtos[esq].nome > produtos[maior].nome) {
        maior = esq;
    }

    if (dir < n && produtos[dir].nome > produtos[maior].nome) {
        maior = dir;
    }

    if (maior != i) {
        Produtos temp = produtos[i];
        produtos[i] = produtos[maior];
        produtos[maior] = temp;
        heapify(produtos, n, maior);
    }
}

void heapSort(Produtos* produtos, int qtdCadastrada) {
    int n = qtdCadastrada;

    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(produtos, n, i);
    }
    for (int i = n - 1; i > 0; --i) {
        Produtos temp = produtos[0];
        produtos[0] = produtos[i];
        produtos[i] = temp;
        heapify(produtos, i, 0);
    }
}

void merge(Produtos* produtos, int esquerda, int meio, int direita) {
    int n1 = meio - esquerda + 1;
    int n2 = direita - meio;

    Produtos* vetorEsquerda = new Produtos[n1];
    Produtos* vetorDireita = new Produtos[n2];

    for (int i = 0; i < n1; i++) {
        vetorEsquerda[i] = produtos[esquerda + i];
    }
    for (int j = 0; j < n2; j++) {
        vetorDireita[j] = produtos[meio + 1 + j];
    }

    int i = 0, j = 0, k = esquerda;

    while (i < n1 && j < n2) {
        if (vetorEsquerda[i].nome <= vetorDireita[j].nome) {
            produtos[k] = vetorEsquerda[i];
            i++;
        } else {
            produtos[k] = vetorDireita[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        produtos[k] = vetorEsquerda[i];
        i++;
        k++;
    }

    while (j < n2) {
        produtos[k] = vetorDireita[j];
        j++;
        k++;
    }

    delete[] vetorEsquerda;
    delete[] vetorDireita;
}

void mergeSortPorNome(Produtos* produtos, int esquerda, int direita) {
    if (esquerda < direita) {
        int meio = esquerda + (direita - esquerda) / 2;

        mergeSortPorNome(produtos, esquerda, meio);
        mergeSortPorNome(produtos, meio + 1, direita);
        merge(produtos, esquerda, meio, direita);
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

int opcoes(Produtos* produtos, int qtdCadastrada){
    int continuar = 0;
    int opcao;
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
                break;

            case 2:
                quickSortNOME(produtos, 0, qtdCadastrada - 1);
                break;

            case 3:
                insertionSortPorNome(produtos, qtdCadastrada);
                break;

            case 4:
                InsertionSortBinariaPorNome(produtos, qtdCadastrada);
                break;

            case 5:
                bubbleSort(produtos, qtdCadastrada);
                break;

            case 6:
                selectionSortNOME(produtos, qtdCadastrada);
                break;

            case 7:
                heapSort(produtos, qtdCadastrada);
                break;

            case 8:
                mergeSortPorNome(produtos, 0, qtdCadastrada - 1);
                break;

            case 9:
                if (qtdCadastrada == 0) {
                    cout << "Nenhum produto cadastrado.\n";
                } else {
                    exibirTodos(produtos, qtdCadastrada);
                }
                break;

            case 0:
                cout << "   Saindo...\n";
                continuar = 1;
                break;

            default:
                cout << "Opcao invalida!\n";
                break;
        }

    return continuar;
}

int main() {
    do {
        cout << R"(
        =============================
            MENU PRINCIPAL
        =============================
        
        1. Cadastrar produto
        2. Ordenar por quicksort
        3. Ordenar por inserção direta
        4. Ordenar por inserção binária
        5. Ordenar por bubblesort
        6. Ordenar por SelectionSort
        7. Ordenar por Heapsort
        8. Ordenar por Mergesort
        9. Mostrar todos

        0. Sair
)";
        
    } while (opcoes(produtos, qtdCadastrada) == 0);

    delete[] produtos;

    //benchmark
    int inicial = 10000; 
    for(int i = inicial; i <= inicial*5; i+= inicial){
        //cout << i << ": "<< endl;

        Produtos* crescente = new Produtos[i];


        Produtos* copiaCrescente = new Produtos[i];
        copy(crescente, copiaCrescente + i, copiaCrescente);

        Produtos* decrecente = new Produtos[i];
        Produtos* aleatorio = new Produtos[i];

        
        delete[] copiaCrescente;

        //gera os arrays e cópias

        for(int i = 1; i < 9; i++){
                opcoes(crescente,i);
            }
        delete[] crescente;
        delete[] decrecente;
        delete[] aleatorio;
    }
    
    return 0;
}