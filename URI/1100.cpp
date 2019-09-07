##include <iostream>

#define TAM 9
#define Infinito 999999999

using namespace std;

typedef struct{
  int origem;
  int destino;
  int peso;
} Aresta;

Aresta aresta[350];

int bellmanFord(int nArestas, int nNodes, int origem, int destino){

  int troca = 1;
  int dist[65];

  for(int i = 0; i <= nNodes; i++){
    dist[i] = Infinito;
  }

  dist[origem] = 0;
  //se nao ha efeito em nenhuma iteracao entoa houve troca, portanto sai
  for(int i = 0; i <= nNodes && troca; i++){
    troca = 0;
    for(j = 0; j< nArestas; j++){
      if(dist[aresta[j].destino] > dist[aresta[j].origem] + aresta[j].peso){
        dist[aresta[j].destino] = dist[aresta[j].origem] + aresta[j].peso;
        troca = 1;
      }
    }
  }

  return dist[destino];
}


int int main(int argc, char const *argv[]) {

  int tabuleiro[TAM][TAM];
  int cont = 1;

  for(int i = 1; i < TAM; i++){
    for(int j = 1; j < TAM; j++){
      tabuleiro[i][j] = cont++;
    }
  }

  //flood-fill
  cont = 0;
  for(int i = 1; i < TAM; i++){
    for(int j = 1; j < TAM; j++){
      if((i+1) < TAM && (j+2) < TAM){
        aresta[cont].origem = tabuleiro[i][j];
        aresta[cont].destino = tabuleiro[i+1][j+2];
        aresta[cont].peso = 1;
        cont++;
      }
      if((i+1) < TAM && (j-2) >= 1){
        aresta[cont].origem = tabuleiro[i][j];
        aresta[cont].destino = tabuleiro[i+1][j-2];
        aresta[cont].peso = 1;
        cont++;
      }
      if((i+2) < TAM && (j+1) < TAM){
        aresta[cont].origem = tabuleiro[i][j];
        aresta[cont].destino = tabuleiro[i+2][j+1];
        aresta[cont].peso = 1;
        cont++;
      }
      if((i-1) > 0 && (j+2) < TAM){
        aresta[cont].origem = tabuleiro[i][j];
        aresta[cont].destino = tabuleiro[i-1][j+2];
        aresta[cont].peso = 1;
        cont++;
      }
      if((i-1) > 0 && (j-2) >=1){
        aresta[cont].origem = tabuleiro[i][j];
        aresta[cont].destino = tabuleiro[i-1][j-2];
        aresta[cont].peso = 1;
        cont++;
      }
      if((i-2) > 0 && (j+1) < TAM){
        aresta[cont].origem = tabuleiro[i][j];
        aresta[cont].destino = tabuleiro[i-2][j+1];
        aresta[cont].peso = 1;
        cont++;
      }
      if((i-2) > 0 && (j-1) >= 1){
        aresta[cont].origem = tabuleiro[i][j];
        aresta[cont].destino = tabuleiro[i-2][j-1];
        aresta[cont].peso = 1;
        cont++;
      }
    }
  }

  int origem, destino;
  string de, para;

  while(cin >> de >> para){
    origem = (de[0]-'a')*8 + de[1]-'0';
    destino = (para[0]-'a')*8 + para[1]-'0';

    cout << "To get from" << de << "to" << para << "takes" << bellmanFord(cont,
    64,origem, destino) << "knight moves." << endl;

    if(de == para){
      break;
    }
  }
  return 0;
}
