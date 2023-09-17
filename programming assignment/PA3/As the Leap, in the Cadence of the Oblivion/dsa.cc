#pragma once

#include "dsa.h"

#include <queue>
#include <algorithm>

Graph::Graph(VertexId vertices, std::vector<Edge> edges)
    : vertices(vertices), adj(vertices + 1) {
  for (auto e : edges) adj[e.u].push_back(e);
}

struct node{
  int num;
  Weight val;
  Edge e;
  friend bool operator < (node a, node b)
  {
    return a.val>b.val;
  }
};

void Graph::sssp(VertexId src, std::vector<Weight> &dis) {
  // TODO
  for(int i=1;i<=this->vertices;++i)
    dis[i]=INF;
  dis[src]=0;
  std::priority_queue<node> q;
  node init,new_node;
  init.num=src,init.val=0;
  q.push(init);
  std::vector<bool> vis;
  vis.resize(this->vertices+1);
  while(!q.empty())
  {
    init=q.top();
    q.pop();
    if(vis[init.num])continue;
    vis[init.num]=1;
    for(auto edge : this->adj[init.num])
    {
      if(dis[edge.v]>dis[init.num]+edge.w)
      {
        dis[edge.v]=dis[init.num]+edge.w;
        new_node.num=edge.v;
        new_node.val=dis[edge.v];
        q.push(new_node);
      }
    }
  }
}

void Graph::mst(VertexId src, std::vector<Edge> &mst_edges) {
  // TODO
  std::vector<Weight> dis;
  dis.resize(this->vertices+1);
  for(int i=0;i<=this->vertices;++i)
    dis[i]=INF;
  dis[src]=0;
  std::priority_queue<node> q;
  node init,new_node;
  init.num=src,init.val=0;
  q.push(init);
  std::vector<bool> vis;
  vis.resize(this->vertices+1);
  while(!q.empty())
  {
    init=q.top();
    q.pop();
    if(vis[init.num])continue;
    vis[init.num]=1;
    if(init.num!=src)
      mst_edges.push_back(init.e);
    for(auto edge : this->adj[init.num])
    {
      if(dis[edge.v]>edge.w)
      {
        dis[edge.v]=edge.w;
        new_node.num=edge.v;
        new_node.val=dis[edge.v];
        new_node.e=edge;
        q.push(new_node);
      }
    }
  }
}