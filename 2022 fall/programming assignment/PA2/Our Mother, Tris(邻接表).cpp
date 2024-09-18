#include<iostream>
#include<cstdio>
#include<vector>

inline int read()
{
	int r,s=0,c;
	for(;!isdigit(c=getchar());s=c);
	for(r=c^48;isdigit(c=getchar());(r*=10)+=c^48);
	return s^45?r:-r;
}

const int N = 1000010; 
int n,q;
int minn,pos;
int val;

struct edge{
	int to,next;
}mem[N<<1];
int head[N],cnt;
inline void add(int u,int v)
{
	mem[++cnt].next=head[u];
	mem[cnt].to=v;
	head[u]=cnt; 
}
int fa[N];

void dfs(int u,int f)
{
	if(f==pos)
		fa[u]=u;
	else
		fa[u]=fa[f];
	for(int e=head[u];e!=0;e=mem[e].next)
	{
		int to=mem[e].to;
		if(to==f)
			continue;
		dfs(to,u);
	}
} 
int main()
{
	n=read(),q=read();
	minn=1e9+7;
	for(int i=1;i<=n;++i)
	{
		val=read();
		if(minn>val)
		{
			minn=val;
			pos=i;
		}
	}
	int x,y;
	for(int i=1;i<n;++i)
	{
		x=read(),y=read();
		add(x,y),add(y,x);
	}
	//std::cout<<'\n'<<'\n'<<pos<<'\n'<<'\n';
	dfs(pos,pos);
	//std::cout<<'\n'<<'\n';for(int i=1;i<=n;++i)std::cout<<fa[i]<<' ';std::cout<<'\n'<<'\n';
	while(q--)
	{
		x=read(),y=read();
		if(fa[x]==fa[y])
			puts("David");
		else
			puts("Abigail");
	}
	return 0;
}
