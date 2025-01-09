/*
Problem   : RubbishGame
Author    : Zu Lingkai
Algorithm : queue + deque
*/

#include<iostream>
using namespace std;
const int M=4e5;
int cnt[M+1];
struct pkm
{
	int kind,id;
	pkm(int _kind=0,int _id=0):kind(_kind),id(_id)
	{
	}
};

template <typename T>
struct Deque
{
	static const int SIZE=1e6;
	T value[SIZE+1];
	int head,tail;
	
	Deque():head(0),tail(0)
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
	
	T back()
	{
		return value[tail-1];
	}
	
	void push_back(T val)
	{
		value[tail++]=val;
	}
	
	void pop_front()
	{
		head++;
	}
	
	void pop_back()
	{
		tail--;
	}
	
	void clear()
	{
		head=tail=0;
	}
};
Deque<pkm>q;
Deque< pair<int,int> >dq;
void logout(int id)
{
	while(!q.empty()&&q.front().id==id)
	{
		pkm retake=q.front();
		q.pop_front();
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
		q.push_back(summon);
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
		int type;
		cin>>type;
		if(type==1)
		{
			login(p_tail++);
			while(!dq.empty()&&dq.back().first<=cnt[0])
			{
				dq.pop_back();
			}
			dq.push_back({cnt[0],p_tail-1});
		}
		if(type==2)
		{
			cout<<dq.front().first<<endl;
			if(dq.front().second==p_head)
			{
				dq.pop_front();
			}
			logout(p_head++);
		}
	}
	return 0;
}
