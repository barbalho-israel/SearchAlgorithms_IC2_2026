#include <iostream>
#include <string>
#include <cmath>
#include <chrono>
#include <algorithm>
#include <random>
#include <iomanip> 
#include <sstream> 

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

void insertionSortPorNomeS(Produtos* produtos, int qtdCadastrada, long long& comparacoes, long long& movimentacoes) {
    for (int i = 1; i < qtdCadastrada; i++) {
        Produtos chave = produtos[i];
        movimentacoes++;
        int j = i - 1;

        while (j >= 0 && produtos[j].nome > chave.nome) {
            comparacoes++;
            produtos[j + 1] = produtos[j];
            movimentacoes++;
            j--;
        }
        if (j >= 0) {
            comparacoes++;
        }
        produtos[j + 1] = chave;
        movimentacoes++;
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

int buscaBinariaS(Produtos* produtos, const string& chave, int esq, int dir, long long& comparacoes) {
    while (esq <= dir) {
        int meio = esq + (dir - esq) / 2;
        comparacoes++;
        if (produtos[meio].nome == chave) {
            return meio + 1;
        } else {
            comparacoes++;
            if (produtos[meio].nome < chave) {
                esq = meio + 1;
            } else {
                dir = meio - 1;
            }
        }
    }
    return esq;
}

void InsertionSortBinariaPorNomeS(Produtos* produtos, int qtdCadastrada, long long& comparacoes, long long& movimentacoes) {
    for (int i = 1; i < qtdCadastrada; i++) {
        Produtos chave = produtos[i];
        movimentacoes++;
        int posicao = buscaBinariaS(produtos, chave.nome, 0, i - 1, comparacoes);

        for (int j = i - 1; j >= posicao; --j) {
            movimentacoes++;
            produtos[j + 1] = produtos[j];
        }
        produtos[posicao] = chave;
        movimentacoes++;
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

int particaoArrayS(Produtos* produtos, int v0, int vN, long long& comparacoes, long long& movimentacoes) {
    string pivot = produtos[vN].nome;
    int i = v0 - 1;
    Produtos temp;

    for (int j = v0; j < vN; j++) {
        comparacoes++;
        if (pivot > produtos[j].nome) {
            i++;
            if (i != j) {
                temp = produtos[i];
                produtos[i] = produtos[j];
                produtos[j] = temp;
                movimentacoes += 3;
            }
        }
    }

    int prox_i = i + 1;
    if (prox_i != vN) {
        temp = produtos[prox_i];
        produtos[prox_i] = produtos[vN];
        produtos[vN] = temp;
        movimentacoes += 3;
    }

    return prox_i;
}

void quickSortNOMES(Produtos* produtos, int inicio, int fim, long long& comparacoes, long long& movimentacoes) {
    if (inicio < fim) {
        int pivot = particaoArrayS(produtos, inicio, fim, comparacoes, movimentacoes);
        quickSortNOMES(produtos, inicio, pivot - 1, comparacoes, movimentacoes);
        quickSortNOMES(produtos, pivot + 1, fim, comparacoes, movimentacoes);
    }
}


void bubbleSort(Produtos* produtos, int qtdCadastrada) {
    int n = qtdCadastrada;
    for (int i = 0; i < n - 1; i++) {
        bool trocou = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (produtos[j].nome > produtos[j + 1].nome) {
                Produtos temp = produtos[j];
                produtos[j] = produtos[j + 1];
                produtos[j + 1] = temp;
                trocou = true;
            }
        }
        if (!trocou) {
            break;
        }
    }
}

void bubbleSortS(Produtos* produtos, int qtdCadastrada, long long& comparacoes, long long& movimentacoes) {
    int n = qtdCadastrada;
    for (int i = 0; i < n - 1; i++) {
        bool trocou = false;
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (produtos[j].nome > produtos[j + 1].nome) {
                Produtos temp = produtos[j];
                produtos[j] = produtos[j + 1];
                produtos[j + 1] = temp;
                movimentacoes += 3;
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

void selectionSortNOMES(Produtos* produtos, int qtdCadastrada, long long& comparacoes, long long& movimentacoes) {
    for (int i = 0; i < qtdCadastrada - 1; i++) {
        int menIndice = i;
        for (int j = i + 1; j < qtdCadastrada; j++) {
            comparacoes++;
            if (produtos[j].nome < produtos[menIndice].nome) {
                menIndice = j;
            }
        }
        if (menIndice != i) {
            movimentacoes += 3;
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

void heapifyS(Produtos* produtos, int n, int i, long long& comparacoes, long long& movimentacoes) {
    int maior = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;

    if (esq < n) {
        comparacoes++;
        if (produtos[esq].nome > produtos[maior].nome) {
            maior = esq;
        }
    }

    if (dir < n) {
        comparacoes++;
        if (produtos[dir].nome > produtos[maior].nome) {
            maior = dir;
        }
    }

    if (maior != i) {
        movimentacoes += 3;
        Produtos temp = produtos[i];
        produtos[i] = produtos[maior];
        produtos[maior] = temp;
        heapifyS(produtos, n, maior, comparacoes, movimentacoes);
    }
}

void heapSortS(Produtos* produtos, int qtdCadastrada, long long& comparacoes, long long& movimentacoes) {
    int n = qtdCadastrada;

    for (int i = n / 2 - 1; i >= 0; --i) {
        heapifyS(produtos, n, i, comparacoes, movimentacoes);
    }
    for (int i = n - 1; i > 0; --i) {
        Produtos temp = produtos[0];
        produtos[0] = produtos[i];
        produtos[i] = temp;
        movimentacoes += 3;
        heapifyS(produtos, i, 0, comparacoes, movimentacoes);
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

void mergeS(Produtos* produtos, int esquerda, int meio, int direita, long long& comparacoes, long long& movimentacoes) {
    int n1 = meio - esquerda + 1;
    int n2 = direita - meio;

    Produtos* vetorEsquerda = new Produtos[n1];
    Produtos* vetorDireita = new Produtos[n2];

    for (int i = 0; i < n1; i++) {
        movimentacoes++;
        vetorEsquerda[i] = produtos[esquerda + i];
    }
    for (int j = 0; j < n2; j++) {
        movimentacoes++;
        vetorDireita[j] = produtos[meio + 1 + j];
    }

    int i = 0, j = 0, k = esquerda;

    while (i < n1 && j < n2) {
        comparacoes++;
        if (vetorEsquerda[i].nome <= vetorDireita[j].nome) {
            produtos[k] = vetorEsquerda[i];
            i++;
        } else {
            produtos[k] = vetorDireita[j];
            j++;
        }
        movimentacoes++;
        k++;
    }

    while (i < n1) {
        produtos[k] = vetorEsquerda[i];
        movimentacoes++;
        i++;
        k++;
    }

    while (j < n2) {
        produtos[k] = vetorDireita[j];
        movimentacoes++;
        j++;
        k++;
    }

    delete[] vetorEsquerda;
    delete[] vetorDireita;
}

void mergeSortPorNomeS(Produtos* produtos, int esquerda, int direita, long long& comparacoes, long long& movimentacoes) {
    if (esquerda < direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        mergeSortPorNomeS(produtos, esquerda, meio, comparacoes, movimentacoes);
        mergeSortPorNomeS(produtos, meio + 1, direita, comparacoes, movimentacoes);
        mergeS(produtos, esquerda, meio, direita, comparacoes, movimentacoes);
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

int opcoes(Produtos* produtos, int& qtdCadastrada, int opcao) {
    if (opcao == -1) {
        cin >> opcao;
    }

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

        case 2: {
            if (qtdCadastrada <= 0) break;
            Produtos* copia = new Produtos[qtdCadastrada];
            copy(produtos, produtos + qtdCadastrada, copia);
            long long comparacoes = 0, movimentacoes = 0, tempo = 0;

            auto inicio = chrono::high_resolution_clock::now();
            quickSortNOME(produtos, 0, qtdCadastrada - 1);
            auto fim = chrono::high_resolution_clock::now();

            tempo = chrono::duration_cast<chrono::nanoseconds>(fim - inicio).count();
            quickSortNOMES(copia, 0, qtdCadastrada - 1, comparacoes, movimentacoes);

            cout << "[QuickSort] Tempo: " << tempo << " ns | Comparacoes: " << comparacoes << " | Movimentacoes: " << movimentacoes << "\n";
            
            delete[] copia;
            break;
        }
        case 3: {
            if (qtdCadastrada <= 0) break;
            Produtos* copia = new Produtos[qtdCadastrada];
            copy(produtos, produtos + qtdCadastrada, copia);
            long long comparacoes = 0, movimentacoes = 0, tempo = 0;

            auto inicio = chrono::high_resolution_clock::now();
            insertionSortPorNome(produtos, qtdCadastrada);
            auto fim = chrono::high_resolution_clock::now();

            tempo = chrono::duration_cast<chrono::nanoseconds>(fim - inicio).count();
            insertionSortPorNomeS(copia, qtdCadastrada, comparacoes, movimentacoes);
            cout << "[InsertionSort] Tempo: " << tempo << " ns | Comparacoes: " << comparacoes << " | Movimentacoes: " << movimentacoes << "\n";
            delete[] copia;
            break;
        }
        case 4: {
            if (qtdCadastrada <= 0) break;
            Produtos* copia = new Produtos[qtdCadastrada];
            copy(produtos, produtos + qtdCadastrada, copia);
            long long comparacoes = 0, movimentacoes = 0, tempo = 0;

            auto inicio = chrono::high_resolution_clock::now();
            InsertionSortBinariaPorNome(produtos, qtdCadastrada);
            auto fim = chrono::high_resolution_clock::now();

            tempo = chrono::duration_cast<chrono::nanoseconds>(fim - inicio).count();
            InsertionSortBinariaPorNomeS(copia, qtdCadastrada, comparacoes, movimentacoes);
            cout << "[InsertionBinaria] Tempo: " << tempo << " ns | Comparacoes: " << comparacoes << " | Movimentacoes: " << movimentacoes << "\n";
            delete[] copia;
            break;
        }
        case 5: {
            if (qtdCadastrada <= 0) break;
            Produtos* copia = new Produtos[qtdCadastrada];
            copy(produtos, produtos + qtdCadastrada, copia);
            long long comparacoes = 0, movimentacoes = 0, tempo = 0;

            auto inicio = chrono::high_resolution_clock::now();
            bubbleSort(produtos, qtdCadastrada);
            auto fim = chrono::high_resolution_clock::now();

            tempo = chrono::duration_cast<chrono::nanoseconds>(fim - inicio).count();
            bubbleSortS(copia, qtdCadastrada, comparacoes, movimentacoes);
            cout << "[BubbleSort] Tempo: " << tempo << " ns | Comparacoes: " << comparacoes << " | Movimentacoes: " << movimentacoes << "\n";
            delete[] copia;
            break;
        }
        case 6: {
            if (qtdCadastrada <= 0) break;
            Produtos* copia = new Produtos[qtdCadastrada];
            copy(produtos, produtos + qtdCadastrada, copia);
            long long comparacoes = 0, movimentacoes = 0, tempo = 0;

            auto inicio = chrono::high_resolution_clock::now();
            selectionSortNOME(produtos, qtdCadastrada);
            auto fim = chrono::high_resolution_clock::now();

            tempo = chrono::duration_cast<chrono::nanoseconds>(fim - inicio).count();
            selectionSortNOMES(copia, qtdCadastrada, comparacoes, movimentacoes);
            cout << "[SelectionSort] Tempo: " << tempo << " ns | Comparacoes: " << comparacoes << " | Movimentacoes: " << movimentacoes << "\n";
            delete[] copia;
            break;
        }
        case 7: {
            if (qtdCadastrada <= 0) break;
            Produtos* copia = new Produtos[qtdCadastrada];
            copy(produtos, produtos + qtdCadastrada, copia);
            long long comparacoes = 0, movimentacoes = 0, tempo = 0;

            auto inicio = chrono::high_resolution_clock::now();
            heapSort(produtos, qtdCadastrada);
            auto fim = chrono::high_resolution_clock::now();

            tempo = chrono::duration_cast<chrono::nanoseconds>(fim - inicio).count();
            heapSortS(copia, qtdCadastrada, comparacoes, movimentacoes);
            cout << "[HeapSort] Tempo: " << tempo << " ns | Comparacoes: " << comparacoes << " | Movimentacoes: " << movimentacoes << "\n";
            delete[] copia;
            break;
        }
        case 8: {
            if (qtdCadastrada <= 0) break;
            Produtos* copia = new Produtos[qtdCadastrada];
            copy(produtos, produtos + qtdCadastrada, copia);
            long long comparacoes = 0, movimentacoes = 0, tempo = 0;

            auto inicio = chrono::high_resolution_clock::now();
            mergeSortPorNome(produtos, 0, qtdCadastrada - 1);
            auto fim = chrono::high_resolution_clock::now();

            tempo = chrono::duration_cast<chrono::nanoseconds>(fim - inicio).count();
            mergeSortPorNomeS(copia, 0, qtdCadastrada - 1, comparacoes, movimentacoes);
            cout << "[MergeSort] Tempo: " << tempo << " ns | Comparacoes: " << comparacoes << " | Movimentacoes: " << movimentacoes << "\n";
            delete[] copia;
            break;
        }
        case 9:
            if (qtdCadastrada == 0) {
                cout << "Nenhum produto cadastrado.\n";
            } else {
                exibirTodos(produtos, qtdCadastrada);
            }
            break;

        case 0:
            cout << "   Saindo...\n\n";
            break;

        default:
            cout << "Opcao invalida!\n";
            break;
    }

    return opcao;
}

string formatarNome(int numero, int largura = 6) { //até 999.999 itens
    ostringstream oss;
    oss << "Item_" << setw(largura) << setfill('0') << numero;
    return oss.str();
}

int main() {
    do {
        cout << R"(
        =============================
            MENU PRINCIPAL
        =============================
        
        1. Cadastrar produto
        2. Ordenar por quicksort
        3. Ordenar por insercao direta
        4. Ordenar por insercao binaria
        5. Ordenar por bubblesort
        6. Ordenar por SelectionSort
        7. Ordenar por Heapsort
        8. Ordenar por Mergesort
        9. Mostrar todos

        0. Sair
)";
    } while (opcoes(produtos, qtdCadastrada, -1) != 0);

    delete[] produtos;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribValor(1, 100);
    uniform_int_distribution<int> distribPorcentagem(0, 100);


    cout << "N inicial: " << endl;
    int inicial = 10000; //define tanto o valor inicial quanto os 5 saltos iguais que serão efetuados
    cin >> inicial;
    //benchmark 
    for(int i = inicial; i <= inicial*5; i+= inicial){
        cout << "n: " << i << endl;

        Produtos* crescente = new Produtos[i];
        Produtos* decrescente = new Produtos[i];
        Produtos* aleatorio = new Produtos[i];

        for (int k = 0; k < i; k++) {
        crescente[k].nome = formatarNome(k + 1);
        crescente[k].valor = distribValor(gen);
    int chance = distribPorcentagem(gen);
    if (chance > 50) {
        crescente[k].porcentagemPromocao = static_cast<double>(distribValor(gen)) / 100.0;
        crescente[k].valorPromocional = crescente[k].valor - (crescente[k].valor * crescente[k].porcentagemPromocao);
    } else {
        crescente[k].porcentagemPromocao = 0.0;
        crescente[k].valorPromocional = crescente[k].valor;
    }
    crescente[k].id = k + 1;
}

    for (int k = 0; k < i; k++) {
        decrescente[k].nome = formatarNome(i - k);
        decrescente[k].valor = distribValor(gen);
        int chance = distribPorcentagem(gen);
        if (chance > 50) {
            decrescente[k].porcentagemPromocao = static_cast<double>(distribValor(gen)) / 100.0;
            decrescente[k].valorPromocional = decrescente[k].valor - (decrescente[k].valor * decrescente[k].porcentagemPromocao);
        } else {
            decrescente[k].porcentagemPromocao = 0.0;
            decrescente[k].valorPromocional = decrescente[k].valor;
        }
        decrescente[k].id = i - k; 
    }

    for (int k = 0; k < i; k++) {
        aleatorio[k].nome = formatarNome(k + 1);
        aleatorio[k].valor = distribValor(gen);
        int chance = distribPorcentagem(gen);
        if (chance > 50) {
            aleatorio[k].porcentagemPromocao = static_cast<double>(distribValor(gen)) / 100.0;
            aleatorio[k].valorPromocional = aleatorio[k].valor - (aleatorio[k].valor * aleatorio[k].porcentagemPromocao);
        } else {
            aleatorio[k].porcentagemPromocao = 0.0;
            aleatorio[k].valorPromocional = aleatorio[k].valor;
        }
        aleatorio[k].id = k + 1;
    }

    // Embaralha todos os elementos aleatoriamente
    shuffle(aleatorio, aleatorio + i, gen);

        //percorre as opcoes passando uma cópia de cada tipo de array
        //cada j corresponde a um algoritmo de ordenação do switch da funcao opcoes

        for(int j = 2; j < 9; j++){
            Produtos* copiaCrescente = new Produtos[i];
            copy(crescente, crescente + i, copiaCrescente);

            Produtos* copiaDecrescente = new Produtos[i];
            copy(decrescente, decrescente + i, copiaDecrescente);

            Produtos* copiaAleatorio = new Produtos[i];
            copy(aleatorio, aleatorio + i, copiaAleatorio);

            cout << "Crescente: ";
            opcoes(copiaCrescente, i, j);
            
            cout << "Decrescente: ";
            opcoes(copiaDecrescente, i, j);
            
            cout << "Aleatório: ";
            opcoes(copiaAleatorio, i, j);

            delete[] copiaCrescente;
            delete[] copiaDecrescente;
            delete[] copiaAleatorio;
            cout << endl;
            }
        delete[] crescente;
        delete[] decrescente;
        delete[] aleatorio;
        cout << endl;
    }
    return 0;
}