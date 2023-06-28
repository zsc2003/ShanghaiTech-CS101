#include<iostream>
#include<cstdio>

inline int read()
{
	int r,s=0,c;
	for(;!isdigit(c=getchar());s=c);
	for(r=c^48;isdigit(c=getchar());(r*=10)+=c^48);
	return s^45?r:-r;
}

const int N=5e6+10;

int n,k;
int a[N];

int main()
{
//	freopen("match_bigsample.in","r",stdin);
//	freopen("match_bigsample.ans","w",stdout);
	n=read(),k=read();
	int val;
	int head=0,tail=0,len;
	for(int i=1;i<=n;++i)
	{
		val=read();
		len=tail-head;
		if(len==k)
			++head,--len;
		if(len>=2)
		{
			if((a[tail-1]==val)&&(a[tail]==val))
				tail-=2;
			else
				a[++tail]=val;
		}
		else
			a[++tail]=val;
	}
	for(int i=1;i<=tail;++i)
		printf("%d ",a[i]);
	return 0;
}
