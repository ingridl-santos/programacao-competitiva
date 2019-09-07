#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <string>
#include <sstream>
#include <queue>

using namespace std;

int INT_MAX = 1000000;

// Representação da aresta
// Campos:
//      destino         -  denota o ultimo nó de uma aresta. Por exemplo, 'v' em u-->v
//      capacidade      -  a  capacidade maxima de uma aresta
//      fluxoResidual   -  a quantidade residual de fluxo que pode passar pela aresta
//      contAresta  -  um ponteiro para o contador de arestas no gráfico residual para otimização de desempenho
struct Aresta{
    int destino;
    int capacidade;
    int fluxoResidual;
    int custo;
    Aresta* contAresta;
};

// Representação do grafo
// Campos:
//      numVertices - denota o numero de vertices no grafo
//      adj         - Lista de adjacencias : coleção de listas não ordenadas uma para cada vértice
struct Grafo{
    int numVertices;
    vector<Aresta*> *adj;
};

Grafo g;
Grafo resGrafo;

// Gera uma nova aresta alocando espaço dinamicamente e retorna um apontado para a aresta
Aresta* genAresta(int destino, int capacidade, int fluxoResidual, int custo){
    Aresta* a1 = new Aresta;
    a1->destino = destino;
    a1->capacidade = capacity;
    a1->fluxoResidual = residualFlow;
    a1->custo = custo;
    return a1;
}

// Imprime todas as arestas no grafo
// Saida:
//      Lista de arestas onde cada aresta é representada por
//          u(nó inicial)   v(nó final)   fluxo   capacidade
int printGrafo(Grafo g){
    for(int i=0; i<g.numVertices; i++){
        for(int j=0; j<g.adj[i].size(); j++){
            cout << i+1 << " " << g.adj[i][j]->destino+1 << " " << (g.adj[i][j]->capacidade - g.adj[i][j]->fluxoResidual) << " " <<
            g.adj[i][j]->custo << endl;
        }
    }
    return 0;
}

int printParams(int verticeParente[], int distancia[]){
    cout << "Vertice Parente:\n";
    for(int i=0; i<g.numVertices; i++){
        cout << verticeParente[i] << " ";
    }
    cout << endl;
    cout << "Distancia do Vertice:\n";
    for(int i=0; i<g.numVertices; i++){
        cout << distancia[i] << " ";
    }
    cout << endl;
}

// Detecta a presença de ciclos negativos no grafo
// Saida:
//      -1          se não houver a presença de ciclos negativos
//      node_num    indice de um nó em ciclo negativo
// As listas verticeParente e arestaParente são atualizadas e podem ser usadas para reconstruir o ciclo negativo
int BFDetectaCiclo(Grafo resGrafo, int origem, int verticeParente[], Aresta* arestaParente[]){
    // Inicializa variaveis que serao necessarias
    int ciclo_no = -1;
    int numVertices = resGrafo.numVertices;
    vector<Aresta*> *adj = resGrafo.adj;
    int distancia[numVertices];
    // Inicializa visitado, parentVertex and distancia
    for(int i=0; i<numVertices; i++){
        verticeParente[i] = -1;
        distancia[i] = INT_MAX;
    }
    // BF - Relaxar as arestas repetidamente
    distancia[origem] = 0;
    for(int i=0; i<numVertices-1; i++){
        // loop em todas as arestas
        for(int u=0; u<numVertices; u++){
            for(int e=0; e<adj[u].size(); e++){
                if(adj[u][e]->fluxoResidual > 0){
                    int v = adj[u][e]->destino;
                    int w = adj[u][e]->custo;
                    if(distancia[v]>distancia[u]+w){
                        distancia[v] = distancia[u]+w;
                        verticeParente[v] = u;
                        arestaParente[v] = adj[u][e];
                    }
                }
            }
        }
    }
    // Verificar o ciclo de peso negativo - loop em todas as arestas
    for(int u=0; u<numVertices; u++){
        for(int e=0; e<adj[u].size(); e++){
            if(adj[u][e]->fluxoResidual > 0){
                int v = adj[u][e]->destino;
                int w = adj[u][e]->custo;
                if(distancia[v]>distancia[u]+w){
                    return v;       // Ciclo negativo detectado!
                }
            }
        }
    }
    return ciclo_no;
}

// Cancela todos os ciclos negativos
// Saida:
//      custoSalvo    quantidade de custo economizado por detecção e cancelamento de ciclo
int cancelaCicloNegativo(Grafo resGrafo){
    int custoSalvo=0, cicloPossivel=1, u, v;
    Aresta *ta1, *ta2;
    int numVertices = resGrafo.numVertices;
    while(cicloPossivel){
        cicloPossivel=0;
        for(int i=0; i<numVertices; i++){
            int parente[g.numVertices];
            Aresta* arestaParente[g.numVertices];
            int no_num = BFDetectaCiclo(resGrafo, i, parente, arestaParente);
            if(no_num!=-1){               // Um ciclo é detectado
                cicloPossivel=1;
                // Calcular o fluxo do caminho
                int fluxo_caminho = INT_MAX;
                v=no_num; u = parente[v]; ta1 = arestaParente[v];
                fluxo_caminho = min(fluxo_caminho, ta1->fluxoResidual);
                for (v=u; v!=no_num; v=parente[v]){
                    u = parente[v];
                    ta1 = arestaParente[v];
                    fluxo_caminho = min(fluxo_caminho, ta1->fluxoResidual);
                }
                // Atualizar gráfico removendo o ciclo
                v=no_num; u = parente[v];
                ta1 = arestaParente[v];
                ta2 = ta1->contAresta;
                ta1->fluxoResidual -= fluxo_caminho;
                ta2->fluxoResidual += fluxo_caminho;
                custoSalvo += fluxo_caminho*(ta1->custo);
                for (v=u; v != no_num; v=parente[v]){
                    u = parente[v];
                    ta1 = arestaParente[v];
                    ta2 = ta1->contAresta;
                    ta1->fluxoResidual -= fluxo_caminho;
                    ta2->fluxoResidual += fluxo_caminho;
                    custoSalvo += fluxo_caminho*(ta1->custo);
                }
            }
        }
    }
    return -1*custoSalvo;
}


// Localiza o caminho mais curto da origem para o destino
// Saida:
//      0           se o caminho não existe da origem ate o destino
//      1           se exister um caminho da origem ate o destino
// Lista verticeParente e arestaParente são atualizados e podem ser usados ​​para reconstruir o caminho mais curto
bool BF(Grafo resGrafo, int origem, int destino, int verticeParente[], Aresta* arestaParente[]){
    // Inicializa variaveis que serao necessarias
    int numVertices = resGrafo.numVertices;
    vector<Aresta*> *adj = resGrafo.adj;
    int distancia[numVertices];
    // Inicializa visitado, verticeParente e distancia
    for(int i=0; i<numVertices; i++){
        verticeParente[i] = -1;
        distancia[i] = INT_MAX;
    }
    // printParams(verticeParente, distancia);
    // BF
    distancia[origem] = 0;
    for(int i=0; i<numVertices-1; i++){
        // loop em todas as arestas
        for(int u=0; u<numVertices; u++){
            for(int e=0; e<adj[u].size(); e++){
                if(adj[u][e]->fluxoResidual > 0){
                    int v = adj[u][e]->destino;
                    int w = adj[u][e]->custo;
                    if(distancia[v]>distancia[u]+w){
                        distancia[v] = distancia[u]+w;
                        verticeParente[v] = u;
                        arestaParente[v] = adj[u][e];
                    }
                }
            }
        }
        // printParams(verticeParente, distancia);
    }
    if(verticeParente[destino] == -1){
        return false;
    }else{
        return true;
    }
}

// Calcula o custo do fluxo 'fluxoRequerido' de 's' para 't'
// Retorna 'INT_MAX' se um fluxo nao é possivel
int calcMinCostFlow(int s, int t, int fluxoRequerido){
    int u, v, currFlow=0, runningCost=0;
    Aresta *ta1, *ta2;
    // Detecta ciclos negativos e remove
    int benifit = cancelaCicloNegativo(resGrafo);
    if(benifit){
        cout << "Ciclo Negativo detectado e removido. Resultando em beneficios de custo de " << benifit << endl;
    }
    // Executar o aumento de caminho mais curto
    int parente[g.numVertices];
    Aresta* arestaParente[g.numVertices];
    while (BF(resGraph, s, t, parent, parentEdge)){
        int fluxo_caminho = INT_MAX;
        for (v=t; v!=s; v=parente[v]){
            u = parente[v];
            ta1 = arestaParente[v];
            fluxo_caminho = min(fluxo_caminho, ta1->fluxoResidual);
        }
        fluxo_caminho = min(fluxo_caminho, fluxoRequerido-currFlow);
        for (v=t; v != s; v=parente[v]){
            u = parente[v];
            ta1 = arestaParente[v];
            ta2 = ta1->contAresta;
            ta1->fluxoResidual -= fluxo_caminho;
            ta2->fluxoResidual += fluxo_caminho;
            runningCost += fluxo_caminho*(ta1->custo);
        }
        currFlow += fluxo_caminho;
        if(currFlow == fluxoRequerido){
            break;
        }
    }
    if(currFlow == fluxoRequerido){
        return runningCost;
    }else{
        return INT_MAX;
    }
}


int main(){
    int numVertices, numArestas,origem, destino, fluxo;
    int tu, tv, tcap, tcost, tflow;

    // Scannea as configurações de gráfico e pede
    cin >> numVertices >> numEdges;
    cin >> flow;
    cin >> source >> destination;
    source--; destination--;                // Como indexação começa de 0

    // Inicializa o grafo
    g.numVertices = numVertices;
    g.adj = new vector<Aresta*>[numVertices];
    resGrafo.numVertices = numVertices;
    resGrafo.adj = new vector<Aresta*>[numVertices];

    // Parâmetros de entrada do grafo
    for(int i=0; i<numEdges; i++){
        cin >>  tcap >> tcost >> tflow;
        tu--; tv--;                         // Como indexação começa de 0
        // Add  aresta ao grafo e aresta e contAresta ao grafo residual
        Aresta* tmpAresta1 = genAresta(tv, tcap,tcap-tflow, tcost);
        Aresta* tmpAresta2 = genAresta(tu, tcap, tflow, -1*tcost);
        tmpAresta1->contAresta = tmpAresta2;
        tmpAresta2->contAresta = tmpAresta1;
    }

    // Imprime estado inicial do grafo
    cout << "Grafo inicial:\n";
    printGrafo(g);

    // Executa algoritmo min-cost flow
    int mincost = calcMinCostFlow(origem, destino, fluxo);

    // Imprime estado final do grafo
    if(mincost == INT_MAX){
        cout << "IMPOSSIVEL!\n";
    }else{
        cout << "Instancia " << k << "\n" << mincost << endl;
        cout << "Grafo final:\n";
        printGrafo(g);
    }
    return 0;
}
