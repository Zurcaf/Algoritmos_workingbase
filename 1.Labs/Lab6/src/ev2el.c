/******************************************************************************
 * (c) 2022 AED Team
 * Last modified: lms 2022-10-20
 *
 * NAME
 *   ev2el
 *
 * DESCRIPTION
 *   Main program for lab guide
 *   - read edge vector,
 *   - write edge lists
 *
 * COMMENTS
 *   Code for internal testing - do not distribute
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#include "LinkedList.h"
#include "queue.h"





typedef struct _twint
{
  int n2;
  int wt;
} twint;

typedef struct _nodeS
{
  int node;
  
  /* could add additional information here */
} NodeS;

int minDistance(int *dist, bool *sptSet, int nv);
void printPath(int *parent, int j);
int printSolution(int dist[], int nv, int parent[]);
void dijkstra(struct _twint twint, int sn, int nv, LinkedList **listv);

void freeEntryItem(Item item)
{
  free(item);
    return;       /* no mem actually allocated */
}

void freeEntryItemQueue(Item item)
{
    return;       /* no mem actually allocated */
}

/******************************************************************************
 * usage ()
 *
 * Arguments: nomeProg - name of executable
 * Returns: (void)
 * Side-Effects: none
 *
 * Description: message function when arguments are missing
 *****************************************************************************/

void usage(char *nomeProg)
{
  printf("Usage: %s filename\n", nomeProg);
  printf("  reads graph edges vector, writes edge lists\n");
  exit(1);
}

/******************************************************************************
 * memoryError ()
 *
 * Arguments: msg - message to output to stderr
 * Returns: (void)
 * Side-Effects: none
 *
 * Description: exit with error message to stderr
 *****************************************************************************/

void memoryError(char *msg)
{

  fprintf(stderr, "Error during memory reserve attempt.\n");
  fprintf(stderr, "Msg: %s\n", msg);
  fprintf(stderr, "Exit Program due to unmanaged error.\n");

  exit(1);
}


// Função para encontrar o vértice a menor distância do conjunto de vértices que não estão na SPT
int minDistance(int dist[], bool sptSet[], int nv)
{
    // inicializar a infinito as distâncias do vértices que não estão incluídos na spt
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < nv; v++)
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
int printSolution(int dist[], int nv, int parent[])
{
    int sn = 0;
    printf("Vertex\t  Distance\tPath");
    for (int i = 1; i < nv; i++)
    {
        printf("\n%d -> %d \t\t %d\t\t%d ", sn, i, dist[i], sn);
        printPath(parent, i);
    }
}
 

void dijkstra(struct _twint twint, int sn, int nv, LinkedList **listv)
{
    // array de saída" em que dist[i] guarda a menor distância da src a i
    int dist[nv];  
 
    // sptSet[i] é true se o vértice i está incluído na spt
    bool sptSet[nv];
 
    // guarda a spt
    int parent[nv];
 
    // inicializa todas as distâncias a infinito e sptSet[] a false
    for (int i = 0; i < nv; i++)
    {
        parent[0] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
 
    // distância de src a src é 0 obviamente
    dist[sn] = 0;
 
    // ciclo para encontrar o caminho mais curto para todos os vértices
    for (int count = 0; count < nv-1; count++)
    {
        // escolher o vértice com menor distância do conjunto de vértices que ainda não foi processado. u= src na primeira iteração.
        int u = minDistance(dist, sptSet, nv);
 
        // marcar o vértice escolhido como processado
        sptSet[u] = true;
 
        // actualizar o valor de dist dos vértices adjacentes ao vértice escolhido
        for (int v = 0; v < nv; v++)
 
            // Actualizar dist[v] se: 
            //(1) não está em sptSet
            //(2) Há uma aresta u-v 
            //(3) o custo total do caminho de src a v através de u é menor do que o valor actual de dist[v].
            while (listv[u]->next)
            
            if (!sptSet[v] && twint->n2 &&
                dist[u] + twint.wt < dist[v])
            {
                parent[v]  = u;
                dist[v] = dist[u] + twint.wt;
            }  
    }
 
    // imprimir resultados
    printSolution(dist, nv, parent);
}

/******************************************************************************
 * doBFS ()
 *
 * Arguments: listv - data structure for graph list of adjacencies
 *            sn - starting node
 *            nv - number of nodes in graph
 * Returns: (void)
 * Side-Effects: none
 *
 * Description: does a BFS on the graph described by the list of adjacencies
 *              reachable through listv and prints nodes as it finds them
 *****************************************************************************/ 

void doBFS(LinkedList **listv, int sn, int nv)
{
  int numInqueue = 0, ni;
  int *inqueue;
  NodeS *fakeNodes, *Ns;
  LinkedList *lp;
  twint *pint;
  Queue *BFSqueue;

  inqueue = (int *)malloc(nv * sizeof(int));
  if (inqueue == ((int *)NULL))
    memoryError("Cannot allocate memory for inqueue nodes.");
  for (ni = 0; ni < nv; ni++)
    inqueue[ni] = 0;

  fakeNodes = (NodeS *)malloc(nv * sizeof(NodeS));
  if (fakeNodes == ((NodeS *)NULL))
    memoryError("Cannot allocate memory for fake nodes.");
  for (ni = 0; ni < nv; ni++)
    fakeNodes[ni].node = ni;

  BFSqueue = newQueue(nv);

  /* put starting node in queue */
  insertQueue(BFSqueue, (Item)&fakeNodes[sn]);
  inqueue[sn] = 1;
  fprintf(stdout, "%d ", sn);
  numInqueue++;
  for (; numInqueue < nv;)
  {
    /* get first element in queue, tells us node being visited */
    Ns = getfirstQueue(BFSqueue); /* -----------  COMPLETE --------------- */
    if (Ns == ((NodeS *)NULL))
      break;
    /* process that node's adjacency list */
    lp = listv[Ns->node]; /* -----------  COMPLETE --------------- */
    while (lp != NULL)
    {
      /* for every element in the adjacency list */
      /* check if it has been queued; if not, put it in the queue */
      /* and print it to stdout */
      pint = (twint *)getItemLinkedList(lp); /* -----------  COMPLETE --------------- */
      if (inqueue[pint->n2] == 0)
      {
        insertQueue(BFSqueue, (Item)&fakeNodes[pint->n2]);
        inqueue[pint->n2] = 1;
        fprintf(stdout, "%d ", pint->n2);
        numInqueue++;
      }
      lp = getNextNodeLinkedList(lp);
    }
  }
  fprintf(stdout, "\n");

  free(inqueue);
  free(fakeNodes);
  freeQueue(BFSqueue, freeEntryItemQueue);

  return;
}

/******************************************************************************
 * main ()
 *
 * Arguments: argc - number of command-line arguments
 *            argv - table of pointers for string arguments
 * Returns: int status
 * Side-Effects: none
 *
 * Description: main Program
 *****************************************************************************/

int main(int argc, char *argv[])
{
  int i, k;
  int nv, ne; /* V and E counts */
  int n1, n2, wt;
  int sn;
  char extIn[] = ".edge";
  char extOut[] = ".ladj";
  char *nomeFicheiroIn, *nomeFicheiroOut;
  twint *pint1, *pint2;

  LinkedList **listv, *lp;
  FILE *fpIn, *fpOut;

  if (argc < 2)
    usage(argv[0]);

  nomeFicheiroIn = argv[1];

  nomeFicheiroOut =
      (char *)malloc((strlen(nomeFicheiroIn) - strlen(extIn) + strlen(extOut) + 1) *
                     sizeof(char));
  if (nomeFicheiroOut == NULL)
    memoryError("Memory allocation for nomeFicheiroOut in main");

  strcpy(nomeFicheiroOut, nomeFicheiroIn);
  nomeFicheiroOut[strlen(nomeFicheiroIn) - strlen(extIn)] = '\0';
  strcat(nomeFicheiroOut, extOut);

  /* open input file */
  fpIn = fopen(nomeFicheiroIn, "r");
  if (fpIn == NULL)
  {
    printf("ERROR cannot read input file %s\n", nomeFicheiroIn);
    exit(2);
  }

  /* read input file, read nv and ne */
  k = fscanf(fpIn, "%d", &nv);
  if (k < 1)
  {
    printf("ERROR cannot read V number from input file %s\n",
           nomeFicheiroIn);
    exit(2);
  }
  k = fscanf(fpIn, "%d", &ne);
  if (k < 1)
  {
    printf("ERROR cannot read E number from input file %s\n",
           nomeFicheiroIn);
    exit(2);
  }

  /* create vector for adjacency lists, one per node */
  listv = (LinkedList **)calloc(nv, sizeof(LinkedList *));
  if (listv == ((LinkedList **)NULL))
    memoryError("memory allocation for adjacency lists vector in main");

  /* read ne edges from file, each triple n1, n2, weight */
  for (i = 0; i < ne; i++)
  {
    k = fscanf(fpIn, "%d %d %d", &n1, &n2, &wt);
    if (k < 3)
    {
      printf("ERROR cannot read edge triple from input file %s\n",
             nomeFicheiroIn);
      exit(2);
    }
    /*  DEBUG
        printf("%d %d %d\n", n1, n2, wt); */
    pint1 = (twint *)malloc(sizeof(twint));
    if (pint1 == ((twint *)NULL))
    {
      memoryError("memory allocation for edge structure in main");
    }
    pint2 = (twint *)malloc(sizeof(twint));
    if (pint2 == ((twint *)NULL))
    {
      memoryError("memory allocation for edge structure in main");
    }
    pint1->n2 = n2;
    pint1->wt = wt;
    pint2->n2 = n1;
    pint2->wt = wt;
    if (listv[n1] == NULL)
    {
      listv[n1] = initLinkedList();
    }
    if (listv[n2] == NULL)
    {
      listv[n2] = initLinkedList();
    }

    /*********** INSERT EDGE STRUCTURES IN EACH APPROPRIATE LIST ***********/
    listv[n1] = insertUnsortedLinkedList(listv[n1], (Item)pint1);
    listv[n2] = insertUnsortedLinkedList(listv[n2], (Item)pint2);

  }

  /* Compute de degree of every nome and the average edge density */
  int degree = 0;
  for (i = 0; i < nv; i++)
  {
    degree = 0;
    lp = listv[i];
    while (lp != NULL)
    {
      degree++;
      lp = getNextNodeLinkedList(lp);
    }
    fprintf(stdout, "Degree of node %d is %d\n", i, degree);
  }
  fprintf(stdout, "Average edge density is %f\n", ((float)(ne*2) / (float)nv));
  /* -----------  COMPLETE --------------- */

  /* open output file */
  fpOut = fopen(nomeFicheiroOut, "w");
  if (fpOut == NULL)
  {
    printf("ERROR cannot write output file %s\n", nomeFicheiroOut);
    exit(3);
  }

  /*  print out edge vectors (.ldaj file) */
  fprintf(fpOut, "%d\n", nv);
  for (i = 0; i < nv; i++)
  {
    lp = listv[i];
    while (lp != NULL)
    {
      pint1 = (twint *)getItemLinkedList(lp);
      lp = getNextNodeLinkedList(lp);
      /* print the node and the respective weight */
      /* -----------  COMPLETE --------------- */
      fprintf(fpOut, " %d:%d", pint1->n2, pint1->wt);
    }
    fprintf(fpOut, " -1\n");
  }

  /* -- close all open files -- */
  fclose(fpIn);
  fclose(fpOut);

  /****************** read path to find ************************************/
  fprintf(stdout,
          "Input node number to do a BFS from that node: ");
  fscanf(stdin, "%d", &sn);
  fprintf(stdout, "\n");
  if (sn >= nv)
  {
    fprintf(stderr,
            "node number outside of range of nodes in graph. Exiting.\n");
    exit(1);
  }

  /************ add code to do a BFS in graph from node en to node sn *********/
  doBFS(listv, sn, nv);

  /* -- free any memory you have allocated -- */
  for(i = 0; i < nv; i++)
  {
    freeLinkedList(listv[i], freeEntryItem);
  }
  free(listv);
  free(nomeFicheiroOut);

  exit(0);
}
