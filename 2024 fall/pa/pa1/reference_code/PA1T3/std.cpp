/*
prolebm   : HackTheQuicksort
author    : Zu Lingkai
algorithm : Brute force?
*/
#include<iostream>
#include<random>
using std::cin;
using std::cout;
using std::endl;
using std::swap;
static std::mt19937 eng;
int _rand(int L,int R)
{
	return std::uniform_int_distribution<int>(L,R)(eng);
}
const int N=1e5;
int pos[N];
int ans[N];
void hack2(int n)
{
	for(int i=0;i<n;i++)
	{
		int pivot=_rand(i,n-1);
		swap(pos[i],pos[pivot]);
	}
}
void hack3(int n)
{
	for(int i=0;n-i>2;i+=2)
	{
		int p1=_rand(i,n-1);
		int p2=_rand(i,n-2);
		int p3=_rand(i,n-3);
		p3+=(p3>=p2);
		p3+=(p3>=p1);
		p2+=(p2>=p1);
		if(p1==i&&p2!=i+1)
		{
			swap(pos[i+1],pos[p2]);
		}
		else
		{
			swap(pos[i],pos[p2]);
			swap(pos[i+1],pos[p1]);
			swap(pos[i],pos[i+1]);
		}
		
	}
}
void solve(int p,int n)
{
	for(int i=0;i<n;i++)
	{
		pos[i]=i;
	}
	if(p==1)
	{
		//do_nothing
	}
	else if(p==2)
	{
		hack2(n);
	}
	else if(p==3)
	{
		hack3(n);
	}
	for(int i=0;i<n;i++)
	{
		ans[pos[i]]=i;
	}
}
int main()
{
	int p,seed;
	cin>>p>>seed;
	eng.seed(seed);
	int n=1e5;
	solve(p,n);
	for(int i=0;i<n;i++)
	{
		cout<<ans[i]<<" ";
	}
	return 0;
}
