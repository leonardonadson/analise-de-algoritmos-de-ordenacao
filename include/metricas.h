#pragma once

// Estrutura para armazenar as métricas de desempenho de um algoritmo
struct Metricas {
    long long comparacoes = 0;
    long long trocas = 0;
    double tempo_ms = 0.0;

    // Reinicia as métricas para uma nova execução
    void reset() {
        comparacoes = 0;
        trocas = 0;
        tempo_ms = 0.0;
    }
};
