#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 100

typedef struct no_line {
    int line;
    struct no_line *next;
}no_line;

typedef struct no_word{
    char word[MAX_STRING];
    struct no_word *next;
    struct no_word *prev;
    no_line *hline;
} no_word;

no_word* insertHead(no_word *head, char *word){
    no_word* new_node = NULL;

    new_node = (no_word*)calloc(1, sizeof(no_word));
    if ( new_node == NULL ){
        printf("Memory alloc error !");
        exit(EXIT_FAILURE);
    }
    strcpy(new_node->word, word);
    if ( head == NULL ){
        return new_node;
    }
    new_node->next = head;
    head->prev = new_node;
    return new_node;
}

void printList(no_word *head){
    no_word *aux = head;
    no_line *tmp = NULL;

    while (aux != NULL){
        printf("%s: ", aux->word);
        tmp = aux->hline;
        while ( tmp != NULL ) {
            printf(" %d ", tmp->line);
            tmp = tmp->next;
        }
        aux = aux->next;
        printf("\n");
    }
}

no_word* swap_nodes(no_word *head, no_word *node1, no_word *node2) {
    no_word *tmp1, *tmp2;

    tmp1 = node1->prev;
    tmp2 = node1->next;

    if ( tmp1 != NULL ) tmp1->next = node2;
    if ( tmp2 != NULL ) tmp2->prev = node2;

    node1->prev = node2->prev;
    node1->next = node2->next;

    if ( node2->prev != NULL ) node2->prev->next = node1;
    if ( node2->next != NULL ) node2->next->prev = node1;

    node2->prev = tmp1;
    node2->next = tmp2;

    if (head == node1) return node2;
    if (head == node2) return node1;
    return head;
}

void remove_nodes(no_word **head) {
    no_word *tmp1 = *head, *aux1 = NULL;
    no_line *tmp2 = NULL, *aux2 = NULL;

    while ( tmp1 != NULL ){
        tmp2 = tmp1->hline;
        while ( tmp2 != NULL ) {
            aux2 = tmp2->next;
            free(tmp2);
            tmp2 = aux2;
        }
        aux1 = tmp1->next;
        free(tmp1); 
        tmp1 = aux1;
    }
    *head = NULL;
}

no_word* insert(no_word *head, char wrd[], int nline ) {
    no_word *aux = head;
    no_line *tmp = NULL;

    while ( aux != NULL ){
        if ( strcmp(aux->word, wrd) == 0 ) {
            tmp = aux->hline;
            while ( tmp->next != NULL ){
                tmp = tmp->next;
            }
            tmp->next = (no_line*) malloc(sizeof(no_line));
            tmp->next->line = nline;
            tmp->next->next = NULL;
            return head;
        }
        aux = aux->next;
    }
    aux = (no_word *) malloc(sizeof(no_word));
    strcpy(aux->word, wrd);
    aux->hline = (no_line *) malloc(sizeof(no_line));
    aux->hline->line = nline;
    aux->hline->next = NULL;
    aux->next = NULL;
    aux->prev = NULL;
    if ( head == NULL ) {
        return aux;
    }
    aux->next = head;
    head->prev = aux;
    return aux;
}

int main (void)
{
    no_word *head = NULL, *head1 = NULL;

    head = insertHead(head, "Exame");
    head = insertHead(head, "Progr");
    head = insertHead(head, "3/07/2019");
    head = insertHead(head, "facil");
    head = insertHead(head, "19valores");

    printList(head);

    printf("........\n");
    head = swap_nodes(head, head, head->next->next); //dummy examples
    printList(head);
    head1 = insert(head1, "Exame", 1);
    head1 = insert(head1, "Progr", 15);
    head1 = insert(head1, "Exame", 5);
    head1 = insert(head1, "Progr", 34);
    printList(head1);

    remove_nodes(&head1);
    remove_nodes(&head);

    return EXIT_SUCCESS;
}
