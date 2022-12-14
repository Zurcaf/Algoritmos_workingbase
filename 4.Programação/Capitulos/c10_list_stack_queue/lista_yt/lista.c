#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int data;
    struct node *next;
}node;

void insert(int x, node **head);
void print(node *head);

int main()
{
    node *head = NULL;
    printf("how many numbers? ");
    int n, i, x;

    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("Enter the number \n");
        scanf("%d", &x);
        insert(x, &head);
        print(head);
    }
}

void insert(int x, node **head)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->data = x;
    temp->next = NULL;
    if (*head != NULL)
        temp->next = *head;
    *head = temp;
}

void print(node *head)
{
    node* temp = head;
    printf("List is: ");
    while (temp != NULL)
    {
        printf(" %d", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
