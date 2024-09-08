#include <cstdio>
#include <bitset>
#include <vector>

using namespace std;

#define MAXN 1000000  // Define um valor máximo de 1.000.000 para o tamanho do crivo

// Declaração de variáveis globais:
bitset<MAXN + 10> bs;  // bitset para representar os números primos até MAXN, onde '1' indica primo
typedef long long LL;   // Define um tipo de dado 'LL' para facilitar a utilização de 'long long'
typedef vector<int> vi; // Define 'vi' como um alias para 'vector<int>'

vi primes;  // Vetor que armazenará todos os números primos encontrados
int soma[MAXN + 10];  // Vetor de prefixos que será usado para calcular os resultados

// Função para gerar os números primos utilizando o algoritmo do Crivo de Eratóstenes:
void sieve(LL upperbound) {
    bs.set();  // Inicializa todos os bits do bitset como '1', assumindo que todos são primos no início
    bs[0] = bs[1] = 0;  // Define 0 e 1 como não primos, pois não são considerados primos

    // Loop que percorre todos os números de 2 até o limite superior (upperbound)
    for (LL i = 2; i <= upperbound; i++) {
        if (bs[i]) {  // Se 'i' for primo, ele entra no laço
            // Marca todos os múltiplos de 'i' como não primos, começando de i^2
            for (LL j = i * i; j <= upperbound; j += i) {
                bs[j] = 0;  // Define o bit como 0, indicando que o número não é primo
            }
            // Armazena o número primo encontrado no vetor 'primes'
            primes.push_back((int)i);
        }
    }
}

// Função para verificar se um número é primo:
bool isPrime(int n) {
    // Se o número 'n' for menor que o valor máximo, verifica diretamente no bitset
    if (n < MAXN) {
        return bs[n];  // Retorna true se 'n' for primo (bit igual a 1), false caso contrário
    }

    // Se 'n' for maior que o valor máximo, realiza uma verificação manual com os primos armazenados
    for (int i = 0; i < primes.size(); i++) {
        // Se 'n' for divisível por qualquer primo, retorna false (não é primo)
        if (n % primes[i] == 0) {
            return false;
        }
    }

    // Se passar por todas as verificações, retorna true (é primo)
    return true;
}

int main() {
    // Inicializa o crivo de Eratóstenes até MAXN para preencher o bitset com os primos
    sieve(MAXN);

    // Preenche o vetor 'soma' com prefixos baseados em uma regra específica:
    for (int i = 2; i < MAXN; i++) {
        if (bs[i])  // Se o número 'i' for primo
            // Calcula o valor de soma[i] como a soma acumulada de soma[i-1] + uma verificação:
            // Verifica se i-2 ou i+2 também são primos (primos gêmeos)
            soma[i] = soma[i - 1] + int(bs[i - 2] || bs[i + 2]);
        else
            // Se 'i' não for primo, apenas propaga o valor anterior de soma
            soma[i] = soma[i - 1];
    }

    // Leitura de consultas (Q) onde cada consulta pergunta por um intervalo de números
    int Q;
    scanf("%d", &Q);  // Lê o número de consultas (Q)

    // Loop para processar cada consulta
    while (Q--) {
        int a, b;
        scanf("%d %d", &a, &b);  // Lê os limites a e b da consulta

        // Se 'a' for maior que 'b', troca os valores (para garantir a ordem correta)
        if (a > b) {
            int temp = b;
            b = a;
            a = temp;
        }

        // Imprime a quantidade de primos gêmeos no intervalo [a, b]
        // A resposta é dada por soma[b] - soma[a-1], que usa o vetor de soma acumulada
        printf("%d\n", soma[b] - soma[a - 1]);
    }

    return 0;
}