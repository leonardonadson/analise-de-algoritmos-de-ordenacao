#include <algoritmos.h>
#include <utility>

// Bubble Sort 
void bubbleSort(std::vector<int>& vetor, Metricas& metricas) {
    int n = vetor.size();
    // A cada iteração do loop externo, o maior elemento da porção não ordenada flutua para sua posição correta no final
    for (int i = 0; i < n - 1; ++i) {
        // O loop interno compara pares adjacentes para mover o maior elemento local para a direita
        for (int j = 0; j < n - i - 1; ++j) {
            metricas.comparacoes++;
            if (vetor[j] > vetor[j + 1]) {
                std::swap(vetor[j], vetor[j + 1]);
                metricas.trocas++;
            }
        }
    }
}

// Selection Sort 
void selectionSort(std::vector<int>& vetor, Metricas& metricas) {
    int n = vetor.size();
    // O loop externo itera para construir o vetor ordenado da esquerda para a direita, um elemento por vez
    for (int i = 0; i < n - 1; ++i) {
        int indiceMenor = i;
        // O loop interno busca pelo menor elemento em toda a parte ainda não ordenada do vetor
        for (int j = i + 1; j < n; ++j) {
            metricas.comparacoes++;
            if (vetor[j] < vetor[indiceMenor]) {
                indiceMenor = j;
            }
        }
        // Coloca o menor elemento encontrado na posição correta da parte já ordenada
        if (indiceMenor != i) {
            std::swap(vetor[i], vetor[indiceMenor]);
            metricas.trocas++;
        }
    }
}

// Insertion Sort 
void insertionSort(std::vector<int>& vetor, Metricas& metricas) {
    int n = vetor.size();
    // Inicia do segundo elemento, assumindo que o primeiro já está ordenado
    for (int i = 1; i < n; ++i) {
        int chave = vetor[i];
        int j = i - 1;
        // Move os elementos da parte ordenada que são maiores que a chave para a direita, abrindo espaço
        while (j >= 0 && (metricas.comparacoes++, vetor[j] > chave)) {
            vetor[j + 1] = vetor[j];
            metricas.trocas++; // Considera um deslocamento como uma forma de troca
            j--;
        }
        // Insere a chave na sua posição correta na parte ordenada
        vetor[j + 1] = chave;
        if (j + 1 != i) {
             metricas.trocas++;
        }
    }
}

// Merge Sort 
// Função para combinar (merge) dois subvetores ordenados em um unico vetor ordenado
void merge(std::vector<int>& vetor, int inicio, int meio, int fim, Metricas& metricas) {
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    // Vetores temporários para armazenar as duas metades
    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = vetor[inicio + i];
    for (int j = 0; j < n2; j++) R[j] = vetor[meio + 1 + j];

    int i = 0, j = 0, k = inicio;
    // Intercala os elementos dos vetores temporários de volta no vetor original, em ordem
    while (i < n1 && j < n2) {
        metricas.comparacoes++;
        if (L[i] <= R[j]) {
            vetor[k] = L[i];
            i++;
        } else {
            vetor[k] = R[j];
            j++;
        }
        metricas.trocas++; // Cada escrita no array original é uma movimentação
        k++;
    }

    // Copia os elementos restantes de L ou R, se houver
    while (i < n1) {
        vetor[k] = L[i];
        i++; k++;
        metricas.trocas++;
    }
    while (j < n2) {
        vetor[k] = R[j];
        j++; k++;
        metricas.trocas++;
    }
}

// Adota a estratégia dividir para conquistar, quebrando o problema em subproblemas menores
void mergeSort_recursivo(std::vector<int>& vetor, int inicio, int fim, Metricas& metricas) {
    if (inicio < fim) {
        // Encontra o meio para evitar overflow e dividir o vetor
        int meio = inicio + (fim - inicio) / 2;
        mergeSort_recursivo(vetor, inicio, meio, metricas);
        mergeSort_recursivo(vetor, meio + 1, fim, metricas);
        // Após as chamadas recursivas retornarem, os sub-vetores estarão ordenados e prontos para o merge
        merge(vetor, inicio, meio, fim, metricas);
    }
}

void mergeSort(std::vector<int>& vetor, Metricas& metricas) {
    if (vetor.empty()) return;
    mergeSort_recursivo(vetor, 0, vetor.size() - 1, metricas);
}

// Quick Sort 
// Particiona o vetor em dois, colocando o pivô em sua posição final correta
int partition(std::vector<int>& vetor, int inicio, int fim, Metricas& metricas) {
    // A "mediana de três" ajuda a escolher um pivô melhor, evitando piores casos (vetor já ordenado)
    int meio = inicio + (fim - inicio) / 2;
    if (vetor[meio] < vetor[inicio]) { std::swap(vetor[meio], vetor[inicio]); metricas.trocas++; }
    if (vetor[fim] < vetor[inicio]) { std::swap(vetor[fim], vetor[inicio]); metricas.trocas++; }
    if (vetor[meio] < vetor[fim]) { std::swap(vetor[meio], vetor[fim]); metricas.trocas++; }
    metricas.comparacoes += 3;

    int pivo = vetor[fim]; // O pivô agora está no final
    int i = inicio - 1; // i é o índice do último elemento menor que o pivô

    // Percorre o vetor para mover todos os elementos menores que o pivô para a esquerda de i
    for (int j = inicio; j < fim; ++j) {
        metricas.comparacoes++;
        if (vetor[j] < pivo) {
            i++;
            std::swap(vetor[i], vetor[j]);
            metricas.trocas++;
        }
    }
    // Posiciona o pivô logo após o último elemento menor que ele
    std::swap(vetor[i + 1], vetor[fim]);
    metricas.trocas++;
    return i + 1; // Retorna a posição final do pivô
}

void quickSort_recursivo(std::vector<int>& vetor, int inicio, int fim, Metricas& metricas) {
    if (inicio < fim) {
        // pi é o índice de partição, onde o pivô já está no lugar certo
        int pi = partition(vetor, inicio, fim, metricas);
        // Ordena recursivamente os elementos antes e depois da partição
        quickSort_recursivo(vetor, inicio, pi - 1, metricas);
        quickSort_recursivo(vetor, pi + 1, fim, metricas);
    }
}

void quickSort(std::vector<int>& vetor, Metricas& metricas) {
    if (vetor.empty()) return;
    quickSort_recursivo(vetor, 0, vetor.size() - 1, metricas);
}