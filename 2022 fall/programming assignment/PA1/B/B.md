# Among Leaves Generating Offspring, David Says

## Background

“It's outrageous...”

The maiden scratched her hair again. She loved doing that.

"Ugh... Can't find it."

The lad crumpled his hash table into his left hand. Then his left hand began to burn with a white flame, white smoke seeping out of his fingers.

"There's a whole f\*\*king twenty-one counties to the south, and we're not going to make it this far."

The maiden casually sorted through the electronic files next to her, but of course, nothing was found.

"But I feel the strangest thing is that none of the many life forms met here ...... It feels like the density of life is far lower than we thought."

"It's still *the Whites* who have the most. They are unbearable."

"They're just jealous of your blue hair."

"You're right. But, blue hair ...... All the lifeforms say they have never seen blue hair."

The sky was blue too, yes. But she was now tempted to shoot the small craft down.

"Don't shoot, Abigail."

The lad jumped off the bench he was sitting on - technically, it was a bed that had been cut down vertically with half of it left - and walked over to the maiden.

"It shouldn't be able to answer our questions. 



Who...... are we?"

## Description

> The definition of cache and memory is TOTALLY different from the reality. Please refer to the description of this problem.

The task of archiving the data was also thrown to David by Abigail, but fortunately she had some conscience and the task was not too complicated for David.

Specifically, David now needed to store $n$ elements of a sequence **from front to back** into a cache **one by one**. Each element's information could be represented by an integer $a_i$.

David soon discovered that such storage was redundant with information. He found that if there were **three or more consecutive and identical elements** in the cache sequence at any time, they were all meaningless, needing **to be cleared immediately**.

If the element withstood the redundancy detection, he would store the element in memory. Thus, if the size of the current cache was equal to $k$ and a new element was about to enter **(whether this element was redundant or not)**, the oldest element in the cache should be moved out and deposited into memory and the new element would be store at the end. Also, if all elements of the input sequence had been considered, the remaining elements in the cache were deposited into memory in the order from oldest to newest.

Now David needed to sort out the final sequence of elements in memory.

You will play *David* in this problem. Please dedicate the final sequence to Abigail.

## Input Format

The first line of input contains two integer $n,k$.

The second line of input contains $n$ integers, indicating $a_i$.

## Output Format

The only line of output contains several numbers, indicating the final sequence.

## Samples

### Sample 1 Input

```jsx
5 4
0 1 2 2 2
```

### Sample 1 Output

```jsx
0 1
```

### Sample 2 Input

```jsx
5 3
0 1 2 2 2
```

### Sample 2 Output

```jsx
0 1
```

### Sample 3 Input

```jsx
11 5
0 1 1 0 2 2 2 1 1 3 2
```

### Sample 3 Output

```jsx
0 1 1 0 1 1 3 2
```

## Hint

For the first sample, here is a simulation:

The first step:

| 0 | | | |
| --- | --- | --- | ---|

The second step:

| 0 | 1 | | |
| --- | --- | --- | ---|

The third step:

| 0 | 1 | 2 | |
| --- | --- | --- | ---|

The fourth step:

| 0 | 1 | 2 | 2 |
| --- | --- | --- | ---|

The fifth step:

| 1 | 2 | 2 | 2 |
| --- | --- | --- | ---|

$\to$

| 1 |  |  |  |
| --- | --- | --- | ---|

## Constraints

| Testcase ID | $n$       | Other Constraints |
| ----------- | ------- | ----------------- |
| 1-2         | $\le10$ | N/A               |
| 3-5         | $\le10^5$       | $a_i\le1$                |
| 6-8         | $\le10^5$       | $k=n$                 |
| 9-12        | $\le2000$       | N/A               |
| 13-20       | $\le5\times10^6$       | N/A               |

For all testcases, $1\le k\le n\le 5\times10^6,1\le a_i\le 10^9$.

