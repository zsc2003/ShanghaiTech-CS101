#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

#include "dsa.h"

#define CHK(cond)              \
  do {                         \
    if (!(cond)) return false; \
  } while (0)

int main() {
  // directed
  auto g0 = Graph{5, std::vector{
                         Edge{1, 2, 7},
                         Edge{1, 3, 3},
                         Edge{2, 3, 1},
                         Edge{2, 4, 3},
                         Edge{3, 5, 10},
                         Edge{4, 5, 8},
                         Edge{5, 1, 8},
                     }};
  std::vector<Weight> dis(5, 0);
  g0.sssp(1, dis);
  for (VertexId i = 1; i <= 5; i++) {
    printf("shortest %u->%u: %u", 1, i, (uint32_t)dis[i]);
  }

  // undirected
  auto g1 = Graph{5, std::vector{
                         // w(1,2) = 7
                         Edge{1, 2, 7},
                         Edge{2, 1, 7},
                         // w(1,3) = 3
                         Edge{1, 3, 3},
                         Edge{3, 1, 3},
                         // w(1,4) = 1
                         Edge{1, 4, 1},
                         Edge{1, 4, 1},
                         // w(2,3) = 3
                         Edge{2, 3, 3},
                         Edge{2, 3, 3},
                         // w(2,5) = 90
                         Edge{2, 5, 90},
                         Edge{2, 5, 90},
                     }};
  std::vector<Edge> mst_edges;
  g1.mst(2, mst_edges);
  for (auto e : mst_edges) {
    printf("edge{%u-%u} wight=%u on MST", e.u, e.v, (uint32_t)e.w);
  }

  return 0;
}