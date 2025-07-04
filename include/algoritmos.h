#pragma once

#include <vector>
#include "metricas.h"

// Declarações das funções de ordenação
void bubbleSort(std::vector<int>& vetor, Metricas& metricas);
void selectionSort(std::vector<int>& vetor, Metricas& metricas);
void insertionSort(std::vector<int>& vetor, Metricas& metricas);
void mergeSort(std::vector<int>& vetor, Metricas& metricas);
void quickSort(std::vector<int>& vetor, Metricas& metricas);

