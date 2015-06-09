#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node NODE;

struct node
{
    int info;
    NODE* next;
};

NODE* create_node(int info)
{
    NODE *new;

    new = (NODE*) malloc(sizeof(NODE));

    assert(new != NULL);

    new->info = info;
    new->next != NULL;
    return new;
}

void insert_at_begin(NODE **front, int info)
{
    NODE *nn; 

    nn = create_node(info);

    if(*front == NULL)
    { // if list is containing nothing make it as
     // first element.
        *front = nn;
	return;
    }
    nn->next = *front;
    *front = nn;
}

void insert_at_end(NODE **front, int info)
{
    NODE *nn, *tmp;

    nn = create_node(info);

    if(*front == NULL)
    { // if list is containing nothing make it as
     // first element.
        *front = nn;
	return;
    }

    tmp = *front;
    // traverse till end of the list
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = nn;
}

void insert_at_any_pos(NODE **front, int info, int pos)
{
    NODE *nn, *nxt, *prv;
    int i=0;

    if(pos < 1)
    {
        puts("zero or -ve pos not allowed");
	return;
    }

    nn = create_node(info);

    if( *front==NULL && pos==1)
    {
        *front = nn;
	return;
    }

    if(pos == 1)
    {
	nn->next = *front;
	*front = nn;
	return;
    }

    nxt = *front;
    while(i < pos-1)
    {
        prv = nxt;
	if(nxt == NULL)
	{
	    puts("Beyond the list position");
	    free(nn);
	    nn = NULL;
	    return;
	}
	nxt = nxt->next;
        ++i;
    }
    prv->next = nn;
    nn->next = nxt; 
}

void delete_at_begin(NODE **front)
{
    NODE *tmp;

    if( *front == NULL)
    {
        puts("List empty, Nothing to delete");
	return;
    }

    // when list had only one element
    if( (*front)->next == NULL )
    {
        free(*front);  // To avoid memory leak
	*front = NULL; // TO avoid dangling pointer
	return;
    }

    tmp = *front;
    (*front) = (*front)->next;

    free(tmp);
    tmp = NULL;
}

void delete_at_end(NODE **front)
{
    NODE *cur, *prv=NULL;

    if( *front == NULL)
    {
        puts("List empty, Nothing to delete");
	return;
    }

    // when list had only one element
    if( (*front)->next == NULL )
    {
        free(*front);  // To avoid memory leak
	*front = NULL; // TO avoid dangling pointer
	return;
    }

    // Traverse till end and delete the element
    cur = *front;
    while( cur->next != NULL)
    {
        prv = cur;
	cur = cur->next;
    }
    prv->next = NULL;  // break the link to the last node

    free(cur);
    cur = NULL;
}

void search(NODE *front, int key)
{
    NODE *tmp;

    for( tmp = front; tmp != NULL; tmp = tmp->next)
    {
        if(tmp->info == key)
	{
	    puts("Item found, Search Succesfull");
	    return;
        }
    }
    puts("Item NOT found");
}

void reverse_nrec(NODE **front)
{
    NODE *prv = NULL, *cur, *nxt; //initalize prv pointer to NULL
                                 // To avoid the SLL first node problem
    cur = *front;

    while(cur != NULL)
    {
        nxt = cur->next;   // hold the next node address in nxt 
	cur->next = prv;   // lets point this node to it's previous
	prv = cur;         // change the prv to cur
	cur = nxt;         // change the cur to nxt, to process in next iter
    }
    *front = prv;
}

void display(NODE *front)
{
    while(front != NULL)
    {
        printf(" %d -> ",(front)->info);
	(front) = (front)->next;
    }
    puts("NULL");
}

int main()
{
    NODE *front = NULL;

    display(front);  // List is empty

    insert_at_any_pos(&front, 23, 1);
    display(front);

    insert_at_any_pos(&front, 34, 2);
    display(front);

    insert_at_any_pos(&front, 45, 1);
    display(front);

#if 0
    insert_at_begin(&front, 12);
    display(front);

    insert_at_begin(&front, 23);
    display(front);

    insert_at_begin(&front, 34);
    display(front);

    insert_at_end(&front, 45);
    display(front);

    insert_at_end(&front, 56);
    display(front);

    delete_at_begin(&front);
    display(front);

    delete_at_begin(&front);
    display(front);

    delete_at_begin(&front);
    display(front);

    delete_at_end(&front);
    display(front);

    delete_at_end(&front);
    display(front);

    delete_at_end(&front);
    display(front);

    search(front, 12);
    search(front, 23);
    search(front, 34);

    display(front);

    reverse_nrec(&front);
    display(front);

    reverse_nrec(&front);
    display(front);
#endif

    return 0;
}
