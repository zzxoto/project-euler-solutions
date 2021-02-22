#include "common.h"

typedef struct bst_BST bst_BST;

typedef struct bst_DFSTraversal bst_DFSTraversal;

typedef enum bst_DFSTraversalKind
{
  bst_e_inorder,
  bst_e_preorder,
  bst_e_postorder
} bst_DFSTraversalKind;

//if a > b return +ve number
//if a < b return -ve number
//if a == b return 0
typedef i32 (* bst_CompareFn)(void *a, void *b);

bst_BST *bst_createBST(bst_CompareFn compreFn);
void    bst_freeBST(bst_BST *tree);
bool    bst_addNode(bst_BST *tree, void *data);
bool    bst_removeNode(void *data);
u32     bst_size(bst_BST *tree);

bst_DFSTraversal *bst_createDFSTraversal(bst_BST *tree, bst_DFSTraversalKind kind);
void bst_freeDFSTraversal(bst_DFSTraversal *traversal);

//returns NULL if no more nodes to traverse
void *bst_DFSNext(bst_DFSTraversal *traversal);
