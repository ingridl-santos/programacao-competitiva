#include<iostream>

#define maxVert 10000 //maximo de vertices

using namespace std;

int cnt, lbl[maxVert], moves, cont = 0;
int V, A, G;
int adj[100][100];

void caminhoR(int v){
	
	int w;
	lbl[v] = cnt++;
	
	for(w = 0; w < V; w++){
		if(adj[v][w] == 1){
			if(lbl[w] == -1){
				moves++;
				caminhoR(w);
			}
		}
	}
}

void caminhoDigrafo(int origem){
	
	int v;
	
	for(v = 0; v < V; v++){
		lbl[v] = -1;
	}
	
	caminhoR(origem);
}

int main(void){
	
	int orig, dest, N, casos, origem;
	
	cin >> casos;
	
	while(casos--){
		cin >> origem;
		cin >> V; //vertices
		
		//zera matriz de adjacencia
		for(int i = 0; i < V; i++){
			for(int j = 0; j < V; j++){
				adj[i][j] = 0;
			}
		}
		
		moves = 0;
		cin >> A; //arestas
		
		for(int i = 0; i < A; i++){
			cin >> orig >> dest;
			adj[orig][dest] = 1;
			adj[dest][orig] = 1;
			//se o grafo nao for digrafo seta para ambas as direcoes
		}
		
		caminhoDigrafo(origem);
		cout << moves*2 << endl;
	}
	
	return 0;
}
