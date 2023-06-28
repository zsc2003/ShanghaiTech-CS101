#include<iostream>
#include<cstdio>
#include<algorithm>
#include<set>
#define ll long long

inline int read()
{
	int r,s=0,c;
	for(;!isdigit(c=getchar());s=c);
	for(r=c^48;isdigit(c=getchar());(r*=10)+=c^48);
	return s^45?r:-r;
}

const int N=1000010;
const int inf=1e9+7;

struct node
{
	int a,d;
}a[N],b[N];

int main()
{
	int n,m;
	n=read(),m=read();
	for(int i=1;i<=n;++i)
		a[i].a=read(),a[i].d=read();
	for(int i=1;i<=m;++i)
		b[i].a=read(),b[i].d=read();
		
	std::sort(a+1,a+1+n,[](node a,node b){if(a.a!=b.a)return a.a<b.a;return a.d<b.d;});
	std::sort(b+1,b+1+m,[](node a,node b){if(a.a!=b.a)return a.a<b.a;return a.d<b.d;});
	
	std::multiset<int>s;
	s.insert(-inf),s.insert(inf);

	int cnt=1,ans=0;
	for(int i=1;i<=m;++i)
	{
		while(cnt<=n&&a[cnt].a<=b[i].a)
		{
			s.insert(a[cnt].d);
			++cnt;
		}
			
		auto it=s.upper_bound(b[i].d);
		--it;
		if((*it)!=-inf)
		{
			//std::cout<<(*it)<<'\n';
			++ans;
			s.erase(it);
		}
	}
	std::cout<<ans;
	return 0;
}/*
5 5
0 0
1 2
2 0
6 5
7 4

2 0
0 2
3 2
8 5
7 6

*/
