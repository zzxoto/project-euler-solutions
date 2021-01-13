#include "lib/common.h"
#include "lib/graph.h"

//Question:
//
//By starting at the top of the triangle below and
//moving to adjacent numbers on the row below, the maximum total from top to bottom is 23.
//              3
//             7 4
//            2 4 6
//           8 5 9 3
//That is, 3 + 7 + 4 + 9 = 23.
//
//Find the maximum total from top to bottom of the triangle below:

i32 main(i32 argc, i32 **argv)
{
  i32 triangle[] = {
    75
    ,95, 64
    ,17, 47, 82 
    ,18, 35, 87, 10
    ,20, 04, 82, 47, 65
    ,19, 01, 23, 75, 03, 34
    ,88, 02, 77, 73, 07, 63, 67
    ,99, 65, 04, 28, 06, 16, 70, 92
    ,41, 41, 26, 56, 83, 40, 80, 70, 33
    ,41, 48, 72, 33, 47, 32, 37, 16, 94, 29
    ,53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14
    ,70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57
    ,91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48
    ,63, 66, 04, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31
    ,04, 62, 98, 27, 23, 9,  70, 98, 73, 93, 38, 53, 60, 04, 23
  };

  //no. of vertices
  i32 V = sizeof(triangle) / sizeof(i32);

  //1. Weight vector
  i32 *W = triangle;

  //2. "Cost" Vector. We ought to maximize this.
  i32 *D = (i32 *) alloca(V * sizeof(i32));
  for (i32 i = 0; i < V; i++)
  {
      D[i] = 0;
  }
  D[0] = triangle[0];

  //3. create graph
  //ith index of triangle is the vertex i of this graph
  g_Graph *graph = g_createGraph(V);

  //4. build graph
  {
    //see notes "How many rows in a triangle of numbers" for the proof
    i32 rows  = (sqrt(1 + 8 * V) - 1) / 2;

    for (i32 row = 0; row < rows - 1; row++)
    {
      //ABSOUTE index of first element in the THIS ROW
      i32 i = (row * (row + 1) / 2);

      //there are i + 1 elements in ith row of the triangle
      i32 cols = row + 1;

      //ABSOUTE index of first element in NEXT ROW
      i32 i2 = i + cols;

      for (i32 col = 0; col < cols; col++)
      {
        i32 u  = i + col;
        i32 v1 = i2 + col;
        i32 v2 = i2 + col + 1;
        g_addEdge(graph, u, v1);
        g_addEdge(graph, u, v2);
      }
    }
  }

  //5. Topological sort
  //property of triangle is that it is by virtue, topologically sorted.
  //Even then, being explicit here
  i32 *sortedVertices = (i32 *) alloca(V * sizeof(i32));
  i32 sortedVerticesLen = V;
  g_topsort(graph, sortedVertices, &sortedVerticesLen);

  //5. "Relax" the edges, as MIT lecture names it. Basically at the end of this
  //piece of code, D vector would be maximized.
  {
    i32 adj[2];
    i32 adjLen = 2;

    for (i32 i = 0; i < sortedVerticesLen; i++)
    {
      i32 u = sortedVertices[i];
      g_getAdjacentVertices(graph, u, adj, &adjLen);

      for (i32 j = 0; j < adjLen; j++)
      {
        i32 v = adj[j];
        if (D[u] + W[v] > D[v])
        {
          D[v] = D[u] + W[v];
        }
      }
    }
  }

  //6. search for maximum in the bottom of the triangle
  i32 max;
  {
    //last row
    i32 row  = ((sqrt(1 + 8 * V) - 1) / 2) - 1;

    //first element in last row
    i32 i = (row * (row + 1) / 2);

    max = D[i];
    for (;i < V; i++)
    {
      max = MAX(max, D[i]);
    }
  }

  printf("%d\n", max);

  return 0;
}
