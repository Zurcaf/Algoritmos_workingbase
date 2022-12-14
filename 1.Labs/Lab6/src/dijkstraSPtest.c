
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
 

 
// Função para encontrar o vértice a menor distância do conjunto de vértices que não estão na SPT
int minDistance(int dist[], bool sptSet[])
{
    // inicializar a infinito as distâncias do vértices que não estão incluídos na spt
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
 
    return min_index;
}

// função para imprimir o sp da source para j, usando o parrent
void printPath(int parent[], int j)
{
    // se j é a source (caso base)
    if (parent[j]==-1)
        return;
 
    printPath(parent, parent[j]);
 
    printf("%d ", j);
}
 
// função para imprimir o array com as distâncias
int printSolution(int dist[], int n, int parent[])
{
    int src = 0;
    printf("Vertex\t  Distance\tPath");
    for (int i = 1; i < V; i++)
    {
        printf("\n%d -> %d \t\t %d\t\t%d ", src, i, dist[i], src);
        printPath(parent, i);
    }
}
 

void dijkstra(int graph[V][V], int src)
{
    // array de saída" em que dist[i] guarda a menor distância da src a i
    int dist[V];  
 
    // sptSet[i] é true se o vértice i está incluído na spt
    bool sptSet[V];
 
    // guarda a spt
    int parent[V];
 
    // inicializa todas as distâncias a infinito e sptSet[] a false
    for (int i = 0; i < V; i++)
    {
        parent[0] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
 
    // distância de src a src é 0 obviamente
    dist[src] = 0;
 
    // ciclo para encontrar o caminho mais curto para todos os vértices
    for (int count = 0; count < V-1; count++)
    {
        // escolher o vértice com menor distância do conjunto de vértices que ainda não foi processado. u= src na primeira iteração.
        int u = minDistance(dist, sptSet);
 
        // marcar o vértice escolhido como processado
        sptSet[u] = true;
 
        // actualizar o valor de dist dos vértices adjacentes ao vértice escolhido
        for (int v = 0; v < V; v++)
 
            // Actualizar dist[v] se: 
            //(1) não está em sptSet
            //(2) Há um aresta u-v 
            //(3) o custo total do caminho de src a v através de u é menor do que o valor actual de dist[v].
            if (!sptSet[v] && graph[u][v] &&
                dist[u] + graph[u][v] < dist[v])
            {
                parent[v]  = u;
                dist[v] = dist[u] + graph[u][v];
            }  
    }
 
    // imprimir resultados
    printSolution(dist, V, parent);
}
 
