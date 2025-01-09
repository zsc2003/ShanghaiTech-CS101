#include<bits/stdc++.h>
#define DEBUG 0
#define $ if(DEBUG)
#define ll long long
#define db double
#define N 1000005
int n, m, p, ans[N], cnt;
struct node
{
	int l, r;
}s[N];
void erase (int x)
{
	s[s[x].r].l = s[x].l;
	s[s[x].l].r = s[x].r;
}
int main ()
{
	freopen("south.in","r",stdin);
	freopen("south.out","w",stdout);
	scanf ("%d%d%d", &n, &m, &p);
	for (int i = 1; i <= n * m; i++) s[i].l = i - 1, s[i].r = i + 1;
	s[n * m].r = 1, s[1].l = n * m;
	int pos = 1;
	for (int i = 1; i <= n * m; i++)
	{
		if (i % n == 0) ans[++cnt] = pos;
		erase (pos);
		for (int j = 0; j <= p; j++) pos = s[pos].r;
	}
	std::sort (ans + 1, ans + 1 + cnt);
	for (int i = 1; i <= cnt; i++) printf ("%d ", ans[i]);
	return 0;
}