/*
problem   : candy
author    : Zu Lingkai
algorithm : Linked list
*/
#include<iostream>
using namespace std;
const int N=1e6;
template<typename T>
struct ListNode
{
	T value;
	ListNode *nxt;
	
	ListNode(T _value=T(),ListNode *_nxt=nullptr):value(_value),nxt(_nxt)
	{
	}
	
	void erase_next()
	{
		if(nxt==nullptr||nxt==this) return;
		ListNode *tmp=nxt;
		this->nxt=tmp->nxt;
		delete tmp;
	}
};

template<typename T>
struct SingleList
{
	
	ListNode<T> *head;
	
	SingleList():head(new ListNode<T>())
	{
		head->nxt=head;
	}
	
	void insert_front(T value)
	{
		auto node=new ListNode<T>(value,head->nxt);
		head->nxt=node;
	}
};

template<typename T>
void init_list(int tot,SingleList<T> &list)
{
	for(int i=tot;i>=1;i--)
	{
		list.insert_front(i);
	}
}

bool ans[N+1];

template<typename T>
void solve(int n,int m,int p,SingleList<T> list)
{
	ListNode<T> *node=list.head;
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n;j++)
		{
			ans[node->nxt->value]=(j==n);
			node->erase_next();
			if(node->nxt==list.head)
			{
				node=node->nxt;
			}
			for(int k=1;k<=p;k++)
			{
				node=node->nxt;
				if(node->nxt==list.head)
				{
					node=node->nxt;
				}
			}
		}
	}
	for(int i=1;i<=n*m;i++)
	{
		if(ans[i])
		{
			cout<<i<<" ";
		}
	}
	return;
}
int main()
{
	int n,m,p;
	cin>>n>>m>>p;
	SingleList<int> list;
	init_list(n*m,list);
	solve(n,m,p,list);
	return 0;
}
