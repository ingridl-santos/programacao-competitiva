#include <iostream>
#include <algorithm>

using namespace std;

typedef struct{
	int origem;
	int destino;
	int peso;
}aresta;

bool compara(aresta A, aresta B){
	return(A.peso < B.peso);
}

int verifica_ciclo(int p[], int origem, int destino){
	while(p[origem] > -1){
		origem = p[origem];
	}
	
	while(p[destino] > -1){
		destino = p[destino];
	}
	
	if(origem != destino){
		p[destino] = origem;
		
		return 1;
	}
	
	return 0;
}

int main(){
	
	int vertixAmount, edgeAmount;
	
	int p[200000]; aresta arestas[200000];
	
	while(cin >> vertixAmount >> edgeAmount){
		if(vertixAmount == 0 and edgeAmount == 0){
			return 0;
		}
		
		int custo = 0, custoTotal = 0;
		
		for(int i = 0; i < vertixAmount; i++){
			p[i] = -1;
		}
		
		for(int i = 0; i < edgeAmount; i++){
			cin >> arestas[i].origem >> arestas[i].destino >> arestas[i].peso;
			custoTotal += arestas[i].peso;
		}
		
		sort(arestas, arestas + edgeAmount, compara);
		
		int i = 0;
		int j = 1;
		
		while(j < vertixAmount and i < edgeAmount){
			if(verifica_ciclo(p, arestas[i].origem, arestas[i].destino)){
				j++;
				custo = custo + arestas[i].peso;
			}
			
			i++;
		}
		
		cout << custoTotal - custo << endl;
	}
	
	return 0;
}
