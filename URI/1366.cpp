#include <iostream>

using namespace std;

int main(int argc, char const *argv[]){
    // n qtd de comprimentos de varetas no conjunto
    // x qtd de quadrados possiveis
    // c comprimento da vareta  e
    // v qtd de varetas com comprimento c
    int n, x, c, v;

    while(cin >> n && n){
        x = 0;
        for (int i = 0; i < n; i++){
            cin >> c >> v;
            x = x + v/2;        //qtd de varetas de comprimento c q podem ser dividas em pares
        }

        cout << x/2 << endl;   // x / 2 resulta na qtd maxima de retangulos que podem ser formados a partir dos pares formados em x
    }
    return 0;
}
