#include<iostream>
#include<cstdio>
#include<map> 
#define ll long long
using namespace std;
inline ll read()
{
	ll r,s=0,c;
	for(;!isdigit(c=getchar());s=c);
	for(r=c^48;isdigit(c=getchar());(r*=10)+=c^48);
	return s^45?r:-r;
}
const int N=1000010; 
int n;
ll a[N];
ll s,t;
map<ll,int> mp;
int main()
{
	n=read();
	for(int i=0;i<n;++i)
	{
		a[i]=read();
		mp[a[i]^(ll)i]++;
	}
	s=read();
	for(int i=0;i<n;++i)
	{
		ll now=a[i]^(ll)i;
		t=s^now;
		if(t==now)
		{
			if(mp[t]>=2)
			{
				puts("Yes");
				return 0;
			}
		}
		else
		{
			if(mp[t]>=1)
			{
				puts("Yes");
				return 0;
			}	
		}
	}
	puts("No");
	return 0;
}
