#include<iostream>
#include<cstdio>
#define ull unsigned long long
using namespace std;
inline int read()
{
	int r,s=0,c;
	for(;!isdigit(c=getchar());s=c);
	for(r=c^48;isdigit(c=getchar());(r*=10)+=c^48);
	return s^45?r:-r;
}
const int N=10000010;
int n,tot,x;
int phi[N],prime[N];
bool vis[N];
ull ans;
int main()
{
	n=read();
	phi[1]=1;
	ans=1;
	for(int i=2;i<=n;i++)
	{
		if(!vis[i])
			phi[i]=i-1,prime[++tot]=i;
		for(int j=1;i*prime[j]<=n&&j<=tot;j++)
		{
			x=i*prime[j];
			vis[x]=1;
			if(i%prime[j])
				phi[x]=phi[i]*(prime[j]-1);
			else
			{
				phi[x]=phi[i]*prime[j];
				break;
			}
		}
	}
	ans=0;
	for(int i=2;i<=n;++i)
		if(!vis[i])
			ans+=(ull)i;
	cout<<ans;
	return 0;
}
