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

struct Node{
	Node(int m_val) : val(m_val), nxt(nullptr), pre(nullptr) {};
	int val;
	Node* nxt;
	Node* pre;
};
Node* head;
Node* tail; 

int n,k;
int a[N];

void print()
{
	Node* old_node;
	while(head!=nullptr)
	{
		std::cout<<head->val<<' ';
		old_node=head;
		head=head->nxt;
		delete old_node;
	}
}
int main()
{
//	freopen("match_bigsample.in","r",stdin);
//	freopen("match_bigsample.ans","w",stdout);
	//std::cout<<sizeof(Node); 
	n=read(),k=read();
	a[n+1]=-1e9;
	for(int i=1;i<=n;++i)
		a[i]=read();
	if(k<=2)
	{
		for(int i=1;i<=n;++i)
			std::cout<<a[i]<<' ';
		return 0;
	}
	head=nullptr,tail=nullptr;
	int num=0;
	Node *pre1,*pre2;
	for(int i=1;i<=n;++i)
	{
		Node* new_node=new Node(a[i]);
		if(head==nullptr)
		{
			head=new_node;
			tail=new_node;
			++num;
			continue;
		}
		if(num==k)
		{
			std::cout<<head->val<<' ';
			Node* old_node=head;
			head->nxt->pre=nullptr;
			head=head->nxt;
			--num;
			delete old_node;
		}
		pre1=tail;// tail != nullptr
		pre2=pre1->pre;		
		if(pre2==nullptr)
		{
			++num;
			tail->nxt=new_node;
			new_node->pre=tail;
			tail=new_node;
			continue;
		}
		if((pre1->val==a[i])&&(pre2->val==a[i]))
		{
			num-=2;
			tail=pre2->pre;
			delete new_node;
			delete pre1;
			delete pre2;
			if(tail==nullptr)
				head=nullptr;
			else
				tail->nxt=nullptr;
			continue;
		}
		++num;
		tail->nxt=new_node;
		new_node->pre=tail;
		tail=new_node;
	}
	print();
	return 0;
}
