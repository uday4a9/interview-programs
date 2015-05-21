#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))

typedef struct node NODE;

struct node
{
    NODE *left;
    int info;
    NODE *right;
};


NODE* create_node(int ele)
{ // Create Node and returns the nodes address
    NODE *new;
	new = malloc(sizeof(NODE));
	assert(new != NULL);

    new->info = ele;
	new->left = new->right = NULL;
	return new;
}

NODE *insert(NODE *root, int ele)
{ // Findout the exact position to insert in 
  // given BST.
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
{ // inorder traversal : left -> NODE -> right
    if(root != NULL)
	{
	    inorder(root->left);
		printf(" %d ",root->info);
	    inorder(root->right);
	}
}

void preorder(NODE *root)
{ // preorder : NODE -> left -> right
    if(root != NULL)
	{
		printf(" %d ",root->info);
	    preorder(root->left);
	    preorder(root->right);
	}
}

void postorder(NODE *root)
{ // postorder : left -> right -> NODE
    if(root != NULL)
	{
	    postorder(root->left);
	    postorder(root->right);
		printf(" %d ",root->info);
	}
}

int height(NODE *root)
{ // Return the height of the binary tree
    int left = 0, right = 0;
    if (root == NULL)
	    return 0;
  // both the logics are same, but differs only in 
  // length of the code
#if 1
    return 1 + MAX(height(root->left), height(root->right));
#else
    left = height(root->left);
    right = height(root->right);
	if(left > right)
	    return 1 + left;
    else
	    return 1 + right;
#endif
}

int size(NODE *root)
{ // size of a binary tree counts total number of nodes
  // in given tree
    if(root == NULL)
	    return 0;
    return 1 + size(root->left) + size(root->right);
}

int min(NODE *root)
{ // ttraverse till the end of the left most node of 
  // given tree, returns the node info.
    if(root != NULL)
	{
	    if(root->left != NULL)
		    min(root->left);
        else
		    return root->info;
	}
}

int max(NODE *root)
{ // ttraverse till the end of the left most node of 
  // given tree, returns the node info.
    if(root != NULL)
	{
	    if(root->right!= NULL)
		    max(root->right);
        else
		    return root->info;
	}
}

int main()
{
    NODE *root = NULL,*tmp;
	int N,i,ele;

	printf("Enter how many NODES you want to insert ? ");
	scanf("%d",&N);

	printf("Height of tree : %d \n",height(root));

	for(i=0; i<N; i++)
	{
	    scanf("%d",&ele);
		root = insert(root, ele);
    }

	printf("Inorder Elements : ");
	inorder(root);
	puts("");

	printf("Preorder Elements : ");
	preorder(root);
	puts("");

	printf("Postorder Elements : ");
	postorder(root);
	puts("");

	printf("Height of tree : %d \n",height(root));
	printf("size of tree : %d \n",size(root));

    root = NULL;
    if(root != NULL)
	{ // upon the existence of the tree only execute min and max functions.
	    printf("MIN element in Binary tree : %d \n",min(root));
	    printf("MAX element in Binary tree : %d \n",max(root));
    }

    return 0;
}
