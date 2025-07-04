# 📊 Análise Comparativa de Algoritmos de Ordenação  

## 🚀 Descrição do Projeto  
Repositório contendo implementações e análises experimentais de 5 algoritmos clássicos de ordenação, desenvolvido como parte da disciplina de Estruturas de Dados.  

**Objetivo principal**:  
Comparar o desempenho real dos algoritmos em diferentes cenários de dados através de métricas empíricas (tempo, comparações e trocas).

---

## ⚙️ Algoritmos Implementados  
1. **Bubble Sort**  
2. **Insertion Sort**  
3. **Selection Sort**  
4. **Merge Sort**  
5. **Quick Sort**  

---

## ▶️ Como Executar  

### Pré-requisitos  
- Compilador C++ (g++ recomendado)  
- Sistema Linux/macOS (ou WSL no Windows)  

### Passos:  
```bash
# Clonar repositório
git clone https://github.com/leonardonadson/analise-de-algoritmos-de-ordenacao.git

# Compilar projeto
make

# Executar análise completa
./final_cpp
```

### Funcionalidades:  
- Gera datasets de teste (aleatórios, ordenados e inversos)  
- Executa todos os algoritmos com tamanhos variados (100, 1000, 5000 elementos)  
- Exibe os dados em terminal de forma organizada para posterior geração de gráficos  

---

## 📊 Saída Esperada  
```plaintext
===== TESTES PARA VETOR Aleatorio (N=100) =====
----------------------------------------
  Algoritmo: BubbleSort
  - Tempo (ms): 0.0566
  - Comparações: 4950
  - Trocas: 2609
----------------------------------------
  Algoritmo: SelectionSort
  - Tempo (ms): 0.0329
  - Comparações: 4950
  - Trocas: 97
----------------------------------------
  Algoritmo: InsertionSort
  - Tempo (ms): 0.0218
  - Comparações: 2706
  - Trocas: 2707
----------------------------------------
  Algoritmo: MergeSort
  - Tempo (ms): 0.0332
  - Comparações: 542
  - Trocas: 672
----------------------------------------
  Algoritmo: QuickSort
  - Tempo (ms): 0.0105
  - Comparações: 718
  - Trocas: 335
----------------------------------------
```

---

## 👨‍💻 Autor  
[<img src="https://avatars.githubusercontent.com/u/72714982?v=4" width=100 style="border-radius:50%"><br> **Leonardo Nadson**](https://github.com/leonardonadson)  
Desenvolvido como projeto acadêmico - IMD/UFRN 2025
