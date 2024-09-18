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
std::vector<int> v[N];
int fa[N];

void dfs(int u,int f)
{
	if(f==pos)
		fa[u]=u;
	else
		fa[u]=fa[f];
	for(auto to : v[u])
	{
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
		v[x].push_back(y),v[y].push_back(x);
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
