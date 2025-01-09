/*
Problem   : RubbishGame
Author    : Zu Lingkai
Algorithm : queue + brute force
*/

#include<iostream>
using namespace std;
const int N=1e5;
const int M=4e5;
int ans[N+1];
int cnt[M+1];
struct pkm
{
	int kind,id;
	pkm(int _kind=0,int _id=0):kind(_kind),id(_id)
	{
	}
};

template <typename T>
struct Queue
{
	static const int SIZE=1e6;
	T value[SIZE+1];
	int head,tail;
	
	Queue():head(0),tail(0)
	{
	}
	
	bool empty()
	{
		return head==tail;
	}
	
	T front()
	{
		return value[head];
	}
	
	void push(T val)
	{
		value[tail++]=val;
	}
	
	void pop()
	{
		head++;
	}
	
	void clear()
	{
		head=tail=0;
	}
};
Queue<pkm>q;
void logout(int id)
{
	while(!q.empty()&&q.front().id==id)
	{
		pkm retake=q.front();
		q.pop();
		cnt[retake.kind]--;
		if(!cnt[retake.kind])
		{
			cnt[0]--;
		}
	}
}
void login(int id)
{
	int c;
	cin>>c;
	while(c--)
	{
		int x;
		cin>>x;
		pkm summon={x,id};
		q.push(summon);
		if(cnt[summon.kind]==0)
		{
			cnt[0]++;
		}
		cnt[summon.kind]++;
	}
}
int main()
{
	int n;
	cin>>n;
	int p_head=1,p_tail=1;
	for(int i=1;i<=2*n;i++)
	{
		int maxx=0,maxi=0;
		int type;
		cin>>type;
		if(type==1)
		{
			login(p_tail++);
			if(maxx<=cnt[0])
			{
				maxx=cnt[0];
				maxi=p_tail-1;
			}
		}
		if(type==2)
		{
			for(int i=p_head;i<p_tail;i++)
			{
				ans[i]=max(ans[i],cnt[0]);
			}
			cout<<ans[p_head]<<endl;
			logout(p_head++);
		}
	}
	return 0;
}
