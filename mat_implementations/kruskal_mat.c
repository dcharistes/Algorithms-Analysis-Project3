#include <stdio.h>
#include <stdlib.h>
#define max 100
typedef struct graph
{
   int V;
   int E;
   struct graph *adj;
} graph;
typedef struct EWtable
{
   int E1, E2, W;
} EWtable;
void initialise_graph(graph **G)
{
   for (int i = 0; i < max; i++)
   {
       G[i] = NULL;
   }
}
void insert(graph **G, int V, int node_to_join, int weight)
{
   graph *temp = G[V], *p = (graph *)malloc(sizeof(graph));
   p->V = node_to_join;
   p->E = weight;
   p->adj = NULL;
   if (temp == NULL)
   {
       G[V] = p;
   }
   else
   {
       while (temp->adj != NULL)
       {
           temp = temp->adj;
       }
       temp->adj = p;
   }
}
void insert_by_array(graph **G, int V, int nodes_to_join[][2], int no_nodes)
{
   for (int i = 0; i < no_nodes; i++)
   {
       insert(G, V, nodes_to_join[i][0], nodes_to_join[i][1]);
   }
}
void print_adj_list(graph **G)
{
   graph *temp;
   for (int i = 0; i < max; i++)
   {
       temp = G[i];
       if (G[i] != NULL)
       {
           printf("%d:->", i);
           while (temp != NULL)
           {
               printf(" (v:%d e:%d) ", temp->V, temp->E);
               temp = temp->adj;
           }
           printf("\n");
       }
   }
}
void add_value_to_graph(graph **G, int number_of_vertex)
{
   while (number_of_vertex--)
   {
       int V;
       printf("Enter vertex: ");
       scanf("%d", &V);
       int adj_edges;
       printf("Enter number of linked edges to vertex: ");
       scanf("%d", &adj_edges);
       while (adj_edges--)
       {
           int node_to_add, weight;
           printf("Enter node to join to vertex and their weight:\n");
           scanf("%d%d", &node_to_add, &weight);
           insert(G, V, node_to_add, weight);
       }
   }
}
int count_edges(graph **G)
{
   int ct = 0;
   for (int i = 0; i < max; i++)
   {
       graph *temp = G[i];
       if (G[i] != NULL)
       {
           while (temp != NULL)
           {
               ct++;
               temp = temp->adj;
           }
       }
   }
   return ct;
}
void set_EWtable(graph **G, EWtable *table)
{
   graph *temp;
   int idx = 0;
   for (int i = 0; i < max; i++)
   {
       temp = G[i];
       if (G[i] != NULL)
       {
           while (temp != NULL)
           {
               table[idx].E1 = i;
               table[idx].E2 = temp->V;
               table[idx].W = temp->E;
               temp = temp->adj;
               idx++;
           }
       }
   }
}
void print_EWtable(EWtable *table, int n)
{
   printf("Edges -> Weights  \n");
   for (int i = 0; i < n; i++)
   {
       printf("%d-%d -> %d\n", table[i].E1, table[i].E2, table[i].W);
   }
   printf("\n");
}
void sort_EWtable(EWtable *table, int n)
{
   for (int i = 0; i < n; i++)
   {
       for (int j = i + 1; j < n; j++)
       {
           if (table[i].W > table[j].W)
           {
               EWtable temp = table[i];
               table[i] = table[j];
               table[j] = temp;
           }
       }
   }
}
int find_op(int union_array[], int count_vertices, int X)
{
   if (union_array[X] == X)
   {
       return X;
   }
   else
   {
       return find_op(union_array, count_vertices, union_array[X]);
   }
}
int union_op(int union_array[], int count_vertices, int a, int b)
{
   a = find_op(union_array, count_vertices, a), b = find_op(union_array, count_vertices, b);
   if (a == b)
   {
       return -1;
   }
   union_array[b] = a;
   return 0;
}
void initialise_Union_array(int *a, int size)
{
   for (int i = 0; i <= size; i++)
   {
       a[i] = i;
   }
}
int count_vertices(graph **G)
{
   int ct = 0;
   for (int i = 0; i < max; i++)
   {
       if (G[i] != NULL)
           ct++;
   }
   return ct;
}
void swap(int *a, int *b)
{
   int temp = (*a);
   (*a) = (*b);
   (*b) = temp;
}
int count_total_weight_sum(graph **ANS)
{
   EWtable ans_table[2 * max];
   set_EWtable(ANS, ans_table);
   int size=count_edges(ANS);
   int cantor_pair[10000], ans = 0;
   for (int i = 0; i < 10000; i++)
       cantor_pair[i] = 0;
   for (int i = 0; i < size; i++)
   {
       int a = ans_table[i].E1, b = ans_table[i].E2;
       if (ans_table[i].E1 < ans_table[i].E2)
       {
           swap(&a, &b);
       }
       if (cantor_pair[a * a + a + b] == 0)
       {
           cantor_pair[a * a + a + b] = 1;
           ans += ans_table[i].W;
       }
   }
   return ans;
}


int construct_minimum_spanning_tree(graph **G, graph **ANS, EWtable *table, int n)
{
   initialise_graph(ANS);
   EWtable ans_table[3 * max];
   int size = count_vertices(G);
   int union_array[size + 1];
   initialise_Union_array(union_array, size);

   int ct = 0, union_ct = 0;
   for (int i = 0; i < n; i++)
   {
       if (union_op(union_array, size, table[i].E1, table[i].E2) != -1 && union_ct != count_vertices(G) - 1)
       {
           union_ct++;
           ans_table[ct].E1 = table[i].E1;
           ans_table[ct].E2 = table[i].E2;
           ans_table[ct].W = table[i].W;

           for (int j = 0; j < n; j++)
           {
               if ((table[j].E1 == table[i].E2 && table[j].E2 == table[i].E1 && table[j].W == table[i].W) && j != i)
               {
                   ct++;
                   ans_table[ct].E1 = table[i].E2;
                   ans_table[ct].E2 = table[i].E1;
                   ans_table[ct].W = table[i].W;
                   break;
               }
           }
           ct++;
       }
   }
   printf("Final EWtable to be inseted in minimum spanning tree:\n");
   print_EWtable(ans_table, ct);
   int ans = 0;
   for (int i = 0; i < ct; i++)
   {
       insert(ANS, ans_table[i].E1, ans_table[i].E2, ans_table[i].W);
   }
   ans = count_total_weight_sum(ANS);
   return ans;
}

void kruskal(graph **G, graph **ANS)
{
   EWtable table[3 * max], ans_table[3 * max];

   initialise_graph(ANS);
   printf("\nThe inputted graph is:\n");
   print_adj_list(G);

   set_EWtable(G, table);
   int n = count_edges(G);
   sort_EWtable(table, n);
   printf("\nThe edges and weights in sorted manner: \n");
   print_EWtable(table, n);

   int min_weight_sum = construct_minimum_spanning_tree(G, ANS, table, n);
   printf("Minimum spanning tree with total weight sum: %d\n", min_weight_sum);
   print_adj_list(ANS);
}

int main()
{
   graph *G[max], *ANS[max];
   initialise_graph(G);

   // Inserting values in graph...
   int v_1[5][2] = {{2, 6}, {3, 1}, {4, 3}, {5, 2}, {6, 1}};
   int v_2[5][2] = {{6, 3}, {1, 6}, {3, 4}, {5, 5}, {4, 7}};
   int v_3[4][2] = {{1, 1}, {2, 4}, {4, 1}, {5, 2}};
   int v_4[5][2] = {{2, 7}, {1, 3}, {3, 1}, {5, 4}, {6, 2}};
   int v_5[5][2] = {{3, 2}, {1, 2}, {2, 5}, {4, 4}, {6, 5}};
   int v_6[4][2] = {{4, 2}, {1, 1}, {5, 5}, {2, 3}};
   insert_by_array(G, 1, v_1, 5);
   insert_by_array(G, 2, v_2, 5);
   insert_by_array(G, 3, v_3, 4);
   insert_by_array(G, 4, v_4, 4);
   insert_by_array(G, 5, v_5, 5);
   insert_by_array(G, 6, v_6, 4);

   //If you would like you can also input in graph dynamically...
   //add_value_to_graph(G,number_of_vertex);
   // Using kruskal's algorithm...
   kruskal(G, ANS);
   return 0;
}

