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
    // se j é a source (caso base)
    if ((parent[j]) == -1)
        return;

    getPath(parent, parent[j], path);

    *path = (Path*) calloc(1, sizeof(Path));
    memoryCheck(*path);
    (*path)->n2 = j;
    (*path)->next = NULL;
      
}
 

void dijkstra(Problem *palsTab, int sn, int nv, int end, Edge **adjs)
{
    Edge *edge;

    // array de saída em que dist[i] guarda a menor distância da src a i
    int dist[nv];
 
    // sptSet[i] é true se o vértice i está incluído na spt
    bool sptSet[nv];
 
    // Relaciona a SPT
    int parent[nv];
 
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
        int v;
        // escolher o vértice com menor distância do conjunto de vértices que ainda não foi processado. u= src na primeira iteração.
        int u = minDistance(dist, sptSet, nv);
        
        if (u == end)
        {
            getPath(parent, end, &palsTab->path);
            palsTab->pathDist = dist[end];
            return;
        }
 
        // marcar o vértice escolhido como processado
        sptSet[u] = true;

        //Veras adjacencias de u e actualizar o valor de dist ao vértice escolhido
        while (adjs[u] != NULL)
        {
            // Actualizar dist[v] se:
            //(1) não está em sptSet
            //(2) o custo total do caminho de src a v através de u é menor do que o valor actual de dist[v].
            v = adjs[u]->n2;
            edge = adjs[u];

            if (sptSet[v])
            {
                adjs[u] = adjs[u]->next;
                continue;
            }
            
            if ((dist[u] + edge->wt) < dist[v])
            {
                parent[v] = u;
                dist[v] = dist[u] + edge->wt;
            }
            adjs[u] = adjs[u]->next;
        }
    }
}

void makePaths(char *locationStats, int *lenCount, char ***tabs, char *locationPals, int lenMax)
{
    FILE *palsPointer = NULL, *statsPointer = NULL;
    char word1[WORD_LEN_MAX], word2[WORD_LEN_MAX]; // buffer para a palavra
    int mode = 0, bsResult1 = -2, bsResult2 = -2;

    for (int i = 0; i < WORD_LEN_MAX; i++)
    {
        word1[i] = '\0';
        word2[i] = '\0';
    }

    // abrir o ficheiro e verificar se foi aberto com sucesso
    palsPointer = (FILE *)fopen(locationPals, "r");
    fileCheck(palsPointer, locationPals);

    statsPointer = (FILE *)fopen(locationStats, "w");
    fileCheck(statsPointer, locationStats);

    // scan dos problemas e escrita da resposta em . pals.stats
    while (fscanf(palsPointer, "%s %s %d", word1, word2, &mode) == 3)
    {
        if (strlen(word1) != strlen(word2) || strlen(word1) > (lenMax) || strlen(word2) > (lenMax))
        {
            fprintf(statsPointer, "%s %s %d \n \n", word1, word2, mode);
            continue;
        }

        bsResult1 = binarySearch(tabs[strlen(word1)], word1, lenCount[strlen(word1)]);
        bsResult2 = binarySearch(tabs[strlen(word2)], word2, lenCount[strlen(word2)]);

        if (bsResult1 == -1 || bsResult2 == -1)
        {
            fprintf(statsPointer, "%s %s %d \n \n", word1, word2, mode);
            continue;
        }

        switch (mode)
        {
        case 1:
            fprintf(statsPointer, "%s %d\n\n", word1, lenCount[strlen(word1)]);
            break;
        case 2:
            fprintf(statsPointer, "%s %d \n%s %d \n\n", word1, bsResult1, word2, bsResult2);
            break;
        default:
            fprintf(statsPointer, "%s %s %d\n\n", word1, word2, mode);
            break;
        }
    }
    fclose(statsPointer);
    fclose(palsPointer);
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


