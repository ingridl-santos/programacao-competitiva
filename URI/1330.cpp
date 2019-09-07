#include <iostream>
#include <string.h>

#define N 110

using namespace std;

struct no{
  int x;
  int y;
}land[51];

int hashT[N][N], a[N][N];
int Map[N][N], v[N], mark[N];

int n, m, cnt;

int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};

//funcao que recebe os dados de entrada do mapa e identifica onde estao os lagos
//e as terras disponiveis para serem unidas ou nao para venda.
void recebeMapa(){

  int i, j, k, x, y;

  cin >> k;
  memset(hashT, 0, sizeof(hashT));

  while(k--){
    cin >> x >> y;
    hashT[x][y] = 1;
  }

  cnt = 1;

  for (i = 1; i <= n; i++) {
    for(j = 1; j <= m; j++){
      if(hashT[i][j] == 0){
        a[i][j] = cnt;
        land[cnt].x = i;
        land[cnt].y = j;
        cnt++;
      }
    }
  }

  memset(Map,0,sizeof(Map));

  for(i = 1; i <= n; i++){
    for(j = 1; j <= m; j++){
      if(hashT[i][j] == 0){
        for(k = 0; k < 4; k++){
          x = i+dx[k];
          y = j+dy[k];
          if(x >= 1 && x <= n && y >= 1  && y <=m && hashT[x][y] == 0){
            Map[a[i][j]][a[x][y]] = 1;
            Map[a[x][y]][a[i][j]] = 1;
          }
        }
      }
    }
  }
}

//funcoa que emprega o algoritmo de busca em profundidade para percorrer todos os espacos da terra e
//determinar quantos pares de terra podem ser formados
int dfs(int k){

  for(int i = 1; i < cnt; i ++){
    if((land[i].x + land[i].y) % 2 == 1){
      continue;
    }
    if(Map[k][i] && !v[i]){
      v[i] = 1;
      if(mark[i] == -1 || dfs(mark[i])){
        mark[i] = k;
        return 1;
      }
    }
  }

  return 0;
}

//funcao que retorna a combinacao de terras para venda. (x,y) -- (x,y).
/*void saida(){

  for(int i = 1; i < cnt; i++){
    if(mark[i] != -1){
      printf("(%d,%d) -- (%d,%d)\n", land[i].x, land[i].y, land[mark[i]].x,
      land[mark[i]].y);
    }
  }
}*/

//funcao que chama as funcoes anteriores para solucionar o problema geral e
//retorna a saida final desejada de quantas terras sao possiveis vender.
void soluciona(){

  int count = 0;

  memset(mark, -1, sizeof(mark));

  for(int i = 1; i < cnt; i++){
    if((land[i].x+land[i].y) % 2 == 0){
      continue;
    }
    memset(v, 0, sizeof(v));

    if(dfs(i)){
      count++;
    }
  }
  cout << count << endl;
  //saida();
}

int main(int argc, char const *argv[]) {

    while (scanf("%d%d",&n, &m)!= -1){
      if(!n && !m){
        break;
      }
      recebeMapa();
      soluciona();
    }
  return 0;
}
