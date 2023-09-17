#include<iostream>
#include<cstdio>
#include<queue>
#include<cmath>
#define ll long long

inline int read()
{
	int r,s=0,c;
	for(;!isdigit(c=getchar());s=c);
	for(r=c^48;isdigit(c=getchar());(r*=10)+=c^48);
	return s^45?r:-r;
}

const int N=1000010;
int s[N];

struct edge
{
	int to,next;
}mem[N<<1];
int head[N],cnt;
inline void add(int u,int v)
{
	mem[++cnt].next=head[u];
	mem[cnt].to=v;
	head[u]=cnt;
}

bool vis[N];
struct node{
	int num;
	int step,prenum;
	friend bool operator < (node a,node b)
	{
		return a.step>b.step;
	}
}init,new_node;

void bfs1(ll A,ll D,int n)
{
	std::queue<node> q;
	init.num=1,init.step=0;
	q.push(init);
	while(!q.empty())
	{
		init=q.front();
		q.pop();
		if(init.num==n)
		{
			std::cout<<init.step<<'\n';
			return;
		}
		if(vis[init.num])continue;
		vis[init.num]=1;
		for(int e=head[init.num];e>0;e=mem[e].next)
		{
			int to=mem[e].to;
			if(s[1]+(A-D)*init.step>s[to])
			{
				new_node.num=to,new_node.step=init.step+1;
				q.push(new_node);
			}
		} 
	}
	puts("-1");
	return;
}

void bfs2(ll A,ll D,int n)
{
	int access=0;
	std::priority_queue<node> q;
	init.num=1,init.step=0,init.prenum=0;
	q.push(init);
	while(!q.empty())
	{
		init=q.top();
		q.pop();		
		if(vis[init.num])continue;
		if(init.step>access)continue;
		if(init.num==n)
		{
		//	std::cout<<"access="<<access<<'\n';
			std::cout<<init.step<<'\n';
			return;
		}
		vis[init.num]=1;
		++access;
		for(int e=head[init.num];e>0;e=mem[e].next)
		{
			int to=mem[e].to;
			//std::cout<<"to="<<to<<"s[to]="<<s[to]<<'\n';
			ll step=0;
			if(s[to]>=s[1])
			{
				step=(ll)std::ceil((double)(s[to]-s[1])/(double)(A-D));
				if((ll)(s[to]-s[1])%(A-D)==0)
					++step;
			}
				
			new_node.num=to,new_node.prenum=init.prenum+1;
			new_node.step=std::max(step,(ll)init.step)+1;
			q.push(new_node);
		}
	}
	puts("-1");
	return;
}
int main()
{
	//freopen("AgtD.in","r",stdin);
	//freopen("AgtD.ans","w",stdout);
	int T,n,m,u,v;
	ll A,D;
	T=read();
	while(T--)
	{
		n=read(),m=read(),A=read(),D=read();
		for(int i=1;i<=m;++i)
		{
			u=read(),v=read();
			add(u,v),add(v,u);
		}
		for(int i=1;i<=n;++i)
			s[i]=read();
		
	/*	std::cout<<"\n----------------------\n";
		for(int i=1;i<=n;++i)
			std::cout<<s[i]<<'\n';
		std::cout<<"\n----------------------\n";*/

		if(A<=D)
			bfs1(A,D,n);
		else
			bfs2(A,D,n);
		
		
		for(int i=1;i<=n;++i)
			head[i]=0,vis[i]=0;//check[i]=0;
		cnt=0;
		for(int i=1;i<=2*m;++i)
			mem[i].next=0,mem[i].to=0;
	}
	return 0;
}/*
1
6 5 20 5
1 2
2 3
3 4
4 6
1 5
1 10 10 10 0 10

1
5 4 10 1
1 2
1 3
1 4
1 5
10 1 1 1 22

1
5 4 10 1
1 2
1 4
2 5
1 3
10 20 10 1 1

1
5 4 10 1
1 2
1 3
3 4
4 5
10 1 1 29 1

1
4 4 10 1
1 2
1 3
2 4
3 4
10 9 18 18
*/
