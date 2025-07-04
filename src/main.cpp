#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include <functional>
#include "metricas.h"
#include "algoritmos.h"

// Função para gerar um vetor com números aleatórios
// Usado para simular o caso médio de performance de um algoritmo.
std::vector<int> gerarVetorAleatorio(int tamanho) {
    std::vector<int> vetor(tamanho);
    // Usa o hardware para gerar uma semente aleatória para o gerador de números
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, tamanho * 10);
    for (int i = 0; i < tamanho; ++i) {
        vetor[i] = distrib(gen);
    }
    return vetor;
}

// Função para gerar um vetor ordenado
// Usado para testar o melhor caso de alguns algoritmos
std::vector<int> gerarVetorOrdenado(int tamanho) {
    std::vector<int> vetor(tamanho);
    for (int i = 0; i < tamanho; ++i) {
        vetor[i] = i + 1;
    }
    return vetor;
}

// Função para gerar um vetor inversamente ordenado
// Geralmente representa o pior cenário de performance para a maioria dos algoritmos de ordenação
std::vector<int> gerarVetorInversamenteOrdenado(int tamanho) {
    std::vector<int> vetor(tamanho);
    for (int i = 0; i < tamanho; ++i) {
        vetor[i] = tamanho - i;
    }
    return vetor;
}

int main() {
    // Define os tamanhos dos vetores a serem testados
    std::vector<int> tamanhos = {100, 1000, 5000};

    // Define os tipos de dados a serem testados
    struct TipoDeDados {
        std::string nome;
        // Permite armazenar e chamar as diferentes funções geradoras de vetores 
        std::function<std::vector<int>(int)> gerador;
    };
    // Agrupa os diferentes cenários de teste para facilitar a iteração
    std::vector<TipoDeDados> tipos_de_dados = {
        {"Aleatorio", gerarVetorAleatorio},
        {"Ordenado", gerarVetorOrdenado},
        {"InversamenteOrdenado", gerarVetorInversamenteOrdenado}
    };

    // Define os algoritmos a serem testados
    struct AlgoritmoTeste {
        std::string nome;
        // Armazena um ponteiro para a função de ordenação, permitindo que os algoritmos sejam tratados como dados
        std::function<void(std::vector<int>&, Metricas&)> funcao;
    };
    // Agrupa todos os algoritmos para que possam ser executados em um loop
    std::vector<AlgoritmoTeste> algoritmos = {
        {"BubbleSort", bubbleSort},
        {"SelectionSort", selectionSort},
        {"InsertionSort", insertionSort},
        {"MergeSort", mergeSort},
        {"QuickSort", quickSort}
    };

    // Loop principal para executar todos os testes
    // A estrutura de loops aninhados garante que cada algoritmo seja testado com cada tipo e tamanho de vetor
    for (int tamanho : tamanhos) {
        for (const auto& tipo : tipos_de_dados) {
            std::cout << "\n===== TESTES PARA VETOR " << tipo.nome
                      << " (N=" << tamanho << ") =====\n";

            // Gera o vetor base apenas uma vez por tipo/tamanho para economizar tempo
            std::vector<int> vetor_base = tipo.gerador(tamanho);

            for (const auto& algo : algoritmos) {
                // É crucial criar uma cópia para garantir que cada algoritmo ordene o mesmo vetor original
                // Sem isso, apenas o primeiro algoritmo receberia o vetor desordenado
                std::vector<int> vetor_teste = vetor_base;
                Metricas metricas;

                // Usa um relógio de alta precisão para medir o tempo 
                auto inicio = std::chrono::high_resolution_clock::now();
                algo.funcao(vetor_teste, metricas);
                auto fim = std::chrono::high_resolution_clock::now();

                // Calcula a duração em milissegundos
                std::chrono::duration<double, std::milli> duracao = fim - inicio;
                metricas.tempo_ms = duracao.count();

                // Imprime os resultados de forma legivel
                std::cout << "----------------------------------------\n"
                          << "  Algoritmo: " << algo.nome << "\n"
                          << "  - Tempo (ms): " << metricas.tempo_ms << "\n"
                          << "  - Comparações: " << metricas.comparacoes << "\n"
                          << "  - Trocas: " << metricas.trocas << "\n";
            }
                 std::cout << "----------------------------------------\n";
        }
    }

    return 0;
}