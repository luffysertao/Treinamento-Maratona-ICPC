#include <iostream>     // Biblioteca para entrada e saída de dados
#include <bitset>       // Biblioteca para manipulação de bits, útil para representar grandes conjuntos de valores booleanos
#include <vector>       // Biblioteca para usar a estrutura de dados vector

using namespace std;    // Facilita o uso dos elementos do namespace padrão (std) sem precisar prefixá-los

bitset<10000010> bs;    // Cria um bitset de tamanho 10.000.010, onde cada bit representa se um número é primo ou não
typedef long long LL;   // Define um apelido para o tipo long long, simplificando o código
typedef vector<int> vi; // Define um apelido para o tipo vector<int>, que é um vetor de inteiros

vi primes;              // Vetor de inteiros para armazenar os números primos encontrados

// Função para executar o Crivo de Eratóstenes e encontrar todos os primos até upperbound
void sieve(LL upperbound) {
    bs.set();           // Define todos os bits como 1 (inicialmente assume que todos os números são primos)
    bs[0] = bs[1] = 0;  // Define 0 e 1 como não primos

    // Loop para marcar os múltiplos dos números primos encontrados como não primos
    for (LL i = 2; i * i <= upperbound; i++) {
        if (bs[i]) {    // Se o número atual i é primo
            for (LL j = i * i; j <= upperbound; j += i) {
                bs[j] = 0; // Marca todos os múltiplos de i como não primos
            }
            primes.push_back((int)i); // Adiciona o número primo ao vetor primes
        }
    }
}

// Função para verificar se um número n é primo
bool isPrime(int n, LL upperbound) {
    if (n <= upperbound) {
        return bs[n];  // Se o número está dentro do intervalo do bitset, retorna se ele é primo ou não
    }

    // Se o número é maior que upperbound, verifica se é divisível por algum primo já encontrado
    for (int i = 0; i < primes.size(); i++) {
        if (n % primes[i] == 0) {
            return false; // Se n é divisível por algum primo, então não é primo
        }
    }

    return true; // Se não for divisível por nenhum dos primos menores que sqrt(n), é primo
}

// Função principal
int main(void) {
    int qntd;     // Variável para armazenar a quantidade de números a serem verificados
    int num;      // Variável para armazenar cada número a ser verificado
    cin >> qntd;  // Lê a quantidade de números

    LL upperbound = 10000000; // Define o limite superior para o crivo de Eratóstenes
    sieve(upperbound);        // Executa o crivo para encontrar todos os primos até upperbound

    // Loop para verificar se cada número fornecido é primo
    for (int i = 0; i < qntd; i++) {
        cin >> num; // Lê o número a ser verificado
        if (isPrime(num, upperbound)) {
            cout << num << " eh primo" << endl; // Se for primo, imprime que é primo
        } else {
            cout << num << " nao eh primo" << endl; // Se não for primo, imprime que não é primo
        }
    }

    return 0; // Retorna 0 indicando que o programa terminou com sucesso
}
