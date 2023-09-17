#include<iostream>
#include<cstdio>
#include<algorithm>
#define ll long long

inline int read()
{
	int r,s=0,c;
	for(;!isdigit(c=getchar());s=c);
	for(r=c^48;isdigit(c=getchar());(r*=10)+=c^48);
	return s^45?r:-r;
}

const int N=1000010;

struct node
{
	int x,y,val;
}a[N<<1];

int fa[N];
inline int getfa(int x)
{
	if(fa[x]!=x)
		fa[x]=getfa(fa[x]);
	return fa[x];
}
int main()
{
	int n,m,f,cnt=0;
	n=read(),m=read();
	for(int i=1;i<=n;++i)
	{
		f=read();
		a[++cnt]={n+1,i,f};
	}
	int x,y,val;
	while(m--)
	{
		x=read(),y=read(),val=read();
		a[++cnt]={x,y,val};
	}
	
	std::sort(a+1,a+1+cnt,[](node a,node b){return a.val<b.val;});
	for(int i=1;i<=n+1;++i)
		fa[i]=i;
	
	int f1,f2,num=0;
	ll ans=0;
	for(int i=1;i<=cnt;++i)
	{
		f1=getfa(a[i].x),f2=getfa(a[i].y);
		if(f1!=f2)
		{
			++num;
			fa[f1]=f2;
			ans+=(ll)a[i].val;
			if(num==n)
				break;
		}
	}
	std::cout<<ans;
	return 0;
}
