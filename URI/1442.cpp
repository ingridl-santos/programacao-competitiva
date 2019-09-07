#include <cstdio>
#include <cstdlib>
#include <vector>

#define MAXN 1000
#define MAXM 100000

using namespace std;

int n,m;
vector<int> adj[MAXN];//adj de G
vector<int> adj2[MAXN];//adj de G^t
vector<int> adj3[MAXN];//adj do Grafo das componentes

int sop[MAXN]; // sop[i] = Vértice com órdem de finalização i
int komp[MAXN]; // komp[i] = Componente do vértice i

int f, cnt, pontes;
int lbl[MAXN];

int pre[MAXN], low[MAXN], prnt[MAXN]; // 3ª dfs

//dfs que vai calcular os valores de finalização em G
void dfs1(int v){
	lbl[v] = 1;
	for(vector<int>::iterator i = adj[v].begin(); i != adj[v].end(); i++){
		int u = (*i);
		if(lbl[u] == -1)
			dfs1(u);
	}
	sop[f++] = v;
}

//Dfs que vai montar o garfo auxiliar das componentes fortemente conexas
void dfs2(int v, int comp){
	komp[v] = comp;
	for(vector<int>::iterator i = adj2[v].begin(); i != adj2[v].end(); i++)	{
		int u = (*i);
		if(komp[u] == -1){
			dfs2(u, comp);
		}	else if(komp[u] != komp[v]){
				adj3[komp[u]].push_back(komp[v]);
				adj3[komp[v]].push_back(komp[u]);
		}
	}
}

void dfs3(int v){
	int u;
	pre[v] = cnt++;
	low[v] = pre[v];
	for(vector<int>::iterator i = adj3[v].begin(); i != adj3[v].end(); i++)	{
		if(pre[u = (*i)] == -1){
			prnt[u] = v;
			dfs3(u);
			if(low[v] > low[u]){
				low[v] = low[u];
			}
			// Possivel ponte. Se não descobrimos nenhuma ponte até agora.Testamos.
			else if(low[u] == pre[u] && pontes == 0){
				//Vamos verificar se de fato esse arco é uma ponte é uma ponte.
				int q =0;
				for(vector<int>::iterator i = adj3[v].begin(); i != adj3[v].end(); i++){
					if((*i) == u) q++;
					if(q>1) break; // Arcos paralelos. Não é ponte
				}
				if(q == 1){
					pontes++;
				}
			}
		}
		else if(u != prnt[v] && low[v] > pre[u])
			low[v] = pre[u];
	}
}

int main(){
	int comp = 0;
	while(scanf("%d %d\n",&n,&m) != EOF){
		//Inicialização dos roles
		for(int i =0; i < n; i++){
					adj[i].clear();
					adj2[i].clear();
					adj3[i].clear();
					prnt[i] = pre[i] = low[i] = komp[i] = lbl[i] = sop[i] = -1;
					comp = pontes = f = 0;
				}
		// Lê as arestas
		for(int i = 0; i < m; i++){
			int a,b,t;
			scanf("%d %d %d\n",&a, &b, &t);
			if(!i) continue;
			a--;b--;
			adj[a].push_back(b);
			adj2[b].push_back(a);
			if(t == 2){
					adj[b].push_back(a);
					adj2[a].push_back(b);
				}
		}
		//Aplica a dfs em todo o Grafo G para
		//Calcular os tempos de finalizações.
		for(int i = 0; i < n; i++)
			if(lbl[i] == -1)
				dfs1(i);
		//Segunda dfs para calcular as componentes
		//fortemente Conexas
		for(int i =n-1; i >= 0; i--){
			if(komp[sop[i]] == -1)
				dfs2(sop[i], comp++);
		}
		//Se tiver só uma componente, já é
		//Tudo fortemente conexo e GG
		if(comp == 1){
			printf("-\n");
			continue;
		}
		//Vamos detectar se o grafo auxiliar
		//Das componentes fortemente conexas
		//Tem pontes
		cnt = 0;
		prnt[0] = 0; // Inicializo o vetor de pais.
		dfs3(0); //Começo de um vértice arbitrário.

		//Vamor verificar se o grafo das componentes é conexo.
		int j;
		for(j = 0; j < comp; j++)
			if(prnt[j] == -1) break;

		if(j < comp) // Desconexo
			printf("*\n");
		else if(pontes)
			printf("2\n");
		else
			printf("1\n");
}
	return 0;
}
