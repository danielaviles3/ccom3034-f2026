

//Daniel Aviles Gerena
//801-24-5453

// shortest.cpp - print the shortest path between given nodes in a graph
// Copyright (2026) - Humberto Ortiz Zuazaga
// Released under
// https://creativecommons.org/licenses/by/4.0/deed.en

#include <iostream>

#include "AdjacencyLists.h"
#include "graph-algorithms.h"



template<class Graph>
bool shortestPath(Graph &g, int r, int t) {
    // Search g starting from r, find and print a shortest path to t

    //Aqui uso la funcion bfs_reachable y lo modifico para buscar el shortest path
    bool *seen = new bool[g.nVertices()];
    //Implemento un auxillary array p
    int *p = new int[g.nVertices()];
    
    for (int i = 0; i < g.nVertices(); i++) {
        seen[i] = false;
        
    }

    ods::SLList<int> q;
    q.add(r);
    seen[r] = true;

    while (q.size() > 0) {
        int i = q.remove();

        ods::ArrayStack<int> edges;
        g.outEdges(i, edges);
        for (int k = 0; k < edges.size(); k++) {
            int j = edges.get(k);
            
            if (!seen[j]) {
                q.add(j);
                p[j] = i;
                seen[j] = true;
            }
        }
    }
    // Aqui chequeamos si encontramos el valor
    if (!seen[t]) {
        delete[] seen;
        delete[] p;
        return false;
    }

    //Esto pone el shortest path en reversa
    //estoy creyendo un array stack porque si imprimo los valores de p directamente sale al reves
    ods::ArrayStack<int> path;

    while (t != r) {

        path.add(t);
        t = p[t];
    }

    path.add(r);

    //Imprime el shortest path
    std::cout << "Shortest path: ";

    for (int i = path.size() - 1; i >= 0; i--) {
        std::cout << path.get(i);

        if (i > 0) {
            std::cout << " -> ";
        }
    }

    std::cout << std::endl;

    delete[] seen;
    delete[] p;

    return true;
}

int main (int argc, char *argv[]) {
  // make sure we were called with 3 arguments
  if (argc < 4) { 
    std::cout << "Usage: " << argv[0] << "<graph> <source> <target> \n"; 
    exit(1);
  }

  ods::AdjacencyLists g = ods::readGraph(argv[1]);
  int start = std::atoi(argv[2]); 
  int target = std::atoi(argv[3]);
  
  // check if we can reach the target, starting from start
  if (shortestPath<ods::AdjacencyLists>(g, start, target)) {
    std::cout << "Found a path from " << start << " to " << target << std::endl;
  } else {
    std::cout << "No path found from " << start << " to " << target << "!\n";
  }
  return 0;
}
