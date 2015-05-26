#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define LIMIT 30

typedef struct node NODE;

struct node
{
    NODE *left;
    int info;
    NODE *right;
};

NODE *stack1[LIMIT],*stack2[LIMIT];
int top1=-1,top2=-1;

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

void push(NODE **st, int *top, NODE *ele)
{ // Just insert an element into the stack
    if(*top == LIMIT-1)
    {
        puts("STACK OVEFLOW");
	exit(1);
    }
    st[(*top)++] = ele;
}

NODE* pop(NODE **st, int *top)
{ // removes the element from the stack
    if(*top == -1)
    {
        puts("STACK UNDERFLOW");
	exit(1);
    }
    return st[(*top)--];
}

int isempty(NODE **st, int *top)
{
    return ((*top)<0 ? 1 : 0);
}

void postorder_nrec(NODE *root)
{ // create 2 stacks for keep track of the elements.
  // one stack to keep track of elements, another stack 
  // to hold the post order traversal of tree.
    
    NODE *tmp;

    if(root ==  NULL)
        return;

    push(stack1, &top1, root);
    printf("1 top1 : %d top2 : %d \n",top1,top2); 
    while(! isempty(stack1,&top1) )
    {
        tmp = pop(stack1, &top1);    
        push(stack2, &top2, tmp);
    printf("2 top1 : %d top2 : %d \n",top1,top2); 

	if (tmp->left)
	    push(stack1, &top1, tmp->left);
	if (tmp->right)
	    push(stack1, &top1, tmp->right);
    }

    while(! isempty(stack2, &top2))
    {
        tmp = pop(stack2, &top2);
	printf("%d => ",tmp->info);
    }
    puts("NULL\n");
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

int search(NODE *root, int key)
{ // search for the given key element, If key is not found
  // return 0, else return 1
    if(root != NULL) 
    {
        if(root->info == key)
	    return 1;
	else if(key < root->info )
	    return search(root->left, key);
        else
	    return search(root->right, key);
    }
    return 0;
}

int maxdepth(NODE *root)
{ // Find out the maxdepth of th egiven binary tree
    if(root == NULL)
        return 0;
    return 1 + MAX(maxdepth(root->left),maxdepth(root->right));
}

int isBST(NODE *root)
{ // if the given tree is inordered(Always incresing) travesal and
  // keep track of last visting node. Then we can come to know that
  // whether tree follows binary search tree rule or not.
    NODE *prev = NULL;
    if(root != NULL)
    {
	if( ! isBST(root->left))
	    return 0;
        if(prev != NULL && root->info < prev->info)
	    return 0;
        prev = root;
	return isBST(root->right);
    }
    return 1;
}

void printArray(int *pathArr, int pathlen)
{ // print the pathlen of array elements
    int i=0;
    for(i=0; i<pathlen; i++)
      printf(" %d => ",pathArr[i]);
    puts("NULL");
}

void printPaths(NODE *root, int *pathArr, int pathlen)
{ // Take the input paramters as root, path Array, and Path len 
  // Once if tree taversal reaches to end, just print the 
  // path array,pathlen as size.
    
    if(root == NULL)
        return;
    pathArr[pathlen++] = root->info;
    if(root->left==NULL && root->right==NULL)
        printArray(pathArr, pathlen);
    printPaths(root->left, pathArr, pathlen);
    printPaths(root->right, pathArr, pathlen);
}

int isSame(NODE *root1, NODE *root2)
{ // check is corresponding nodes in a tree are equal or not
  // it'll handle 3 conditions. if both are NULL, Both are 
  // not NULL and either one is NULL. 
  // on success returns 1, on failure returns 0
    if(root1 == NULL && root2 == NULL)
        return 1;
    if(root1 != NULL && root2 != NULL)
        return root1->info == root2->info && \
               isSame(root1->left, root2->left) && \
	       isSame(root1->right, root2->right);
    return 0;
}

int isMirrorImage(NODE *root1, NODE *root2)
{ // Check whether mirror images of given two trees
  // are equal or not ?
    if(root1 == NULL && root2 == NULL)
        return 1;
    if(root1 == NULL || root2 == NULL)
        return 0;
    return root1->info == root2->info && \
           isMirrorImage(root1->left, root2->right) && \
           isMirrorImage(root1->right, root2->left);
}

int diameter(NODE *root)
{ // Finding out the diameter of the given tree. diameter
  // can be calulated as the no. of nodes between the end to end
  // of the most legthy leaf nodes. Diameter doesn't mean to
  // say to traverse through the root node always.
  // so, better to findout the height of the left and subtrees 
  // from a node, and diameters of the corresponding nodes.
  // finding out the max aming two results the diameter of a Binary tree.

    int lheight, rheight, ldiam, rdiam;
    if(root == NULL)
        return 0;
    lheight = height(root->left);
    rheight = height(root->right);

    ldiam = diameter(root->left);
    rdiam = diameter(root->right);

    return MAX(lheight + rheight + 1, MAX(ldiam, rdiam));
}

NODE* delete(NODE *root)
{ // This method traverse till the ends of binary tree
  // and delete the reachable last node. By properly
  // rearranging the links to NULL. At last this function
  // has to return the NULL to the caller.
    if(root == NULL)
        return root;
    root->left = delete(root->left);
    root->right = delete(root->right);
    free(root);
    root = NULL;
    return root;
}

int main(int argc, char **argv)
{
    NODE *root = NULL,*tmp;
    int N, i, ele, key;
    
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

    if(root != NULL)
    { // upon the existence of the tree only execute min and max functions.
        printf("MIN element in Binary tree : %d \n",min(root));
        printf("MAX element in Binary tree : %d \n",max(root));
    }

    if(root != NULL && argc == 2)
    { // searching for the given key, upon the existence of tree
	  // and if passes the only argv[1], other wise enable below
	  // two lines (#if 1).
#if 0
        printf("Enter a key to search : ");
        scanf("%d", &key);
#endif
        key = atoi(argv[1]);
        if(search(root, key) == 1)
            puts("FOUND");
        else
            puts("NOT FOUND");
    }

    // Max depth of the binary tree
    printf("MAXDEPTH of the tree : %d\n",maxdepth(root));

    if(isBST(root))
        puts("BST");
    else
        puts("NOT BST");

    // Print paths of the given BST.
    // Initially we don't know the pathlen, so pass it as zero.
    int pathArr[20]; // change this size accordingly.
    if(root)
        printPaths(root, pathArr, 0);

    NODE *root1 = NULL;
    if(isSame(root,root1))
        puts("BOTH TREES ARE SAME");
    else
        puts("BOTH TREES ARE NOT SAME");

    if(isMirrorImage(root, root1))
        puts("MIRROR IMAGES");
    else
        puts("NOT MIRROR IMAGES");

    printf("Diameter of given tree : %d \n",diameter(root));

//    root = delete(root);

    printf("post order non recursive travel : ");
    postorder_nrec(root);

    return 0;
}
