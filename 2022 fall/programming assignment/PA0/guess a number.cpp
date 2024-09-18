#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
inline int read()
{
	int r,s=0,c;
	for(;!isdigit(c=getchar());s=c);
	for(r=c^48;isdigit(c=getchar());(r*=10)+=c^48);
	return s^45?r:-r;
}
char s[1100];
int main()
{
	int ans=-1;
	for(int i=0;i<9;++i)
	{
		printf("? %d\n",i);
		cin>>s;
		if(s[0]=='s')
			continue;
		else
		{
			ans=i;
			break;
		}
	}
	if(ans==-1)
		ans=9;
	printf("! %d\n",ans);
	return 0;
}
