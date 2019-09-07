#include <iostream>
#include <list>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <unordered_map>

#define MAX_CARACTERES 50
#define INFINITO 99999999

using namespace std;

typedef struct{
  char primLetra;
  string idiomaVizinho;
  int peso;
}Aresta;

//Alterando a funcao do operador
bool operator<(const Aresta& a, const Aresta& b){
    return a.peso > b.peso;
}

//insere arestas e mapeia com hash
void insereAresta(unordered_map<string, list<Aresta>> &grafo, string idioma1,string idioma2, string palavra){

  Aresta aresta;

  aresta.primLetra = palavra.at(0);
  aresta.peso = palavra.length();
  aresta.idiomaVizinho = idioma2;

  if (grafo.count(idioma1)) { //Existe idioma1?
    grafo[idioma1].push_back(aresta);
  }else {
    grafo.insert(make_pair(idioma1, list<Aresta>()));
    grafo[idioma1].push_back(aresta);
   }

   aresta.idiomaVizinho = idioma1;

   if(grafo.count(idioma2)){ //Existe idioma2
     grafo[idioma2].push_back(aresta);
   }else{
     grafo.insert(make_pair(idioma2,list<Aresta>()));
     grafo[idioma2].push_back(aresta);
   }
}

int dijkstra(unordered_map<string, list<Aresta>> grafo, string origem, string destino) {
    unordered_map<string, int> distancias;     //armazena as distancias dos vertices para a origem
    unordered_map<string, char> predecessores; //armazena a inicial da palavra da aresta com o predecessor
    priority_queue<Aresta> fila;               //fila de prioridade
    Aresta auxAresta1, auxAresta2;

    for(auto vertice : grafo) {
        distancias.insert(make_pair(vertice.first, INFINITO));
        predecessores.insert(make_pair(vertice.first, 0));
    }

    auxAresta1.idiomaVizinho = origem;
    auxAresta1.peso = 0;
    fila.push(auxAresta1);
    distancias[origem] = 0;

    while(!fila.empty()) {
        auxAresta2 = fila.top();
        fila.pop();

        for(auto aresta : grafo[auxAresta2.idiomaVizinho]) {
            if((predecessores[auxAresta2.idiomaVizinho] != aresta.primLetra) && (distancias[aresta.idiomaVizinho] > distancias[auxAresta2.idiomaVizinho] + aresta.peso)) {
                distancias[aresta.idiomaVizinho] = distancias[auxAresta2.idiomaVizinho] + aresta.peso;

                auxAresta1.peso = aresta.peso;
                auxAresta1.idiomaVizinho = aresta.idiomaVizinho;
                predecessores[auxAresta1.idiomaVizinho] = aresta.primLetra;

                fila.push(auxAresta1);
            }
        }
    }
    return distancias[destino];
}

int main(int argc, char const *argv[]) {

  unordered_map<string, list<Aresta>> grafo;

  int m, disTotal;
  string origem, destino;
  string idioma1, idioma2, palavra;

  cin >> m;
  while(m){
    cin >> origem >> destino;
    for(int i = 0; i < m; i++){
      cin >> idioma1 >> idioma2 >> palavra;
      insereAresta(grafo, idioma1, idioma2, palavra);
    }

    disTotal = dijkstra(grafo, origem, destino);
    if((disTotal == 0) || (disTotal == INFINITO)){
      disTotal = dijkstra(grafo,destino,origem);
      if((disTotal == 0) ||(disTotal == INFINITO)){
        printf("impossivel\n");
      }else{
        printf("%d\n", disTotal);
      }
    }else{
      printf("%d\n", disTotal);
    }

    grafo.clear();

    cin >> m;
  }
  return 0;
}
