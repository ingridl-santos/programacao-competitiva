
#include <bits/stdc++.h>

using namespace std;

#define F first
#define S second
#define PB push_back

#define MAXN 10100
#define INF 0x3f3f3f3f

typedef pair<int,int> ii;

vector<ii> lista[MAXN];

int c, v;

//algoritmo de Dijkistra modificado
int dijkstra(int ori, int dest){

	//vetor de distâncias modificado (guarda pares)
	ii dist[MAXN];

	//infinito o vetor de distâncias
	for(int i = 1; i <= c; i++){
    dist[i] = ii(INF,INF);
  }
	//a distância par de 1 a C é 0 (passa por zero pedágios)
	//e a diastância ímpar é INF (pois não existe)
	dist[1] = ii(0,INF);

	//heap de prioridades
	priority_queue< ii, vector<ii>, greater<ii> > heap;

	//adiciono a cidade 1 a distância 0
	heap.push(ii(0,1));

	//enquanto a heap não estiver vazia
	while(!heap.empty()){

		int v = heap.top().S, d = heap.top().F; heap.pop();

		//se d supera as duas distâncias, está desatualizado
		if(d > dist[v].F && d>dist[v].S){
      continue;
    }

		//para cada vizinho de v
		for(int i = 0; i < lista[v].size(); i++){
			ii u=lista[v][i];

			//verifico se consigo melhorar a distância ímpar até u
			if(dist[v].F + u.S < dist[u.F].S){
				dist[u.F].S = dist[v].F + u.S;
				heap.push(ii(dist[u.F].S, u.F));
			}

			//ou a distância par
			if(dist[v].S + u.S < dist[u.F].F){
				dist[u.F].F = dist[v].S + u.S;
				heap.push(ii(dist[u.F].F, u.F));
			}
		}
	}

	//se não consigo alcançar o destino
	//com quantidade par de pedágios, retorno -1
	if(dist[dest].F == INF) {
    return -1;
  }

	//caso contrário, retorno a distância
	return dist[dest].F;
}

int main(int argc, char const *argv[]) {

  //leio o destino e a quantidade de arestas
	scanf("%d %d", &c, &v);

	//leio o grafo
	for(int i = 1; i <= v; i++){
		int c1, c2, g;
		scanf("%d %d %d", &c1, &c2, &g);

		lista[c1].PB(ii(c2,g));
		lista[c2].PB(ii(c1,g));
	}

	//imprimo a menor distância par de 1 a C
	printf("%d\n", dijkstra(1,c));

	return 0;
}
