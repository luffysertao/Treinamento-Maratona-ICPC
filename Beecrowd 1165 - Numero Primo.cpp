#include <iostream>
#include <bitset>
#include <vector>

using namespace std; 

bitset<10000010> bs;  // Define um bitset chamado 'bs' com tamanho 10.000.010 para armazenar números primos (1) e não primos (0)
typedef long long LL;  // Define 'LL' como um apelido para 'long long', um tipo de dado para números inteiros grandes
typedef vector<int> vi;  // Define 'vi' como um apelido para 'vector<int>', um vetor de inteiros

LL size;  // Variável global para armazenar o limite superior do crivo de Eratóstenes
vi primes;  // Vetor global para armazenar todos os números primos encontrados

// Função que implementa o crivo de Eratóstenes para encontrar todos os números primos até 'upperbound'
void sieve(LL upperbound){
    size = upperbound;  // Ajusta 'size' para incluir o 'upperbound'
    bs.set();  // Inicializa todos os bits do bitset 'bs' como 1 (assumindo que todos os números são primos)
    bs[0] = bs[1] = 0;  // Marca 0 e 1 como não primos
    for (LL i = 2; i*i <= size; i++){  // Itera de 2 até a raiz quadrada de 'size' para evitar overflow em i*i
        if(bs[i]){  // Se 'bs[i]' for 1, 'i' é primo
            for(LL j = i*i; j <= size; j += i){  // Marca todos os múltiplos de 'i' como não primos (bs[j] = 0)
                bs[j] = 0;
            }
            primes.push_back((int)i);  // Adiciona 'i' ao vetor de primos
        }
    }
}

// Função que verifica se um número 'n' é primo
bool isPrime(int n) {
    if (n < size) {  // Verifica se 'n' está dentro do limite do crivo
        return bs[n];  // Retorna 'true' se 'n' for primo (bs[n] == 1), 'false' caso contrário
    }
    
    // Verifica se 'n' é divisível por algum dos primos já conhecidos
    for (int i = 0; i < primes.size(); i++) {
        if (n % primes[i] == 0) {  // Se 'n' for divisível por algum primo, não é primo
            return false;
        }
    }
    
    return true;  // Se nenhum primo divide 'n', então 'n' é primo
}

// Função principal do programa
int main(void)
{   
    int qntd;  // Declara uma variável para armazenar a quantidade de números a serem verificados
    int num;  // Declara uma variável para armazenar cada número a ser verificado
    cin >> qntd;  // Lê a quantidade de números a serem verificados
    
    sieve(10000000);  // Cria a tabela de primos até 10^7 usando o crivo de Eratóstenes
    
    for (int i = 0; i < qntd; i++){  // Loop para processar cada número fornecido
        cin >> num;  // Lê o próximo número a ser verificado
        if (isPrime(num)){  // Verifica se 'num' é primo
            cout << num << " eh primo" << endl;  // Se for primo, imprime a mensagem correspondente
        } else {
            cout << num << " nao eh primo" << endl;  // Se não for primo, imprime a mensagem correspondente
        }
    }
    
    return 0;
}
