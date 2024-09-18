#pragma once

#include <cstdint>
#include <limits>
#include <vector>

// vertex index, 1-based: the input graph has no more than 1e6 vertices.
using VertexId = uint32_t;
// edge index, 0-based: the graph has no more than 1e6 edges.
using EdgeId = uint32_t;
// edge weight: non-negative, `0<w && w<1e9` for every edge
using Weight = uint64_t;
// positive infinity: watch out, arithmetic overflow
const Weight INF = std::numeric_limits<Weight>::max();

// An directed edge from `u` to `v` with (non-negative) weight `w`
struct Edge {
  VertexId u, v;
  Weight w;
};

class Graph {
 public:
  Graph() = delete;
  ~Graph() = default;
  Graph(const Graph &) = delete;
  Graph(Graph &&) = delete;
  void operator=(const Graph &) = delete;
  void operator=(Graph &&) = delete;

  // Construct a graph
  // - The vertices are `{1,2,3.. vertices}`
  // - The directed edges are `edges`
  // - For a undirected graph, the edge e={u,v} is given as a pair of edge
  // `Edge{u,v,w}` and `Edge{v,u,w}`
  // - It is guaranteed that no the input contains no self-loop or multi-edge
  explicit Graph(VertexId vertices, std::vector<Edge> edges);

  // Use Dijkstra's algorithm to find the shortest path from `src` to each
  // vertex and store the result in `dis`.
  //
  // It is guaranteed that
  // - Only called on directed graph.
  // - `dis.size() == this->vertices + 1`, the elements in `dis` are initialized
  // to zero.
  // - `src<=this->vertices && 0<src`
  // - `src` can reach every other vertex
  void sssp(VertexId src, std::vector<Weight> &dis);

  // Use Prim's algorithm to find a minimum spanning tree of the graph,
  // starting from `src`.
  //
  // store the edges in the MST to `mst_edges`.
  // - For every undirected edge `e={u,v}` in the MST, you should add either
  // `Edge{u,v,w}` or `Edge{v,u,w}` to `mst_edges`
  //
  // It is guaranteed that
  // - Only called on un-directed graph.
  // - `mst_edges.size()==0`
  // - `src<=this->vertices && 0<src`
  // - graph is connected
  void mst(VertexId src, std::vector<Edge> &mst_edges);

 private:
  // number of vertices
  VertexId vertices;
  // number of edges
  EdgeId edges;
  // adjacency list, stored in vector of vector of edge.
  // `adj[u]` contains all the edges `Edge{x,y,z}` in the graph such that `x=u`.
  // That is: `adj[u]` is the out-going edges of `u`
  std::vector<std::vector<Edge>> adj;
};