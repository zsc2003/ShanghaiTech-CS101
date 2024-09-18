#include<iostream>
#include<cstdio>
#include<queue>
#define ll long long

inline int read()
{
	int r,s=0,c;
	for(;!isdigit(c=getchar());s=c);
	for(r=c^48;isdigit(c=getchar());(r*=10)+=c^48);
	return s^45?r:-r;
}

const int N=1000010;

struct edge{
	int to,next,val;
}mem[N<<2];
int head[N],cnt;

inline void add(int u,int v,int val)
{
	mem[++cnt].next=head[u];
	mem[cnt].to=v;
	mem[cnt].val=val;
	head[u]=cnt;
}

struct node
{
	int num,val;
	friend bool operator < (node a,node b)
	{
		return a.val>b.val;
	}
}init,new_node;

int d[N];
bool vis[N];
ll prim(int s)
{
	ll ans=0;
	for(int i=1;i<s;++i)
		d[i]=1e9+7;
	d[s]=0;
	std::priority_queue<node> q;
	init.num=s,init.val=0;
	q.push(init);
	while(!q.empty())
	{
		init=q.top();
		q.pop();
		if(vis[init.num])continue;
		vis[init.num]=1;
		ans+=(ll)init.val;
		for(int e=head[init.num];e>0;e=mem[e].next)
		{
			int to=mem[e].to;
			if(d[to]>mem[e].val)
			{
				d[to]=mem[e].val;
				new_node.val=d[to];
				new_node.num=to;
				q.push(new_node);
			}
		}
	}
	return ans;
}
int main()
{
	int n,m,f;
	n=read(),m=read();
	for(int i=1;i<=n;++i)
	{
		f=read();
		add(n+1,i,f);
		add(i,n+1,f);
	}
	int x,y,val;
	while(m--)
	{
		x=read(),y=read(),val=read();
		add(x,y,val);
		add(y,x,val);
	}
	
	std::cout<<prim(n+1);
	return 0;
}
