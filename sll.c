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
    new->next = NULL;
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

    if(pos < 1) // check given position is valid or not
    {
        puts("zero or -ve pos not allowed");
	return;
    }

    nn = create_node(info);

    if( *front==NULL && pos==1)
    { // list is not there, and given pos is 1
        *front = nn;
	return;
    }

    if(pos == 1)
    { // list is there, and position is 1
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

void delete_at_any_pos(NODE **front, int pos)
{
    NODE *cur, *prv ;
    int i=0;

    if(*front == NULL)
    {
        puts("List empty, Nothing to delete");
	return;
    }

    if(pos < 1)
    {
        puts("Zero or -ve postions not allowed");
	return;
    }

    if( (*front)->next==NULL && pos==1 )
    {
        free(*front);
	*front = NULL;
	return;
    }

    if(pos == 1)
    {
        cur = *front;
	(*front) = (*front)->next;
	cur->next = NULL;
	free(cur);
	cur = NULL;
	return;
    }

    cur = *front;
    while(i < pos-1)
    {
        prv = cur;
	cur = cur->next;
	if(cur == NULL)
	{
	    puts("Not possible, Beyond the List Position");
	    return;
	}
        ++i;
    }
    prv->next = cur->next;
    cur->next = NULL;
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

void reverse_rec(NODE **front)
{ // Recursive method to reverse the list
    NODE *prv, *nxt;

    if(*front == NULL)
        return;

    prv = *front;
    nxt = prv->next;

    if(nxt == NULL)
        return;

    reverse_rec(&nxt);
    prv->next->next = prv;
    prv->next = NULL;
    *front = nxt;
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

int is_palindrome(NODE **front, NODE *last)
{
    if(last == NULL)
        return 1;

    int i = is_palindrome(front, last->next);

    if (i ==0)
        return 0;

    int j = ((*front)->info == last->info);

    (*front) = (*front)->next;

    return j;
}

int main()
{
    NODE *front = NULL;

    display(front);  // List is empty

    insert_at_any_pos(&front, 22, 1);
    display(front);

    insert_at_any_pos(&front, 23, 2);
    display(front);

    insert_at_any_pos(&front, 12, 1);
    display(front);

    insert_at_end(&front, 12);
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

    delete_at_any_pos(&front, 5);
    delete_at_any_pos(&front, 0);
    delete_at_any_pos(&front, -1);

    delete_at_any_pos(&front, 2);
    display(front);

    delete_at_any_pos(&front, 1);
    display(front);

    delete_at_any_pos(&front, 1);
    display(front);

    delete_at_any_pos(&front, 1);
    display(front);

    delete_at_any_pos(&front, 1);
    display(front);

    reverse_rec(&front);
#endif
    NODE *tmp = front; //preserve the front pointer address
    if ( is_palindrome(&front, front) )
        puts("IT'S PALINDROME");
    else
        puts("IT'S NOT PALINDROME");
    front = tmp;

    display(front);

    return 0;
}
