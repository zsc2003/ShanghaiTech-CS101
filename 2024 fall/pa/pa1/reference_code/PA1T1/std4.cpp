/*
problem   : candy
author    : Zu Lingkai
algorithm : Brute force
*/
#include<iostream>
using namespace std;
const int N=1e6;
int vis[N+1];
int get_next(int pos,int tot)
{
	pos=pos%tot+1;
	while(vis[pos])
	{
		pos=pos%tot+1;
	}
	return pos;
}
void solve(int n,int m,int p)
{
	int tot=n*m;
	int front=1;
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n;j++)
		{
			vis[front]=(j==n?-1:1);
			if(i==m&&j==n)
			{
				break;
			}
			front=get_next(front,tot);
			for(int k=1;k<=p;k++)
			{
				front=get_next(front,tot);
			}
		}
	}
	for(int i=1;i<=tot;i++)
	{
		if(vis[i]==-1)
		{
			cout<<i<<" ";
		}
	}
}
int main()
{
	int n,m,p;
	cin>>n>>m>>p;
	solve(n,m,p);
	return 0;
}
