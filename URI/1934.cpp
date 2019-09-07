#include <bits/stdc++.h>

using namespace std;

int lin, col; // numero de linhas e colunas na matriz
string mat[101][101]; //matriz com palavras
int somaLin[101], somaCol[101]; //soma de cada linha e coluna

map<string, int> valores; //armazena o valor encontrado das palavras
set<string> total; //armazena todas as palavras sem repeticao

int main(int argc, char const *argv[]) {

  while(scanf("%d %d", &lin,&col) != EOF){
    //limpa as estruturas
    valores.clear();
    total.clear();

    //leitura dos dados
    for(int i = 0; i < lin; i++){
      for(int j = 0; j < col; j++){
        cin >> mat[i][j];
        total.insert(mat[i][j]);
      }
      cin >> somaLin[i];
    }
    for(int i = 0; i < col;i++){
      cin >> somaCol[i];
    }

    //encontrando o valor de todas as palavras
    while(valores.size() < total.size()){
      //varredura horizontal
      for(int i = 0; i < lin; i++){
        map<string,int> naoCalc;
        int somaAtual = 0;
        for(int j = 0; j < col; j++){
          if(valores.find(mat[i][j]) == valores.end()){
            naoCalc[mat[i][j]]++;
          }else{
            somaAtual += valores[mat[i][j]];
          }
        }
        if(naoCalc.size() == 1){
          pair<string,int> p = *naoCalc.begin();
          valores[p.first] = (somaLin[i]-somaAtual)/p.second;
        }
      }

      //varredura vertical
      for(int j = 0; j < col; j++){
        map<string,int> naoCalc;
        int somaAtual = 0;
        for(int i = 0; i < lin; i++){
          if(valores.find(mat[i][j]) == valores.end()){
            naoCalc[mat[i][j]]++;
          }else{
            somaAtual += valores[mat[i][j]];
          }
        }
        if(naoCalc.size() == 1){
          pair<string,int> p = *naoCalc.begin();
          valores[p.first] = (somaCol[j]-somaAtual)/p.second;
        }
      }
    }
    for(auto i : valores){
      cout << i.first << " " << i.second << endl;
    }
  }
  // return 0;
}
