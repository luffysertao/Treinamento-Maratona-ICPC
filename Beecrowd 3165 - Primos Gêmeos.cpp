#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

bitset<1005> bs;
typedef long long LL;
typedef vector<int> vi;

vi primos;

LL size;


void sieve(LL num){
    size = num;
    bs.set();
    bs[0] = bs[1] = 0;
    for (LL i = 2; i*i <= size; i++){
        if(bs[i]){
            for(LL j = i*i; j <= size; j += i){
                bs[j] = 0;
            }
            primos.push_back((int)i);
        }
    }
}


void addPrime(int p, vector<int>& lista){
    lista.push_back(p);
    if (lista.size() > 3) {
        lista.erase(lista.begin());
    }
}

int main()
{
    int num;
    cin >> num;
    
    sieve(num); 
    
    vector<int> lista;
    
    for (int i = 2; i <= num; ++i) {
        if (bs[i]) { 
            addPrime(i, lista);
        }
    }
    
    if (!lista.empty()){
        lista.erase(lista.begin());
    }
    
    for (int p : lista) {
        cout << p << " ";
    }
    cout << endl;
    
    return 0;
}
