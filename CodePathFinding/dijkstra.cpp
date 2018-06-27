#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <utility>
#include <iostream>
#include <vector>
#include <set>
#include <climits>
#include <algorithm>


    struct edge
    {
      int to;
      int length;
    };

    using node = std::vector<edge>;
    using graph = std::vector<node>;

    void add_edge( graph& g, int start, int finish, int length ) {
      if ((int)g.size() <= (std::max)(start, finish)){
        g.resize( (std::max)(start,finish)+1 );
      }
      g[start].push_back( {finish, length} );
      g[finish].push_back( {start, length} );
    }

    using path = std::vector<int>;

    struct result {
      int distance;
      path p;
    };
    result dijkstra(const graph &graph, int source, int target) {
      std::vector<int> min_distance( graph.size(), INT_MAX );
      min_distance[ source ] = 0;
      std::set< std::pair<int,int> > active_vertices;
      active_vertices.insert( {0,source} );

      while (!active_vertices.empty()) {
        int where = active_vertices.begin()->second;
        if (where == target)
        {
          int cost = min_distance[where];
          
          path p{where};
          while (where != source) {
            int next = where;
            for (edge e : graph[where])
            {
     

              if (min_distance[e.to] == INT_MAX)
              {
                
                continue;
              }

              if (e.length + min_distance[e.to] != min_distance[where])
              {
                
                continue;
              }
              next = e.to;
              p.push_back(next);
              
              break;
            }
            if (where==next)
            {
              
              break;
            }
            where = next;
          }
          std::reverse( p.begin(), p.end() );
          return {cost, std::move(p)};
        }
        active_vertices.erase( active_vertices.begin() );
        for (auto ed : graph[where])
          if (min_distance[ed.to] > min_distance[where] + ed.length) {
            active_vertices.erase( { min_distance[ed.to], ed.to } );
            min_distance[ed.to] = min_distance[where] + ed.length;
            active_vertices.insert( { min_distance[ed.to], ed.to } );
          }
      }
      return {INT_MAX};
    }

    int main()
    {
      graph g;	//en fonction de notre map et de nos noeuds (unité arbitraire 2 feuilles) aller retour pour les deux sens de passage
      add_edge(g, 9, 10, 2);
      add_edge(g, 10, 9, 2);
      add_edge(g, 10, 11, 2);
      add_edge(g, 11, 10, 2);
      add_edge(g, 11, 1, 1);
      add_edge(g, 1, 11, 1);
      add_edge(g, 1, 2, 2);
      add_edge(g, 2, 1, 2);
      add_edge(g, 2, 3, 3);
      add_edge(g, 3, 2, 3);
      add_edge(g, 3, 4, 2);
      add_edge(g, 4, 3, 2);
      add_edge(g, 4, 5, 1);
      add_edge(g, 5, 4, 1);
      add_edge(g, 5, 6, 3);
      add_edge(g, 6, 5, 3);
      add_edge(g, 6, 7, 2);
      add_edge(g, 7, 6, 2);
      add_edge(g, 7, 8, 5);
      add_edge(g, 8, 7, 5);
      add_edge(g, 8, 9, 2);
      add_edge(g, 9, 8, 2);
      add_edge(g, 9, 12, 2);
      add_edge(g, 12, 9, 2);
      add_edge(g, 8, 16, 1);
      add_edge(g, 16, 8, 1);
      add_edge(g, 16, 15, 4);
      add_edge(g, 15, 16, 4);
      add_edge(g, 15, 14, 1);
      add_edge(g, 14, 15, 1);
      add_edge(g, 14, 6, 1);
      add_edge(g, 6, 14, 1);
      add_edge(g, 10, 14, 5);
      add_edge(g, 14, 10, 5);
      add_edge(g, 14, 4, 3);
      add_edge(g, 4, 14, 3);
      add_edge(g, 11, 12, 2);
      add_edge(g, 12, 11, 2);
      add_edge(g, 12, 13, 2);
      add_edge(g, 13, 12, 2);
      add_edge(g, 13, 3, 1);
      add_edge(g, 3, 13, 1);




      auto r = dijkstra(g, 10, 7); //entrée clavier dans le code des deux noeuds départ et arrivé
      std::cout << "La longueur du trajet est de " << r.distance << ": ";
      for (int x:r.p) {
        std::cout << "Noeud " << x << " --> ";
      }
      std::cout << "Le trajet le plus court est calculé !\n";

      return 0;
    }


