#include<iostream>
#include<cstdio>
#include<map>

inline int read()
{
	int r,s=0,c;
	for(;!isdigit(c=getchar());s=c);
	for(r=c^48;isdigit(c=getchar());(r*=10)+=c^48);
	return s^45?r:-r;
}

const int N=1e6+10;

struct Node{
	Node(int m_idx,int m_val) : idx(m_idx), val(m_val), nxt(nullptr), pre(nullptr) {};
	int idx;
	int val;
	Node* nxt;
	Node* pre;
};
Node* pos_node[N];

struct link_val
{
	link_val(int m_idx,int m_val) : idx(m_idx), val(m_val), nxt(nullptr), pre(nullptr) {};
	int idx;
	int val;
	link_val* nxt;
	link_val* pre;
};
link_val* pos_val[N];
std::map<int,link_val*> mp;

Node* head_node; 
bool insert(int idx,int k,int v,int* pre,int* nxt)
{
	Node* new_node = new Node(idx,v);
	link_val* new_val=new link_val(idx,v);
	if(k==0)
	{
		*pre=-1;
		if(head_node==nullptr)
			*nxt=-1;	
		else
		{
			*nxt=head_node->val;
			new_node->nxt=head_node;
			head_node->pre=new_node;
			new_val->nxt=mp[v];
			if(mp[v]!=nullptr)
				mp[v]->pre=new_val;
		}
		pos_node[idx]=new_node;
		head_node=new_node;
		pos_val[idx]=new_val;
		mp[v]=new_val; 
		return true;
	}
	if(pos_node[k]==nullptr)
	{
		delete new_node;
		delete new_val;
		return false; 
	}
	*pre=pos_node[k]->val;
	if(pos_node[k]->nxt==nullptr)
		*nxt=-1;
	else
	{
		*nxt=pos_node[k]->nxt->val;
		pos_node[k]->nxt->pre=new_node;
	}
	new_node->pre=pos_node[k];
	new_node->nxt=pos_node[k]->nxt;
	pos_node[k]->nxt=new_node;
	pos_node[idx]=new_node;
	
	if(mp[v]!=nullptr)
	{
		new_val->nxt=mp[v];
		mp[v]->pre=new_val;
	}
	mp[v]=new_val;
	pos_val[idx]=new_val;	
	return true;
}

bool modify(int k,int v,int* val)
{
	if(pos_node[k]==nullptr)
		return false;
	*val=pos_node[k]->val;
	pos_node[k]->val=v;
	
	if(pos_val[k]==mp[pos_val[k]->val])
	{
		if(mp[pos_val[k]->val]->nxt==nullptr)
			mp[pos_val[k]->val]=nullptr;
		else
		{
			mp[pos_val[k]->val]->nxt->pre=nullptr;
			mp[pos_val[k]->val]=mp[pos_val[k]->val]->nxt;
		}
	}
	else
	{
		if(pos_val[k]->nxt!=nullptr)
			pos_val[k]->nxt->pre=pos_val[k]->pre;	
		pos_val[k]->pre->nxt=pos_val[k]->nxt;
	}
	pos_val[k]->pre=nullptr;
	if(mp[v]!=nullptr)
	{
		mp[v]->pre=pos_val[k];
		pos_val[k]->nxt=mp[v];
	}
	else
		pos_val[k]->nxt=nullptr;
	mp[v]=pos_val[k];
	pos_val[k]->val=v;
	return true;
}

int remove(int v)
{
	if(mp[v]==nullptr)
		return 0;
	int ans=0;
	link_val* head=mp[v];
	mp[v]=nullptr;
	while(head!=nullptr)
	{
		++ans;
		int pos=head->idx;
		Node* ptr=pos_node[pos];
		if(ptr==head_node)
		{
			if(ptr->nxt==nullptr)
				head_node=nullptr;
			else
			{
				ptr->nxt->pre=nullptr;
				head_node=ptr->nxt;
			}
		}
		else
		{
			ptr->pre->nxt=ptr->nxt;
			if(ptr->nxt!=nullptr)
				ptr->nxt->pre=ptr->pre;
		}
		link_val* old_val=head;
		head=head->nxt;
		
		pos_node[pos]=nullptr;
		pos_val[pos]=nullptr;
		delete old_val;
		delete ptr;
	}
	return ans;
}

void print()
{
	Node* old_node;
	while(head_node!=nullptr)
	{
		old_node=head_node;
		//std::cout<<head_node->val<<' ';
		printf("%d ",head_node->val);
		head_node=head_node->nxt;
		delete old_node;
	}
}

void debug(int i)
{
	std::cout<<"i="<<i<<'\n';
	Node* ptr=head_node;
	while(ptr!=nullptr)
	{
		std::cout<<ptr->idx<<' ';
		ptr=ptr->nxt;
	}
	std::cout<<'\n';
}

int main()
{
//	freopen("list_bigsample.in","r",stdin);
// 	freopen("list_bigsample.ans","w",stdout);

	int n;
	int opt,k,v;
	head_node=nullptr;
	n=read();
	
//	for(int i=1;i<=n;++i)
//		pos_node[i]=nullptr,pos_val[i]=nullptr;
	
	int cnt=0;
	for(int i=1;i<=n;++i)
	{
		opt=read();
		if(opt==1)
		{
			++cnt;
			int pre=0,nxt=0;
			k=read(),v=read();

			if(insert(cnt,k,v,&pre,&nxt)==false)
			{
				puts("!");
				--cnt;
			}
			else
			{
				//std::cout<<pre<<' '<<nxt<<'\n';
				printf("%d %d\n",pre,nxt);
			}
				
		}
		else if(opt==2)
		{
			int val=0;
			k=read(),v=read();
			if(modify(k,v,&val)==false)
				puts("!");
			else
			{
				printf("%d\n",val);
				//std::cout<<val<<'\n';
			}
					
		}
		else if(opt==3)
		{
			v=read();
			//std::cout<<remove(v)<<'\n';
			printf("%d\n",remove(v));
		}
		//debug(cnt);
	}
	print();
	return 0;
}
