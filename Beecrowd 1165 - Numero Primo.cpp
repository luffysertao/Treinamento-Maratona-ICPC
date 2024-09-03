#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

// Definindo um bitset grande para armazenar a primalidade de números até 10.000.010
bitset<10000010> bs; 
typedef long long LL; // Definindo um alias para "long long" como LL
typedef vector<int> vi; // Definindo um alias para um vetor de inteiros como vi

vi primes; // Vetor para armazenar os números primos

// Função para gerar todos os primos até um limite superior usando o Crivo de Eratóstenes
void sieve(LL upperbound) {
    bs.set(); // Inicializa todos os bits como 1 (assumindo que todos os números são primos)
    bs[0] = bs[1] = 0; // 0 e 1 não são primos

    // Loop para marcar os múltiplos de cada número primo como não-primos
    for (LL i = 2; i * i <= upperbound; i++) {
        if (bs[i]) { // Se i é primo
            for (LL j = i * i; j <= upperbound; j += i) {
                bs[j] = 0; // Marca os múltiplos de i como não-primos
            }
            primes.push_back((int)i); // Adiciona o número primo ao vetor
        }
    }
}

// Função para verificar se um número é primo
bool isPrime(int n, LL upperbound) {
    // Se o número está dentro do limite calculado, verifica diretamente no bitset
    if (n <= upperbound) {
        return bs[n]; // Retorna se o número é primo ou não
    }

    // Se o número é maior que o limite calculado, verifica usando os primos armazenados
    for (int i = 0; i < primes.size(); i++) {
        if (n % primes[i] == 0) {
            return false; // Se o número é divisível por algum primo, não é primo
        }
    }

    return true; // Se não for divisível por nenhum primo, é primo
}

int main(void) {
    int qntd; // Variável para armazenar a quantidade de números a serem verificados
    int num; // Variável para armazenar cada número a ser verificado
    cin >> qntd; // Lê a quantidade de números

    LL upperbound = 10000000; // Definindo o limite superior para a geração de primos
    sieve(upperbound); // Gera todos os primos até o limite superior

    // Loop para verificar se cada número inserido é primo
    for (int i = 0; i < qntd; i++) {
        cin >> num; // Lê o número a ser verificado
        if (isPrime(num, upperbound)) {
            cout << num << " eh primo" << endl; // Imprime se o número é primo
        } else {
            cout << num << " nao eh primo" << endl; // Imprime se o número não é primo
        }
    }

    return 0;
}
