#include <bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[]) {
  int j,r;
  int v[510];
  int x;

  cin >> j >> r;
    for(int i = 0; i < j; i++){
      v[i] = 0;
    }
    for(int i = 0; i < j * r; i++){
      cin >> x;
      v[i%j] += x;
    }

    int maior = v[0];
    int pos = 0;

    for(int i = 1; i < j; i++){
      if(v[i] >= maior){
        maior = v[i];
        pos = i;
      }
    }
    cout << pos + 1 << endl;
  return 0;
}
