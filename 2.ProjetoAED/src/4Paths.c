#include "0Main.h"
// Função para encontrar o vértice na franja a menor distância da SPT
int minDistance(int dist[], bool sptSet[], int nv)
{
    //min é inicializado a infinito
    int min = INT_MAX, min_index = -1;
 
    for (int v = 0; v < nv; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
 
    return min_index;
}

// função para imprimir o sp da source para j, usando o parrent
void getPath(int parent[], int j, Path **path )
{
    Path *aux;

    // se j é a source (caso base)
    while(parent[j] != -1)
    {
        aux = (Path*)malloc(sizeof(Path));
        aux->next = *path;
        aux->n2 = j;
        *path = aux;
        j = parent[j];
    }
}

void printPath(Path *path, char **dictTabs)
{
    Path *aux = path;
    while(aux != NULL)
    {
        printf("%d: %s ", aux->n2, dictTabs[aux->n2]);
        aux = aux->next;

    }
    printf("\n");
}
 

void dijkstra(Problem *problem, int sn, int nv, int end, Edge **adjs)
{
    Edge *edge = NULL;

    // array de saída em que dist[i] guarda a menor distância da src a i
    int dist[nv];
 
    // sptSet[i] é true se o vértice i está incluído na spt
    bool sptSet[nv];
 
    // Relaciona a SPT
    int parent[nv];

    int v=0, u=0;
 
    // inicializa todas as distâncias a infinito e sptSet[] a false
    for (int i = 0; i < nv; i++)
    {
        parent[i] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
 
    // distância de src a src é 0 obviamente
    dist[sn] = 0;
 
    // ciclo para encontrar o caminho mais curto para todos os vértices
    for (int count = 0; count < nv-1; count++)
    {
        // escolher o vértice com menor distância do conjunto de vértices que ainda não foi processado. u= src na primeira iteração.
        u = minDistance(dist, sptSet, nv);
 
        // marcar o vértice escolhido como processado
        sptSet[u] = true;

        edge = adjs[u];
        //Veras adjacencias de u e actualizar o valor de dist ao vértice escolhido
        while (edge != NULL)
        {
            // Actualizar dist[v] se:
            //(1) não está em sptSet
            //(2) o custo total do caminho de src a v através de u é menor do que o valor actual de dist[v].
            
            v = edge->n2;
            
            if (sptSet[v])
            {
                edge = edge->next;
                continue;
            }
            
            if ((dist[u] + edge->wt) < dist[v])
            {
                parent[v] = u;
                dist[v] = dist[u] + edge->wt;
            }
            edge = edge->next;
        }

        if (u == end)
            break;
    }
    getPath(parent, end, &problem->path);
    problem->mode = dist[end];
    if (problem->mode == INT_MAX)
        problem->mode = -1;                
    
    return;
}

void makePaths(char *locationStats, int *dicLenCount, char ***dictTabs, int maxLen, Problem **tabs, int nPals, int* palsOrder)
{
    FILE *statsPointer = NULL;
    int i;
    Problem *temp, **aux;
    Path *aux2;
    statsPointer = (FILE *)fopen(locationStats, "w");
    fileCheck(statsPointer, locationStats);

    aux = (Problem **)calloc(maxLen, sizeof(Problem *));
    memoryCheck(aux);

    for (i = 0; i < maxLen; i++)
    {
        aux[i] = tabs[i];
    }

    for (i = 0; i < nPals; i++)
    {
        if (aux[palsOrder[i]] != NULL)
        {
            temp = aux[palsOrder[i]];
            fprintf(statsPointer, "%s %d\n", temp->word1, temp->mode);
            if (temp->mode != -1)
            {
                aux2 = temp->path;
                while (aux2 != NULL)
                {
                    fprintf(statsPointer, "%s\n", dictTabs[strlen(temp->word1)][aux2->n2]);
                    aux2 = aux2->next;
                }
                fprintf(statsPointer, "\n");
            }
            else
            {
                fprintf(statsPointer, "%s\n\n", temp->word2);
            }
        }
        aux[palsOrder[i]] = temp->previous;
    }

    free(aux);

    fclose(statsPointer);
}

int binarySearch(char **tabs, char *nome, int n)
{
    int lower = 0;
    int upper = n - 1;
    int mid = lower + (upper - lower) / 2;
    int res = 1;
    while (lower <= upper)
    {
        mid = lower + (upper - lower) / 2;
        if (strcmp(nome, (tabs[mid])) == 0)
            res = 0;
        if (res == 0)
            return mid;
        if (strcmp(nome, (tabs[mid])) > 0)
            lower = mid + 1;
        else
            upper = mid - 1;
    }
    return -1;
}


