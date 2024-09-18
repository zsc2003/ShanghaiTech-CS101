#include<iostream>
#include<cstdio>
#include<queue>
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
int n,m,k;
int a[N];
 
struct node
{
	int pre,pos,bound;
	ll sum;
	friend bool operator < (node x,node y)
	{
		return x.sum < y.sum;
	}
};
int main()
{
	n=read(),m=read(),k=read();
	for(int i=1;i<=n;++i)
		a[i]=read();
	std::sort(a+1,a+1+n,std::greater<int>());
	//for(int i=1;i<=n;++i)std::cout<<a[i]<<' ';
	ll sum=0;
	for(int i=1;i<=m;++i)
		sum+=(ll)a[i];
	
	std::priority_queue<node> q;
	while(!q.empty())q.pop();
	node init,new_node;
	init.pre=m-1,init.pos=m,init.bound=n,init.sum=sum;
	q.push(init);
	while(!q.empty())
	{
		init=q.top();
		q.pop();
		--k;
		if(k==0)
		{
			std::cout<<init.sum;
			return 0; 
		} 
		if(init.pos<init.bound)
		{
			//16 8 4 2 1
			//16 8 2 -> 16 8 1
			new_node.bound=init.bound;
			new_node.pos=init.pos+1;
			new_node.sum=init.sum-(ll)a[init.pos]+(ll)a[init.pos+1];
			new_node.pre=init.pre;
			q.push(new_node);
		}
		/*
		5 2 4
		5 4 3 2 1
		ans = 7
		*/
		if((init.pre>=1)&&(init.pre+1<init.pos))//&&(init.pre<init.bound)
		{
			//16 8 4 2 1
			//16 8 2 -> 16 4 2
			new_node.pre=init.pre-1;
			new_node.sum=init.sum-(ll)a[init.pre]+(ll)a[init.pre+1];
			new_node.bound=init.pos-1;
			new_node.pos=init.pre+1;
			q.push(new_node);
		}
	}
	puts("-1");
	return 0;
}
