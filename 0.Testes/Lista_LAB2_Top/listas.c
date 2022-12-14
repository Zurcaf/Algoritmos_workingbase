#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct
{
    int terminal;
    struct node* next;
} node;


int main ()
{
    int id[] = {1, 9, 1, 2, 2, 8, 9, 2, 4, 4 };
    int N = 10;

    int i = 0;
    int id_temp = 0;
    int bags_numb = 0;

    node* bags[N];
    for (i = 0; i < N; i++)
    {
        bags[i] = NULL;
    }

    for (i = 0; i < N; i++)
    {
        node *temp = (node *)malloc(sizeof(node));
        temp->terminal = i;
        temp->next = NULL;

        id_temp = id[i];

        if (bags[id_temp] == NULL)
        {
            bags[id_temp] = temp;
        }
        else
        {
            temp->next = bags[id_temp];
            bags[id_temp] = temp;
        }
    }

    for (i = 0; i < N; i++)
    {
        node *temp = bags[i];

        if (temp != NULL)
        {
            bags_numb++;
            while (temp != NULL)
            {
                printf(" %d ", temp->terminal);
                temp = temp->next;
                if (temp != NULL)
                    printf("-");
            }
            printf("\n");
        }
    }
    printf ("Existem %d grupos.\n", bags_numb);

}

