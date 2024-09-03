#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

typedef vector<int> vi; // Definindo um alias para um vetor de inteiros

// Função que usa o Crivo de Eratóstenes para gerar todos os primos até num
void sieve(long long num, vi &primos) {
    bitset<1005> bs; // Bitset para marcar números como primos ou não
    bs.set(); // Inicializa todos os bits como 1 (assumindo que todos os números são primos)
    bs[0] = bs[1] = 0; // 0 e 1 não são primos

    // Loop para marcar os múltiplos de cada número primo como não-primos
    for (long long i = 2; i <= num; i++) {
        if(bs[i]) { // Se i é primo
            for(long long j = i*i; j <= num; j += i) {
                bs[j] = 0; // Marca múltiplos de i como não-primos
            }
            primos.push_back((int)i); // Adiciona o número primo ao vetor
        }
    }
}

int main() {
    int num;
    cin >> num; // Recebe a entrada N
    
    vi primos; // Vetor para armazenar os números primos
    sieve(num, primos); // Gera todos os primos até num e os armazena em primos
    
    int X = -1, Y = -1; // Variáveis para armazenar os primos gêmeos

    // Percorre a lista de primos para encontrar os primos gêmeos mais próximos
    for (int i = 1; i < primos.size(); i++) {
        if (primos[i] - primos[i - 1] == 2) { // Verifica se formam um par de primos gêmeos
            X = primos[i - 1]; // Primeiro primo do par
            Y = primos[i]; // Segundo primo do par
        }
    }

    // Verifica se encontrou algum par de primos gêmeos
    if (X != -1 && Y != -1) {
        cout << X << " " << Y << endl; // Imprime o par de primos gêmeos mais próximos
    } else {
        cout << "Nenhum par de primos gêmeos encontrado." << endl; // Mensagem de erro se não encontrar nenhum par
    }

    return 0;
}
