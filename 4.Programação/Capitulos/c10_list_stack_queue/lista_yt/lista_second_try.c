#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct node *next;
};

struct Node* head;

void inserir_lista(int x)
{
    Node* temp = (Node*) malloc(sizeof(struc Node));

}

imprimir_lista()
{

}

int main()
{
head = NULL;  //lista vazia
printf("Quantos numeros temn a lista?: ");
int n, i, x;
scanf("%d", &n);
for (i=0; i<n; i++)
{
    printf("Inserir numero: ");
    scanf("%d", &x);
    inserir_lista(x);
    imprimir_lista();
}

}