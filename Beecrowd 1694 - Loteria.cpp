#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

// `bitset<2505>` cria um array de bits que será usado para marcar se um número é primo ou não.
// O tamanho 2505 garante que possamos verificar primalidade até 2504.
bitset<2505> bs;

// Define um alias `LL` para `long long`, que é um tipo de dado de 64 bits para armazenar números grandes.
typedef long long LL;

// Define um alias `vi` para `vector<int>`, que é um vetor de inteiros.
typedef vector<int> vi;

// Vetor que vai armazenar todos os números primos encontrados até um limite.
vi primes;

// Função para calcular todos os números primos até um determinado limite (`upperbound`).
// Essa é a implementação do algoritmo "Crivo de Eratóstenes".
void sieve(LL upperbound) {
    bs.set();  // Inicializa o `bitset` marcando todos os números como primos.
    bs[0] = bs[1] = 0;  // Marca 0 e 1 como não primos.

    // Loop para marcar os múltiplos de cada número primo como não primos.
    for (LL i = 2; i * i <= upperbound; i++) {
        if (bs[i]) {  // Se `i` é primo:
            for (LL j = i * i; j <= upperbound; j += i) {
                bs[j] = 0;  // Marca todos os múltiplos de `i` como não primos.
            }
            primes.push_back((int)i);  // Adiciona `i` à lista de primos.
        }
    }
}

// Função para verificar se um número `n` é primo.
// Retorna `true` se `n` for primo, usando o array de bits `bs`.
bool isPrime(int n) {
    return bs[n];
}

// Declaração de um array 2D para armazenar os coeficientes binomiais de Pascal.
LL C[55][55];

// Função para calcular a tabela de Pascal, que armazena os coeficientes binomiais.
// Esses coeficientes são usados para calcular combinações de forma eficiente.
void computePascal() {
    for (int i = 0; i < 55; i++) {
        C[i][0] = C[i][i] = 1;  // O primeiro e último elemento de cada linha são sempre 1.
        for (int j = 1; j < i; j++) {
            // Cada elemento é a soma dos dois elementos diretamente acima dele.
            C[i][j] = C[i-1][j-1] + C[i-1][j];
        }
    }
}

// Função para calcular a combinação simples de `n` itens escolhidos `k` de cada vez.
// Usa a tabela de Pascal calculada na função `computePascal()`.
long long simpleCombination(int n, int k) {
    if (k > n) {
        return 0;  // Se `k` for maior que `n`, a combinação é impossível, então retorna 0.
    }
    return C[n][k];  // Retorna o valor precomputado da combinação `n choose k`.
}

int main() {
    computePascal();  // Calcula a tabela de combinações de Pascal.
    sieve(2502);  // Calcula todos os primos até 2502 usando o crivo de Eratóstenes.

    int N, M, K;

    // Loop para ler a entrada e processar os dados enquanto houver dados de entrada.
    while (cin >> N >> M >> K && N) {
        // Se `K` for maior que `N` e `M`, não é possível fazer a combinação, então imprime 0 e continua.
        if (K > N && K > M) {
            cout << 0 << endl;
            continue;
        }

        // Cria uma matriz de `N` linhas e `M` colunas, preenchendo-a com números inteiros sequenciais.
        vector<vector<int>> matriz(N, vector<int>(M));
        int cnt = 0;  // Contador para preencher a matriz.
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                matriz[i][j] = cnt++;  // Atribui valores crescentes à matriz.
            }
        }

        LL total = 0;  // Variável que vai acumular o número total de combinações válidas.

        // Conta as combinações válidas por linha.
        for (int i = 0; i < N; ++i) {
            int cont = 0;  // Contador para números não primos na linha `i`.
            for (int j = 0; j < M; ++j) {
                if (!isPrime(matriz[i][j])) {
                    cont++;  // Se o número não for primo, incrementa o contador.
                }
            }
            // Se o número de não primos na linha for maior ou igual a `K`, soma as combinações possíveis.
            if (cont >= K) {
                total += simpleCombination(cont, K);  // Soma as combinações possíveis na linha.
            }
        }

        // Conta as combinações válidas por coluna.
        for (int i = 0; i < M; ++i) {
            int cont = 0;  // Contador para números não primos na coluna `i`.
            for (int j = 0; j < N; ++j) {
                if (!isPrime(matriz[j][i])) {
                    cont++;  // Se o número não for primo, incrementa o contador.
                }
            }
            // Se o número de não primos na coluna for maior ou igual a `K`, soma as combinações possíveis.
            if (cont >= K) {
                total += simpleCombination(cont, K);  // Soma as combinações possíveis na coluna.
            }
        }

        // Caso especial: se `K == 1`, divide o resultado por 2 para evitar duplicação.
        if (K == 1) total /= 2;

        // Imprime o número total de combinações válidas.
        cout << total << endl;
    }

    return 0;  // Encerra o programa.
}
