# Importa o módulo sys, que fornece funções e variáveis usadas para manipular diferentes partes do ambiente de tempo de execução Python.
import sys 
import math 

# Função para calcular os números primos até um limite superior usando o algoritmo Crivo de Eratóstenes
def sieve(upperbound):
    bs = [True] * (upperbound + 1)  # Cria uma lista de booleanos (True) de tamanho upperbound + 1, representando se o índice é primo.
    bs[0] = bs[1] = False  # 0 e 1 não são números primos, então definimos esses índices como False.
    primes = []  # Inicializa a lista que armazenará os números primos.

    # Percorre os números de 2 até a raiz quadrada do limite superior (inclusivo).
    for i in range(2, int(upperbound**0.5) + 1):
        if bs[i]:  # Se o número i ainda é considerado primo:
            # Marca todos os múltiplos de i (começando de i^2) como não primos.
            for j in range(i * i, upperbound + 1, i):
                bs[j] = False
    # Gera a lista de números primos a partir dos índices ainda marcados como True.
    primes = [i for i in range(2, upperbound + 1) if bs[i]]
    return bs, primes  # Retorna a lista de booleanos (indicando se é primo) e a lista de números primos.

# Função para verificar se um número é primo, usando a lista de primos calculada pela função sieve
def isPrime(n, upperbound, bs, primes):
    if n <= upperbound:  # Se o número é menor ou igual ao limite superior:
        return bs[n]  # Retorna True se n for primo (conforme a lista bs), ou False se não for.

    # Para números maiores que o limite superior, verifica se n é divisível por algum primo.
    for prime in primes:
        if n % prime == 0:  # Se n é divisível por qualquer primo, não é primo.
            return False
    return True  # Se não foi divisível por nenhum primo, então n é primo.

# Função principal que será executada ao rodar o script.
def main():
    upperbound = 100  # Define o limite superior para calcular os primos.
    bs, primes = sieve(upperbound)  # Gera a lista de booleanos e a lista de primos até o limite superior.

    # Lê todos os dados de entrada do usuário (números) a partir da entrada padrão (stdin).
    input_data = sys.stdin.read().split()
    qntd = int(input_data[0])  # A primeira entrada indica a quantidade de números.
    nums = list(map(int, input_data[1:qntd + 1]))  # Mapeia os próximos qntd valores para uma lista de inteiros.

    factorial_cache = {}  # Inicializa um dicionário para armazenar fatoriais já calculados.

    # Para cada número na lista de números fornecidos:
    for num in nums:
        if isPrime(num, upperbound, bs, primes):  # Verifica se o número é primo.
            if num not in factorial_cache:  # Se o fatorial desse número ainda não foi calculado:
                factorial_cache[num] = math.factorial(num)  # Calcula e armazena o fatorial no cache.
            print(f"{num}! = {factorial_cache[num]}")  # Imprime o fatorial do número.

if __name__ == "__main__":
    main()
