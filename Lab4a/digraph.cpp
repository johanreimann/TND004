/*********************************************
* file:	~\tnd004\lab\lab4a\digraph.cpp       *
* remark: mplementation of directed graphs   *
* file for students                          *
**********************************************/


#include <iostream>
#include <iomanip>
#include <cassert>
#include <string>

using namespace std;

#include "digraph.h"
#include "queue.h"

const int INFINITY = 9999;

// -- CONSTRUCTORS

Digraph::Digraph(int n)
{
    assert(n >= 1);
    array = new List[n + 1];
    dist  = new int [n + 1];
    path  = new int [n + 1];
    done  = new bool[n + 1];
    size  = n;
}

// -- DESTRUCTOR

Digraph::~Digraph()
{
    delete[] array;
    delete[] dist;
    delete[] path;
    delete[] done;
}

// -- MEMBER FUNCTIONS

// insert directed edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Digraph::insertEdge(int u, int v, int w)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].insert(v, w);
}

// remove directed edge (u, v)
void Digraph::removeEdge(int u, int v)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].remove(v);
}

// unweighted single source shortest paths
void Digraph::uwsssp(int s)
{
    Queue<int> Q;
    if (s < 1 || s > size)
    {
         cout << "\nERROR: expected source s in range 1.." << size << " !" << endl;
         return;
    }

    for(int i = 1; i <= size; i++)
    {
            dist[i] = INFINITY;
            path[i] = 0;
    }

    dist[s] = 0;
    Q.enqueue(s);

    while (!Q.isEmpty())
    {
        int v = Q.getFront();
        Q.dequeue();

        Node *p2 = array[v].getFirst();

        while(p2 != nullptr)
        {
            if(dist[p2->vertex] == INFINITY)
            {
                dist[p2->vertex] = dist[v] + 1;
                path[p2->vertex] = v;
                Q.enqueue(p2->vertex);
            }
            p2 = array[p2->vertex].getNext();
        }
    }
}

// positive weighted single source shortest pats
void Digraph::pwsssp(int s)
{
    if (s < 1 || s > size)
    {
         cout << "\nERROR: expected source s in range 1.." << size << " !" << endl;
         return;
    }

    for(int i = 0; i <= size; i++)
    {
        dist[i] = INFINITY;
        path[i] = 0;
        done[i] = false;
    }

    dist[s] = 0;
    done[s] = true;
    int v = s;

    while(true)
    {
        Node *p = array[v].getFirst();
        while(p != nullptr)
        {
            if(!done[p->vertex] && (dist[p->vertex] > (dist[v] + p->weight)))
            {
                dist[p->vertex] = dist[v] + p->weight;
                path[p->vertex] = v;
            }
            p = array[v].getNext();
        }

        v = minDistance(dist, done);

        if (dist[v] >= INFINITY)
            break;

        done[v] = true;
    }
}

int Digraph::minDistance(int dist[], bool done[])
{
   // Initialize min value
   int minDist = INFINITY, min_index = 0;

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




// print graph
void Digraph::printGraph() const
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex  adjacency list                  " << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " : ";
        array[v].print();
    }

    cout << "------------------------------------------------------------------" << endl;
}

// print shortest path tree for s
void Digraph::printTree() const
{
    cout << "----------------------" << endl;
    cout << "vertex    dist    path" << endl;
    cout << "----------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " :" << setw(8) << dist[v] << setw(8) << path[v] << endl;
    }

    cout << "----------------------" << endl;
}

// print shortest path from s to t
void Digraph::printPath(int t, int &counter) const
{
    if (t < 1 || t > size)
    {
         cout << "\nERROR: expected target t in range 1.." << size << " !" << endl;
         return;
    }

    if (path[t] != 0)
    {
        counter++;
        printPath(path[t], counter);
    }
    else
        cout << " (" << counter << ")";

    cout << setw(4) << right << t;

}
