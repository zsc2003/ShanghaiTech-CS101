注：代码是C++17的。编译需要带上`-std=c++17`选项。

## 图的存储与遍历

文件：`graph.cpp`

使用邻接表存储一张图，并实现基本的 dfs 和 bfs 。详见课程公众号推文《图和树的基本实现方式》。

## 并查集

文件：`union-find.cpp`

并查集的基本实现，包括初始化`init`、寻找树根`findfa`和合并`merge`三个函数。这里采用了路径压缩 (path compression) 和按秩合并 (union-by-rank) 优化。

`fa[x]`是`x`所在的树的树根，或者说是`x`所属的集合的“代表元素”。`height[x]`表示以`x`为树根的那棵树的高度，注意`height[x]`的值仅在`fa[x] == x`时有意义。

`init`函数初始化了`n`个集合，其中第`i`个集合仅包含一个元素`i`，其高度是`1`。

`findfa(x)`采用了一个递归的实现：如果当前结点是树根，即`fa[x] == x`，就返回`x`，否则就往上找`findfa(fa[x])`。注意它将`findfa(fa[x])`的返回值又赋给了`fa[x]`，这就是路径压缩。一次`findfa(x)`之后，从`x`到树根的路径上的所有结点都会变成树根的直接孩子。

`merge(x, y)`合并`x`和`y`所在的两个集合，这里采用按秩合并，会根据`height`的大小关系来选择合并方式。当`height[x] == height[y]`时，可以将`x`所在的树并到`y`所在的树上，也可以反过来，但必须将新的树根的`height`值增加`1`。

## 拓扑排序

文件：`topo-sort.cpp`

输入一张有向无环图 (DAG) ，输出它的一个可能的拓扑序。

`indegree[x]`记录了结点`x`的入度。

## 最小生成树

文件：`mst/*`

这里的所有代码都假定边权能被32位带符号整数表示。

`kruskal.cpp`是采用`union-find.cpp`中的并查集实现的 Kruskal 算法。`prim_adjlist.cpp`和`prim_adjmat.cpp`是没有堆优化的朴素 Prim 算法，前者基于邻接表实现，时间复杂度为 $O\left(V^2+E\right)$ ；后者基于邻接矩阵实现，时间复杂度为 $O\left(V^2\right)$ 。`prim_heap.cpp`和`prim_fibheap.cpp`分别是用二叉堆和斐波那契堆优化的 Prim 算法，时间复杂度分别为 $O\left(E\log V\right)$ 和 $O\left(E+V\log V\right)$。

`kruskal.cpp`、`prim_heap.cpp`和`prim_fibheap.cpp`都假定图的结点数不超过 $10^5$ 。`prim_adjlist.cpp`和`prim_adjmat.cpp`假定图的结点数不超过 $5000$ 。

`prim_heap.cpp`基于 C++ 标准库`std::priority_queue`实现。首先，我们需要让 priority queue 知晓每个 push 进去的结点的`dist`值，同时每次从中取出堆顶元素时也需要知道它来自于哪个结点，并且又考虑到`std::priority_queue`默认是 max-heap ，所以我们需要存入堆中的信息应该表示为二元组`(-dist[x], x)`。由于`std::priority_queue`不支持修改其中某一个元素的值，当我们更新一个结点`v`的信息`dist[v]`时，只能将一个新的二元组`(-dist[v], v)`再次加入堆中，这时堆里可能本来有`v`，但它入堆时带有的`dist`信息一定比现在的`dist[v]`大。我们每次从堆中取出一个二元组时，需要先判断它所携带的`dist`信息是不是最新的，如果不是就要跳过：
```cpp
auto [w, x] = heap.top();
heap.pop();
w = -w;
if (w != dist[x])
  continue;
dist[x] = -inf;
```
我们通过将`dist[x]`赋值为`-inf`的方式来保证`x`不会再被入堆。

`prim_fibheap.cpp`基于 Boost 库的`boost::heap::fibonacci_heap`实现。编译这个文件需要先确保你安装了 Boost 库。在我的电脑上 Boost 库位于路径`/usr/local/boost_1_80_0`，所以编译时需要带上`-I /usr/local/boost_1_80_0`。为了保持与标准库接口的一致性， Boost Fibonacci-heap 默认也是 max-heap 。出于和前面相同的原因，我们将二元组`(-dist[x], x)`作为存入堆中的元素。

Boost Fibonacci-heap 提供了所谓的“handle”来指向其内部的元素，从而允许我们指定一个元素并修改它的值。我们首先将所有元素都加入堆，`push`或`emplace`函数会返回指向新元素的 handle ，我们将它们存入一个数组。每次更新一个`dist[v]`时，我们只需调用它的`increase`成员函数，这个函数可以 $O(1)$ 地原地将一个元素的值改大，这样堆中就不会存在重复的结点了。

## 单源最短路径

这里的所有代码都假定边权能被32位带符号整数表示，并且我们没有对负环作任何判定。

### Dijkstra

文件：`shortest_path/dijkstra/*`

`dijkstra_naive.cpp`是朴素的 $O\left(V^2+E\right)$ 实现，它假定输入的图的结点数不超过 $5000$ 。`dijkstra_heap.cpp`和`dijkstra_fibheap.cpp`分别是使用二叉堆和斐波那契堆优化的实现，它们假定结点数不超过 $10^5$ ，时间复杂度分别为 $O\left(E\log V\right)$ 和 $O\left(E+V\log V\right)$ 。

`dijkstra_fibheap.cpp`同样基于 Boost Fibonacci-heap 实现。堆优化的 Dijkstra 算法和 Prim 算法有诸多相似之处，如果对实现细节有疑问请看前面有关 Prim 的段落。

### Bellman-Ford

文件：`shortest_path/bellman_ford/*`

`bellman_ford.cpp`是朴素的 Bellman-Ford 算法实现，它假定图的结点数量不超过 $5000$ ，时间复杂度为 $O(VE)$ 。

`spfa.cpp`是所谓的 Shortest-Path-First-Access (SPFA) 算法，它是基于 Bellman-Ford 的一种改进。注意到： Bellman-Ford 每一次都会遍历所有的边，尝试用它们进行松弛，但在实际情况中这会有大量的冗余，例如在第一次迭代时，只有起点 $s$ 的出边是真正有用的。于是我们不再每次都遍历所有的边，而是维护一个队列，每次从队列中取出一个结点 $x$ ，用 $x$ 的每一条出边 $(x,v)$ 去松弛 $v$ ，并将所有松弛成功的 $v$ 加入队列，这样就避免了枚举许多“显然没用”的边。

SPFA 的时间复杂度仍然为 $O(VE)$ ，但是它在平均情况下表现极好。对于随机生成的点数和边数都在 $10^5$ 级别的图， SPFA 算法中每个结点入队的次数几乎不超过 $10$ ，所以它在随机的测试数据下甚至可以比堆优化的 Dijkstra 还要快，而且代码实现也非常简短。

## 所有点对之间的最短路径

文件：`floyd-warshall.cpp`

非常普通的 Floyd-Warshall 算法实现，没有给出完整的输入输出细节。它假定图的结点数不超过 $2000$ ，边权能被32位带符号整数表示。