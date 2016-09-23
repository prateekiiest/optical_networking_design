#include <stdio.h>
#include <limits.h>
#include<stdbool.h>  
// Number of vertices in the graph
#define V 14 
  
int minDistance(int dist[], bool sptSet[])
{
   // Initialize min value
   int min = INT_MAX, min_index;
  int v;
   for (v = 0; v < V; v++)
     if (sptSet[v] == false && dist[v] <= min)
         min = dist[v], min_index = v;
  
   return min_index;
}
  
// A utility function to print the constructed distance array
int printSolution(int dist[], int n)
{  int i;
   printf("Vertex   Distance from Source\n");
   for ( i = 0; i < V; i++)
      printf("%d \t\t %d\n", i, dist[i]);
}
  


void dijkstra(int graph[V][V], int src)
{
     int dist[V];   
     int  i;
     bool sptSet[V];
     int count; 
    
     for (i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
  
     // Distance of source vertex from itself is always 0
     dist[src] = 0;
  
     // Find shortest path for all vertices
     for (count = 0; count < V-1; count++)
     {

       int u = minDistance(dist, sptSet);
  
        int v;
       sptSet[u] = true;
  

       for (v = 0; v < V; v++)
  
 
 

         if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX 
                                       && dist[u]+graph[u][v] < dist[v])
            dist[v] = dist[u] + graph[u][v];
     }
  
     // print the constructed distance array
     printSolution(dist, V);
}
  
// driver program to test above function
int main()
{
   /* Let us create the example graph discussed above */
   int graph[V][V] = {{0, 4, 5, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0},

{4, 0, 9, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{5, 9, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 ,0}, 
{0, 1, 0, 0, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0},
{8, 0, 0, 0, 0, 0, 5, 0, 0, 0, 6, 0, 0, 0},
{0, 0, 0 ,3 ,0, 5, 0, 1, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0 ,1 ,0, 0, 0, 0, 0, 0, 0},
{0, 0, 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0},
{0, 0, 0, 0, 7, 0, 0, 0, 7, 0, 0, 9, 1, 0},
{0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 1, 6, 0},
{0, 0, 0, 0, 0, 0, 0, 0 ,0 ,9 ,1 ,0 ,0 ,4},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 6, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0},
};
                     
  
    dijkstra(graph, 0); // From the vertex 0
  
    return 0;

}
