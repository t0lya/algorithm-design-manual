#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
struct Node
{
    int data;
    struct Node *next;
};

void reverse(Node **head)
{
    if (head == NULL || *head == NULL || (*head)->next == NULL)
    {
        return;
    }

    Node *prev, *curr, *next;
    prev = NULL;
    curr = *head;
    next = NULL;
    while (curr)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    *head = prev;
}

int main()
{
    Node *first, *second, *third;
    first = malloc(sizeof(Node));
    second = malloc(sizeof(Node));
    third = malloc(sizeof(Node));
    first->data = 1;
    first->next = second;
    second->data = 2;
    second->next = third;
    third->data = 3;
    third->next = NULL;

    Node **head = &first;
    reverse(head);

    Node *next;
    for (Node *p = *head; p != NULL; p = next)
    {
        printf("%d\n", p->data);
        next = p->next;
        free(p);
    }

    return 0;
}
