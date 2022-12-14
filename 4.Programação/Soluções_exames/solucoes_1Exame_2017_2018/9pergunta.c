#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct{
    char name[100];
    int number;
} student;

typedef struct no_str{
    int grade;
    student *ps;
    struct no_str *next;
}no_str;

void insert_tail(no_str **tail, no_str *new_node)
{
    no_str *aux = *tail;

    if ( aux == NULL )
    {
        *tail = new_node;
        new_node->next = *tail;
        return;
    }
    new_node->next = aux->next;
    aux->next = new_node;
    *tail = new_node;
}

no_str* create_node(int _number, int _grade, char _name[])
{
    no_str *new = NULL;

    new = (no_str*) malloc (sizeof(no_str));

    if ( new == NULL )
    {
        printf("Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    new->ps = (student *)malloc(sizeof(student));
    if ( new->ps == NULL )
    {
        printf("Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    strcpy(new->ps->name, _name);
    new->grade = _grade;
    new->ps->number = _number;
    return new;
}

void remove_nodes(no_str **tail)
{
    no_str *currNode = (*tail), *nextNode = currNode->next;
    int first = 1;

    if (*tail == NULL ) return;

    while ( currNode != (*tail) || first ) // could be also done with do{}while; 
    {
        if ( nextNode->grade < 10 )  // remove in the middle
        {
            currNode->next = nextNode->next;
            free(nextNode->ps);
            free(nextNode);
            if ( nextNode == *tail ) *tail = currNode;  // in case of removal of tail
            nextNode = currNode->next;
        }
        else                                            // advance pointers
        {
            currNode = nextNode;
            nextNode = nextNode->next;
            first = 0;
        }
    }
}

// tail should have the biggest element
// assuming that there is already one element in the list
void insert_sorted(no_str **tail, no_str *new_node)
{
    no_str *aux = (*tail)->next;
   
    if ( aux->grade > new_node->grade  ) {  // insert in head ?
        new_node->next = aux;
        (*tail)->next = new_node;
        return;
    }

    while ( aux != *tail && aux->next->grade < new_node->grade ) {
       aux = aux->next; 
    };

    new_node->next = aux->next;
    aux->next = new_node;
    if ( aux == *tail ) *tail = new_node;
}

void print_list(no_str *tail)
{
    no_str *aux = tail->next;
    while(aux != tail)
    {
        printf("%s - %d\n", aux->ps->name, aux->grade);
        aux = aux->next;
    }
    printf("%s - %d\n", aux->ps->name, aux->grade);
}

int main()
{
    no_str *node, *tail = NULL, *tail_sorted = NULL;

    node = create_node(39000, 5, "Joao");
    insert_tail(&tail,node);
    node = create_node(39001, 11, "Manel");
    insert_tail(&tail,node);
    node = create_node(39010, 12, "Francisco");
    insert_tail(&tail,node);
    node = create_node(39011, 7, "Luisao");
    insert_tail(&tail,node);
    node = create_node(40100, 19, "Catarina");
    insert_tail(&tail,node);
    node = create_node(40101, 18, "Cristina");
    insert_tail(&tail,node);
    node = create_node(9456, 8, "Celine");
    insert_tail(&tail,node);

    printf("All the students:\n");
    print_list(tail);

    printf("Removing all students with grades less than %d\n", 10);
    remove_nodes2(&tail);
    print_list(tail);

    node = create_node(39000, 5, "Joao");
    insert_tail(&tail_sorted,node);
    node = create_node(39001, 7, "Manel");
    insert_sorted3(&tail_sorted,node);
    node = create_node(39010, 12, "Francisco");
    insert_sorted3(&tail_sorted,node);
    node = create_node(39011, 16, "Luisao");
    insert_sorted3(&tail_sorted,node);
    node = create_node(40100, 2, "Catarina");
    insert_sorted3(&tail_sorted,node);
    node = create_node(40101, 18, "Cristina");
    insert_sorted3(&tail_sorted,node);
    node = create_node(9456, 19, "Celine");
    insert_sorted3(&tail_sorted,node);

    printf("All the students with some order:\n");
    print_list(tail_sorted);
}
