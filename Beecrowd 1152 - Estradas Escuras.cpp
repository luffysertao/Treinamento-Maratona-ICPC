#include <iostream>   // Biblioteca para entrada e saída padrão
#include <vector>     // Biblioteca para utilizar o contêiner de vetor
#include <algorithm>  // Biblioteca para funções de algoritmos como sort

using namespace std;  // Para usar o namespace std sem prefixar std::

const int MAXN = 200100;  // Define o tamanho máximo para os arrays de vértices e arestas

int parent[MAXN], treeRank[MAXN];  // Arrays para armazenar os pais e o rank dos conjuntos disjuntos

// Estrutura para representar uma aresta com peso e dois vértices
struct Edge {
    int weight, u, v;
};

// Função para encontrar o representante do conjunto ao qual o vértice pertence
int find(int x) {
    if (x == parent[x]) return x;  // Se x é o pai de si mesmo, então x é o representante
    // Caminho de compressão: atualiza o pai do vértice para o representante encontrado
    return parent[x] = find(parent[x]);
}

// Função para unir dois conjuntos
void unionSets(int x, int y) {
    x = find(x);  // Encontra o representante do conjunto de x
    y = find(y);  // Encontra o representante do conjunto de y
    // Une os conjuntos com base no "rank" (profundidade) dos conjuntos
    if (treeRank[x] < treeRank[y])
        parent[x] = y;  // Faz o conjunto de x ser filho do conjunto de y
    else if (treeRank[x] > treeRank[y])
        parent[y] = x;  // Faz o conjunto de y ser filho do conjunto de x
    else {
        parent[x] = y;  // Faz o conjunto de x ser filho do conjunto de y
        treeRank[y]++;  // Aumenta o rank do conjunto de y
    }
}

int main() {
    while (true) {  // Laço infinito para processar múltiplos casos de teste
        int n, m;  // n = número de vértices, m = número de arestas
        int totalWeight = 0;  // Armazena o peso total das arestas

        cin >> n >> m;  // Lê o número de vértices e arestas
        if (n == 0 && m == 0) break;  // Se ambos são zero, termina a execução

        // Inicializa os conjuntos disjuntos
        for (int i = 0; i < n; i++) {
            parent[i] = i;  // Cada vértice é seu próprio pai
            treeRank[i] = 0;  // Inicialmente, todos os conjuntos têm rank 0
        }

        vector<Edge> edges(m);  // Vetor para armazenar todas as arestas

        // Lê as arestas e seus pesos
        for (int i = 0; i < m; i++) {
            int u, v, weight;
            cin >> u >> v >> weight;  // Lê os vértices u, v e o peso da aresta
            edges[i] = {weight, u, v};  // Armazena a aresta no vetor
            totalWeight += weight;  // Soma o peso da aresta ao peso total
        }

        // Ordena as arestas em ordem crescente de peso
        sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
            return a.weight < b.weight;
        });

        int mstWeight = 0;  // Peso da árvore geradora mínima (MST)
        for (const Edge &edge : edges) {  // Itera sobre todas as arestas ordenadas
            if (find(edge.u) != find(edge.v)) {  // Se u e v estão em conjuntos diferentes
                unionSets(edge.u, edge.v);  // Une os conjuntos que contêm u e v
                mstWeight += edge.weight;  // Adiciona o peso da aresta à MST
            }
        }

        // Imprime o peso total das arestas que não foram incluídas na MST
        cout << (totalWeight - mstWeight) << endl;
    }
    return 0;
}
