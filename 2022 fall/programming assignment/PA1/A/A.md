# And Let Galaxy Occupy Devastation Steps

## Background

*Galaxy, what a wonderful word.*

*Yet the living beings of this world have not seen it for I don't know how long.*

## Description

David read. He had just turned up these words in the decaying library where the roof had been lifted off.

He didn't know what the Galaxy was, but he knew that a linked list could help him get closer to where he wanted to go. Now he was building a linked list, with each node on it representing each transfer station. However, since the climate varies very much from place to place in *The First Isolated Island*, he needs some more thoughtful planning. Specifically, he was now maintaining a linked list with three operations:

1. **Insert a new node after** the given location, the node, with the value $v_i$, indicating the local climate type.

2. **Change the value** of the given node. This is due to climate change.

3. Since a certain climate is no longer suitable for human survival, **remove all nodes** with the value $v_i$.

You will play *David* in this problem. Please maintain the specified linked list.

## Input Format

The first line of input contains an integer $n$, indicating the number of operations.

There are three formats for the following $n$ lines. For the $i$-th line,

- `1 k_i v_i`: insert a node with value $v_i$ after the node indexed $k_i$. The new node is indexed $count+1$, where $count$ is the number of **previous operation-1s**. If $k_i=0$, insert at the head of the linked list. Otherwise if the node indexed $k_i$ **does not exist** or **has been removed**, this operation is **invalid**.
- `2 k_i v_i`: change the value of the node indexed $k_i$ to $v_i$. If the node indexed $k_i$ **does not exist** or **has been removed**, this operation is **invalid**.
- `3 v_i`: remove all nodes with value $v_i$.

## Output Format

For each operation, output one line:

- For operation 1, if this operation is **invalid**, output `!`. Otherwise output the values of the nodes before and after the inserted node. If It has **no node before/after it**, output `-1` on the first/second place instead.
- For operation 2, if this operation is **invalid**, output `!`. Otherwise output the value of the node before change.
- For operation 3, output the number of nodes which are removed.

**After the $n$ lines, output one line**: the values of nodes left in the linked list one by one.

## Sample Input

```
7
1 0 123
1 1 456
1 1 123
1 3 789
2 3 789
3 789
1 3 456
```

## Sample Output

```
-1 -1
123 -1
123 456
123 456
123
2
!
123 456
```

## Constraints

| Testcase ID | $n$        | Other Constraints  |
| ----------- | ---------- | ------------------ |
| 1-3         | $\le 2000$ | N/A                |
| 4-6         | $\le 10^5$ | operation 1 only   |
| 7-9         | $\le 10^5$ | operation 1,2 only |
| 10-12       | $\le 10^5$ | operation 1,3 only |
| 13-20       | $\le 10^6$ | N/A                |

For all testcases, $1\leq n\leq 1\times10^6,0\le k_i < n,0< v_i <2^{31}$.


