typedef struct g_Graph g_Graph;

typedef void(* g_DFSCallback)(i32 u, void *bag);

g_Graph *g_createGraph(i32 V);
void g_freeGraph      (g_Graph *g);
void g_addEdge        (g_Graph *g, i32 u, i32 v);
void g_removeEdge     (g_Graph *g, i32 u, i32 v);
void g_DFS            (g_Graph *g, void *bag, g_DFSCallback cb);
void g_topsort        (g_Graph *g, i32 *vertices, i32 *vericesLen);
void g_getAdjacentVertices(g_Graph *g, i32 u, i32 *vertices, i32 *verticesLen);
