import numpy as np
import sys

# Generate an undirected graph with n vertices and m weighted edges
n = int(sys.argv[1])
m = int(sys.argv[2])

def randWeight():
    return np.random.randint(1, int(1e9))

print(n, m)
edges = set()
for i in range(2, n + 1):
    fa = np.random.randint(1, i)
    weight = randWeight()
    edges.add((fa, i))
    print(i, fa, weight)
for i in range(n - 1, m):
    while True:
        x, y = np.random.randint(1, n + 1, 2)
        while x == y:
            y = np.random.randint(1, n + 1)
        if (x, y) not in edges and (y, x) not in edges:
            break
    edges.add((x, y))
    print(x, y, randWeight())

# the source vertex
print(np.random.randint(1, n + 1))