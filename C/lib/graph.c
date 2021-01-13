#include "common.h"
#include "graph.h"
#include "utils.h"

/*
  DFS works ok with cycles as it naturally does. g_topsort uses DFS for ordering of vertices,
  therefore it terminates on graph with cycles.
*/

//Node of the adjacency list
typedef struct g_Node
{
  i32 v;
  struct g_Node *next;
} g_Node;

typedef struct g_Graph
{
  i32  V;
  g_Node **list;
} g_Graph;

internal void g_checkVertex(g_Graph *g, i32 v);
internal void g_DFSVisit(g_Graph *g, i32 s, bool *visited, void *bag, g_DFSCallback cb);
internal void g_topsortDFSCallback(i32 u, void *bag);

g_Graph *g_createGraph(i32 V)
{
  assert(V > 0);

  g_Node **list = (g_Node **) malloc(sizeof(g_Node *) * V);
  //set pointers to null;
  {
    g_Node **head = list;
    i32 V_ = V;
    while(V_--)
    {
      *head = NULL;
      head  += 1;
    }
  }

  g_Graph *g = (g_Graph *) malloc(sizeof(g_Graph));
  g->V       = V;
  g->list    = list;

  return g;
}

void g_freeGraph(g_Graph *g)
{
  for (i32 i = 0; i < g->V; i++)
  {
    g_Node *neighbor = g->list[i];
    g_Node *n;
    while (neighbor)
    {
      n = neighbor;
      neighbor = neighbor->next;
      free(n);
    }
  }

  free(g->list);
}

void g_addEdge(g_Graph *g, i32 u, i32 v)
{
  g_removeEdge(g, u, v);

  g_Node **neighbors = g->list + u;

  g_Node *node = (g_Node *) malloc(sizeof(g_Node));
  node->v = v;
  node->next = NULL;

  if (*neighbors == NULL)
  {
    //No edges coming out of vertex u, so far
    *neighbors = node;
  }
  else
  {
    g_Node *neighbor = *neighbors;
    while(neighbor->next)
    {
      neighbor = neighbor->next;
    }
    neighbor->next = node;
  }
}

void g_removeEdge(g_Graph *g, i32 u, i32 v)
{
  g_checkVertex(g, u);
  g_checkVertex(g, v);

  g_Node **neighbors = g->list + u;

  g_Node *neighborNext = *neighbors;
  g_Node *neighborPrev = NULL;

  while(neighborNext)
  {
    if (neighborNext->v == v)
    {
      if (neighborPrev)
      {
        //remove from the body of the list
        neighborPrev->next = neighborNext->next;
        free(neighborNext);
        neighborNext       = neighborPrev->next;
      }
      else
      {
        //removing from head of the list
        g_Node *neighborNext_ = neighborNext->next;
        free(neighborNext);
        neighborNext          = neighborNext_;
        *neighbors            = neighborNext_;
      }

      break;
    }
    else
    {
      neighborPrev = neighborNext;
      neighborNext = neighborNext->next;
    }
  }
}

void g_DFS(g_Graph *g, void *bag, g_DFSCallback cb)
{
  i32 V = g->V;

  bool *visited = alloca(sizeof(bool) * V);
  memset(visited, false, sizeof(bool) * V);

  for (i32 s = 0; s < V; s++)
  {
    if (!visited[s])
    {
      g_DFSVisit(g, s, visited, bag, cb);
    }
  }
}

internal void g_DFSVisit(g_Graph *g, i32 s, bool *visited, void *bag, g_DFSCallback cb)
{
  g_Node *neighbor = g->list[s];
  visited[s] = true;

  while(neighbor)
  {
    if (!visited[neighbor->v])
    {
      g_DFSVisit(g, neighbor->v, visited, bag, cb);
    }
    neighbor = neighbor->next;
  }

  cb(s, bag);
}

typedef struct g_TopsortDFSState
{
  i32   *sortedVertices;
  i32   idx;
} g_TopsortDFSState;

void g_topsort(g_Graph *g, i32 *vertices, i32 *verticesLen)
{
  assert(verticesLen >= 0);

  g_TopsortDFSState state;
  state.sortedVertices = (i32 *) alloca(sizeof(i32) * g->V);
  state.idx            = g->V - 1;

  g_DFS(g, &state, g_topsortDFSCallback);
  
  i32 K = MIN(*verticesLen, g->V);
  for (i32 i = 0; i < K; i++)
  {
    vertices[i] = state.sortedVertices[i];
  }
  *verticesLen = K;
}

internal void g_topsortDFSCallback(i32 u, void *bag)
{
  g_TopsortDFSState *state = (g_TopsortDFSState *) bag;
  state->sortedVertices[state->idx--] = u;
}

void g_getAdjacentVertices(g_Graph *g, i32 u, i32 *vertices, i32 *verticesLen)
{
  i32 *adj = (i32 *) alloca(sizeof(i32) * g->V);

  i32 count = 0;
  g_Node *neighbor = g->list[u];
  while(neighbor)
  {
    adj[count++] = neighbor->v;
    neighbor = neighbor->next;
  }

  for (i32 i = 0; i < count; i++)
  {
    vertices[i] = adj[i];
  }
  *verticesLen = count;
}

internal void g_checkVertex(g_Graph *g, i32 v)
{
  assert(v >= 0 && v < g->V);
}

internal void printAdjacentVertices(g_Graph *g, i32 u)
{
  i32 len = g->V;
  i32 *vertices = (i32 *) alloca(sizeof(i32) * len);

  g_getAdjacentVertices(g, u, vertices, &len);
  u_printList_i32(vertices, len);
}
