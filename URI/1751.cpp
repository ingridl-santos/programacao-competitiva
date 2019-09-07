#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

//typedef pair <int, int> ii;
typedef vector<int> vi;

typedef{
	int primeiro;
	int segundo;
}adj;
// custo entre o dado vertice e o vertice 1
int custo[100010];

// se o vertice esta no caminho para o amigo mais distante
bool caminho[100010];

// amigo que deseja visitar
int amigos[100010];

// funcao que calcula o custo de um dado vertice ate o vertice 1
int func(int u);

int main() {
	// entrada de vairaveis
	int n, k;
	int a, b, c;
	adj[1].primeiro = 1;

	while(scanf("%d %d", &n, &k) != EOF) {
		// monta o grafo
		for(int i=0; i<n-1; i++) {
			scanf("%d %d %d", &a, &b, &c);

			adj[b].primeiro = a;
			adj[b].segundo = c;
		}

		// leitura dos amigos
		for(int i=0; i<k; i++) {
			scanf("%d", &amigos[i]);
		}

		// calcula o custo de um dado vertice ate o vertice 1
		memset(custo, 0, sizeof(custo));
		for(int i=2; i<=n; i++) if(!custo[i]) {
			custo[i] = func(adj[i].primeiro)+adj[i].segundo;
		}

		// encontra amigo que esta mais distante do vertice 1
		int dist = amigos[0];
		for(int i=1; i<k; i++) {
			dist = (custo[ amigos[i] ] > custo[dist] ? amigos[i] : dist);
		}

		// executa o caminho e marca.
		memset(caminho, false, sizeof(caminho)); caminho[1] = true;
		do {
			caminho[dist] = true;
			dist = adj[dist].primeiro;
		} while(dist != 1);

		// adicionando os custos de ida de todos os vértices que tem um amigo
		// para qualquer vértice que faz parte do caminho  depois de visitar
		// um vertice, e adicionamos ao caminho também.
		int resposta = 0;
		for(int i=0; i<k; i++) {
			int aux = amigos[i];

			while(!caminho[aux]) {
				resposta += adj[aux].segundo;
				caminho[aux] = true;
				aux = adj[aux].primeiro;
			}
		}

		// imprimeiroe a resposta.
		printf("%d\n", resposta);
	}

	return 0;
}

// funcao que calcula o custo entre cada no u e o no 1
int func(int u){
	if(u == 1){
		return 0;
	}else if(custo[u]){
		return custo[u];
	}else {
		return custo[u] = func(adj[u].primeiro)+adj[u].segundo;
	}
}
