#include "bst.h"

typedef struct bst_Node
{
  void *data;
  struct bst_Node *left;
  struct bst_Node *right;
  struct bst_Node *parent;
} bst_Node;

//TODO: realloc if insertCount >= maxInserts
//TODO: implement inorder/postorder traversal
//TODO: implement remove node
typedef struct bst_BST
{
  u32 size;
  u32 insertCount;
  u32 maxInserts;
  bst_CompareFn compareFn;
  struct bst_Node *root;
} bst_BST;

internal u32 bst_initDFSTraversal_preorder(bst_Node *curr, bst_DFSTraversal *dfs, u32 insertOffset);

typedef struct bst_DFSTraversal
{
  bst_Node **nodes;
  u32 maxCount;
  u32 at;
} bst_DFSTraversal;

bst_BST *bst_createBST(bst_CompareFn compareFn)
{
  bst_BST *tree = (bst_BST *) malloc(sizeof(bst_BST));
  tree->size        = 0;
  tree->insertCount = 0;
  tree->maxInserts  = 8192; 
  tree->compareFn   = compareFn;

  bst_Node *root = (bst_Node *) malloc(sizeof(bst_Node) * tree->maxInserts);
  memset(root, 0, sizeof(bst_Node) * tree->maxInserts);

  tree->root = root;

  return tree;
}

void bst_freeBST(bst_BST *tree)
{
  free(tree->root);
  free(tree);
}

bool bst_addNode(bst_BST *tree, void *data)
{
  if (!tree->size)
  {
    bst_Node *n = tree->root;
    n->left   = NULL;
    n->right  = NULL;
    n->parent = NULL;
    n->data = data;

    tree->size += 1;
    tree->insertCount += 1;

    return true;
  }

  bst_Node *curr = tree->root;
  bool insertAtLeft = false;

  for(;;)
  {
    i32 compareResult = tree->compareFn(data, curr->data);
    if (compareResult < 0)
    {
      if (curr->left)
      {
        curr = curr->left;
      }
      else
      {
        insertAtLeft = true;
        break;
      }
    }
    else if (compareResult > 0)
    {
      if (curr->right)
      {
        curr = curr->right;
      }
      else
      {
        insertAtLeft = false;
        break;
      }
    }
    else
    {
      return false;
    }
  }

  bst_Node *newNode = tree->root + tree->insertCount;
  newNode->left   = NULL;
  newNode->right  = NULL;
  newNode->parent = curr;
  newNode->data   = data;

  tree->size += 1;
  tree->insertCount += 1;

  if (insertAtLeft)
  {
    curr->left = newNode;
  }
  else
  {
    curr->right = newNode;
  }

  return true;
}

bool bst_removeNode(void *data)
{
  printf("Not implemented bst_removeNode\n");
  assert(false);

  return false;
}

u32 bst_size(bst_BST *tree)
{
  return tree->size;
}

bst_DFSTraversal *bst_createDFSTraversal(bst_BST *tree, bst_DFSTraversalKind kind)
{
  if (kind != bst_e_preorder)
  {
    printf("Only preorder traversal implemented\n");
    assert(false);
  }

  bst_DFSTraversal *dfs = (bst_DFSTraversal *) malloc(sizeof(bst_DFSTraversal));

  if (!tree->size)
  {
    dfs->nodes = NULL;
    dfs->maxCount = 0;
    dfs->at = 0;

    return dfs;
  }
  else
  {
    dfs->nodes = (bst_Node **) malloc(sizeof(bst_Node *) * tree->size);
    dfs->maxCount = tree->size;
    dfs->at = 0;
  }

  bst_initDFSTraversal_preorder(tree->root, dfs, 0);

  return dfs;
}

//return value is just used internally for recursion
internal u32 bst_initDFSTraversal_preorder(bst_Node *curr, bst_DFSTraversal *dfs, u32 insertOffset)
{
  if (curr->left)
  {
    insertOffset = bst_initDFSTraversal_preorder(curr->left, dfs, insertOffset);
  }

  *(dfs->nodes + insertOffset) = curr;
  insertOffset++;

  if (curr->right)
  {
    insertOffset = bst_initDFSTraversal_preorder(curr->right, dfs, insertOffset);
  }

  return insertOffset;
}

void bst_freeDFSTraversal(bst_DFSTraversal *dfs)
{
  if (dfs->nodes)
  {
    free(dfs->nodes);
  }
  free(dfs);
}

void *bst_DFSNext(bst_DFSTraversal *dfs)
{
  if (dfs->at >= dfs->maxCount)
  {
    return NULL;
  }
  bst_Node *node = *(dfs->nodes + dfs->at);

  dfs->at = dfs->at + 1;

  return node->data;
}
