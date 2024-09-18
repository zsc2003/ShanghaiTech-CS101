# Abigail Leads Granules Over Dawn Slog

## Background

There are not answers everywhere. All living things will eventually realize that there are too many things for which no answers can be found.

But, they seemed to have found the answer.

The yellow sand in the southeast corner was huge, and it did not seem to have been like this before. They did not really know why they know it was before, but the answer is so.

None of this was the point, though.

The tape in Abigail's hand - it was spinning. Its raspy voice slowly read out... 

a signal.

## Description

Abigail did not actually hate yellow sands because she could sort them exactly by weight. Now she had had an unsorted sequence of sand $(a_1,a_2,\dots,a_n)$ and had ordered the $n$ grains of sand with an insertion sort. To make it easier for the inhabitants of *The First Isolated Island* to make no mistakes in understanding, her insertion sort looked like this.

```cpp
for(int i = 1; i <= n; ++i)
	for(int j = i; j > 1; --j)
		if(a[j - 1] > a[j])
		{
			int tmp = a[j - 1];
			a[j - 1] = a[j];
			a[j] = tmp;
		}
		else
			break;
```

She believed that everyone knew C++, so she used C++ code when she showed it to the residents of *The First Isolated Island* as well.

However, because she was so busy examining the traces of civilization with David, she forgot the sequence of the sands she had picked. Fortunately, she remembered that all sands are different (which means there is no identical elements in $\{a_i\}$) and found a sequence $s_i$ stored in David's database, and it took her $\frac1{998244353}​$ seconds to quickly recall the meaning of the sequence:

$s_i$ means when $j=s_i$, the inner cycle will break (which means $a_i $ has swapped with $a_{i-1},a_{i-2},\dots,a_{s_i}$ and stopped at $j=s_i$). if $s_i=1$, the inner cycle will end after $j=1$.

Since it was too much trouble to sort the sand again, she decided to let it rot *(aka bailan)*. Now she just needed to know the index of the $k$-th smallest element in the initial unsorted sequence.

You will play *Abigail* in this problem. Please do not let it rot.

## Input Format

The first line of input contains two integers $n,k$.

The second line contains $n$ integers, indicating $s_1,s_2,\dots,s_n$ respectively.

## Output Format

The only line of output contains one integer, indicating the index of the $k$-th smallest element in the initial unsorted sequence.

## Sample Input

```cpp
6 1
1 1 2 1 1 3
```

## Sample Output

```
5
```

## Hint

A valid initial sequence is 6 4 5 2 1 3.

## Constraints

| Testcase ID | $n$    | Other Constraints        |
| ----------- | ---- | ------------------------ |
| 1-2         | $\le10$    | N/A                      |
| 3-5         | $\le 10^5$    | $s_i$ is strictly increasing |
| 6-8         | $\le 10^5$    | $k=1$                     |
| 9-12        | $\le 5000$    | N/A                      |
| 13-20       | $\le 10^7$    | N/A                      |

For all testcases, $1\le k\le n\le 10^7$.


