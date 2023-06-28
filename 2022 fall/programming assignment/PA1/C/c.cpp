#include<iostream>
#include<cstdio>

inline int read()
{
	int r,s=0,c;
	for(;!isdigit(c=getchar());s=c);
	for(r=c^48;isdigit(c=getchar());(r*=10)+=c^48);
	return s^45?r:-r;
}

const int N=1e7+10;

int n,k;
int s[N];

int main()
{
//	freopen("crack_bigsample.in","r",stdin);
//	freopen("crack_bigsample.ans","w",stdout);
	
	n=read(),k=read();
	for(int i=1;i<=n;++i)
		s[i]=read();
	int ans=0;
	for(int i=n;i>=1;--i)
	{
		if(s[i]==k)
		{
			ans=i;
			break;
		}
		if(s[i]<k)
			--k;
	}
	std::cout<<ans;
	return 0;
}
