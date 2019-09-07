#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
  int n,k;

  int fat[9];
  fat[0] = 1;
  //resolucao para fatorial
  for(int i = 1; i <= 8; i++){
    fat[i] = i*fat[i-1];
  }

  cin >> n;

  int x = 0;
  for(int i = 8; i >= 0; i--){
    x = x + (n/fat[i]);
    n = n % fat[i];
  }

  cout << x << endl;

  return 0;
}
