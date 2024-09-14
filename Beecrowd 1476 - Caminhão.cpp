#include <algorithm>
#include <cstdio>
#include <vector>
#include <climits>

#define MAXN 100010  // Definição do tamanho máximo do grafo

using namespace std;

typedef pair<int, int> Edge;              // Representa uma aresta como (vértice, peso)
typedef pair<int, Edge> WeightedEdge;    // Representa uma aresta com peso negativo para ordenar

// Arrays globais para armazenar o estado do grafo e da união dos conjuntos
int parent[MAXN], depth[MAXN], edgeToParent[MAXN], representative[MAXN], n, m, queries;
vector<Edge> graph[MAXN];               // Lista de adjacências para o grafo
vector<WeightedEdge> edges;             // Lista de arestas com pesos para o algoritmo de Kruskal

// Função para encontrar o representante de um conjunto (com path compression)
int findSet(int x) {
    if (representative[x] == x) return x;  // Se x é o representante do seu conjunto, retorna x
    return representative[x] = findSet(representative[x]);  // Compression: atualiza o pai de x diretamente
}

// Função para unir dois conjuntos (union by rank)
void unionSets(int x, int y) {
    x = findSet(x);  // Encontra o representante do conjunto de x
    y = findSet(y);  // Encontra o representante do conjunto de y
    if (x > y) swap(x, y);  // Garante que x seja o menor dos dois representantes
    representative[y] = x;  // Une os conjuntos, fazendo x o representante de y
}

// Função DFS para calcular a profundidade e o peso da aresta até o pai
void dfs(int node) {
    for (const auto& [neighbor, weight] : graph[node]) {  // Itera sobre vizinhos do nó
        if (parent[neighbor] == -1) {  // Se o vizinho ainda não foi visitado
            parent[neighbor] = node;  // Define o pai do vizinho
            depth[neighbor] = depth[node] + 1;  // Atualiza a profundidade do vizinho
            edgeToParent[neighbor] = weight;  // Armazena o peso da aresta para o pai
            dfs(neighbor);  // Chama recursivamente a DFS para o vizinho
        }
    }
}

// Função para encontrar o menor peso da aresta no caminho entre dois vértices usando o LCA
int findLCA(int u, int v) {
    int minEdge = INT_MAX;  // Armazena o menor peso encontrado no caminho
    while (u != v) {  // Continua até que u e v se encontrem
        if (depth[u] > depth[v]) {  // Se u está mais fundo que v
            minEdge = min(minEdge, edgeToParent[u]);  // Atualiza o peso mínimo
            u = parent[u];  // Move u para seu pai
        } else {
            minEdge = min(minEdge, edgeToParent[v]);  // Atualiza o peso mínimo
            v = parent[v];  // Move v para seu pai
        }
    }
    return minEdge;  // Retorna o menor peso encontrado
}

// Função para ler um inteiro da entrada
void readInt(int &x) {
    x = 0;
    int c = getchar_unlocked();  // Leitura rápida do próximo caractere
    while (c < '0' || c > '9') c = getchar_unlocked();  // Pular caracteres não numéricos
    while (c >= '0' && c <= '9') {  // Ler o número
        x = x * 10 + (c - '0');  // Atualiza o valor de x
        c = getchar_unlocked();  // Lê o próximo caractere
    }
}

// Função para imprimir um inteiro na saída
void printInt(int n) {
    if (n == 0) {
        putchar_unlocked('0');  // Imprime zero diretamente
        putchar_unlocked('\n');  // Nova linha
        return;
    }
    if (n < 0) {
        putchar_unlocked('-');  // Imprime o sinal negativo
        n = -n;  // Torna n positivo para facilitar a impressão
    }
    char buffer[11];  // Buffer para armazenar os dígitos
    int index = 10;
    buffer[index--] = '\n';  // Nova linha no final do buffer
    while (n) {  // Preenche o buffer com os dígitos de n
        buffer[index--] = (n % 10) + '0';  // Adiciona o dígito mais à direita
        n /= 10;  // Remove o dígito mais à direita de n
    }
    while (index < 10) putchar_unlocked(buffer[++index]);  // Imprime os dígitos
}

// Função principal
int main() {
    while (scanf("%d %d %d", &n, &m, &queries) != EOF) {  // Lê n (nós), m (arestas) e s (consultas)
        // Inicializa arrays e vetores
        for (int i = 0; i <= n; ++i) {
            parent[i] = -1;  // Sem pai definido ainda
            representative[i] = i;  // Cada nó é seu próprio representante
            depth[i] = -1;  // Profundidade ainda não definida
            edgeToParent[i] = INT_MAX;  // Peso da aresta para o pai
            graph[i].clear();  // Limpa o grafo
        }
        edges.clear();  // Limpa a lista de arestas
        
        // Lê as arestas e suas informações
        for (int i = 0; i < m; ++i) {
            int u, v, weight;
            readInt(u);
            readInt(v);
            readInt(weight);
            edges.emplace_back(-weight, make_pair(u, v));  // Adiciona a aresta com peso negativo para ordenar em ordem decrescente
        }

        sort(edges.begin(), edges.end());  // Ordena as arestas em ordem não crescente pelo peso

        int remainingEdges = n - 1;  // Número de arestas restantes para construir a MST
        for (const auto& [weight, edge] : edges) {
            int u = edge.first;
            int v = edge.second;
            if (findSet(u) != findSet(v)) {  // Se u e v não estão no mesmo conjunto
                unionSets(u, v);  // Une os conjuntos de u e v
                graph[u].emplace_back(v, -weight);  // Adiciona v ao grafo de u com o peso original
                graph[v].emplace_back(u, -weight);  // Adiciona u ao grafo de v com o peso original
                if (--remainingEdges == 0) break;  // Se todas as arestas necessárias foram adicionadas, sai do loop
            }
        }

        depth[1] = 0;  // Define a profundidade da raiz (nó 1)
        parent[1] = 0;  // Define o pai da raiz como ela mesma
        dfs(1);  // Realiza a DFS a partir do nó 1

        while (queries--) {  // Processa cada consulta
            int u, v;
            readInt(u);
            readInt(v);
            printInt(findLCA(u, v));  // Encontra e imprime o menor peso da aresta no caminho entre u e v
        }
    }
    return 0;
}
