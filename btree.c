#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node NODE;

struct node
{
    NODE *left;
    int info;
    NODE *right;
};


NODE* create_node(int ele)
{
    NODE *new;
	new = malloc(sizeof(NODE));
	assert(new != NULL);

    new->info = ele;
	new->left = new->right = NULL;
	return new;
}

NODE *insert(NODE *root, int ele)
{
	if(root == NULL)
	{
	    root = create_node(ele);
		return root;
    }
	else if(ele < root->info)
	    root->left = insert(root->left, ele);
	else 
	    root->right = insert(root->right, ele);
}

void inorder(NODE *root)
{ // inorder 
    if(root != NULL)
	{
	    inorder(root->left);
		printf(" %d ",root->info);
	    inorder(root->right);
	}
}

void preorder(NODE *root)
{ // inorder 
    if(root != NULL)
	{
		printf(" %d ",root->info);
	    preorder(root->left);
	    preorder(root->right);
	}
}

void postorder(NODE *root)
{ // inorder 
    if(root != NULL)
	{
	    postorder(root->left);
	    postorder(root->right);
		printf(" %d ",root->info);
	}
}

int main()
{
    NODE *root = NULL;
	int N,i,ele;

	printf("Enter how many NODES you want to insert ? ");
	scanf("%d",&N);

	for(i=0; i<N; i++)
	{
	    scanf("%d",&ele);
		root = insert(root, ele);
    }
	printf("Elements : ");
	inorder(root);
	puts("");
	printf("Elements : ");
	preorder(root);
	puts("");
	printf("Elements : ");
	postorder(root);
	puts("");
    return 0;
}
