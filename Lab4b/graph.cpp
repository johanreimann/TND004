/*********************************************
* file:	~\tnd004\lab\lab4b\graph.h           *
* remark:implementation of undirected graphs *
* file for students                          *
**********************************************/


#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

#include "graph.h"
#include "edge.h"
#include "heap.h"
#include "dsets.h"

const int INFINITY = 9999;

// -- CONSTRUCTORS

Graph::Graph(int n)
{
    assert(n >= 1);
    array = new List[n + 1];
    size  = n;
}

// -- DESTRUCTOR

Graph::~Graph()
{
    delete[] array;
}

// -- MEMBER FUNCTIONS

// insert undirected edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Graph::insertEdge(int u, int v, int w)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].insert(v, w);
    array[v].insert(u, w);
}

// remove undirected edge (u, v)
void Graph::removeEdge(int u, int v)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].remove(v);
    array[v].remove(u);
}

// Prim's minimum spanning tree algorithm
void Graph::mstPrim() const
{
    // *** TODO ***
    int source = 1;
    const int NR_EDGES = size-1;
    int weightCounter = 0;

    int dist[size + 1];
    int path[size + 1];
    bool done[size + 1];

    Edge edges[NR_EDGES];

    for(int i = 1; i <= size; i++)
    {
        dist[i] = INFINITY;
        path[i] = 0;
        done[i] = false;
    }

    dist[source] = 0;
    done[source] = true;

    int v = source;

    for(int i = 0; i < NR_EDGES; i++)
    {
        Node* p = array[source].getFirst();

        while(p != nullptr)
        {
            if(!done[p->vertex] && (dist[p->vertex] > p->weight))
            {
                dist[p->vertex] = p->weight;
                path[p->vertex] = v;
            }
            p = array[v].getNext();
        }
        v = minDistance(dist, done);
        weightCounter += dist[v];
        edges[i] = Edge(path[v], v, dist[v]); //head, tail, weight

        done[v] = true;
    }

    for(int i = 0; i < NR_EDGES; i++)
        cout << edges[i] << endl;

    cout << endl << "Total Weight: " << weightCounter << endl;
}

int Graph::minDistance(int dist[], bool done[]) const
{
   // Initialize min value
   int minDist = INFINITY, min_index;

   for (int v = 1; v <= size; v++)
   {
        if (done[v] == false && dist[v] <= minDist)
        {
             minDist = dist[v];
             min_index = v;
        }
   }
   return min_index;
}


// Kruskal's minimum spanning tree algorithm
void Graph::mstKruskal() const
{
    // *** TODO ***
    const int NR_EDGES = size-1;
    int weightCounter = 0;
    int counter_H = 0;

    Heap <Edge> H;//(NR_EDGES); //Heap = lägg in alla edges

    DSets D(size);//Dsets = alla olika småträd

    //hepify
    for(int i = 1; i <= size; i++)
    {
        //hitta den edge med minst vikt
        Node* p = array[i].getFirst();

        while(p != nullptr)
        {

            if (i < p->vertex)
            {
                Edge e(i, p->vertex, p->weight); //head, tale, weight
                H.insert(e);
                counter_H++;
            }
            p = array[i].getNext();
        }
    }
    int counter = 0;
    Edge e2;

    while (counter < NR_EDGES)
    {
        e2 = H.deleteMin(); //första ur heap
        if(D.find(e2.head) != D.find(e2.tail))
        {
            //display (v, u, weight(v,u));
            D.join(D.find(e2.head), D.find(e2.tail));
            weightCounter += e2.weight;
            counter++;
            cout << "( " << e2.head << ",  " << e2.tail << ",  " << e2.weight << ")" << endl;
        }
    }
    cout << endl << "Total Weight: " << weightCounter << endl;
}

// print graph
void Graph::printGraph() const
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex  adjacency list                                            " << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " : ";
        array[v].print();
    }

    cout << "------------------------------------------------------------------" << endl;
}
