#include<iostream>
#include<cstdio>

inline int read()
{
	int r,s=0,c;
	for(;!isdigit(c=getchar());s=c);
	for(r=c^48;isdigit(c=getchar());(r*=10)+=c^48);
	return s^45?r:-r;
}

const int N=100010;
int a[N];
int n;
int ans[N];
int minn[N],maxn[N];
int num[N<<1];

void calc(int l,int r)
{
	if(l==r)
	{
		ans[l]=1;
		return;
	}
	
	int mid=(l+r)>>1;
	calc(l,mid);
	calc(mid+1,r);
	
	minn[mid]=maxn[mid]=a[mid];
	for(int i=mid-1;i>=l;--i)
	{
		minn[i]=std::min(a[i],minn[i+1]);
		maxn[i]=std::max(a[i],maxn[i+1]);
	}
	
	minn[mid+1]=maxn[mid+1]=a[mid+1];
	for(int i=mid+2;i<=r;++i)
	{
		minn[i]=std::min(a[i],minn[i-1]);
		maxn[i]=std::max(a[i],maxn[i-1]);
	}
	
	//min,max都在左侧
	//区间[i,j] 
	//maxn[i]-minn[i]=j-i
	//j=i+maxn-minn
	for(int i=mid;i>=l;--i)
	{
		int j=i+maxn[i]-minn[i];
		if((mid<j)&&(j<=r))
		{
			if((maxn[j]<maxn[i])&&(minn[i]<minn[j]))
				++ans[i];
		}
	}
	
	//min,max都在右侧
	//区间[i,j] 
	//maxn[j]-minn[j]=j-i
	//i=j-(maxn-minn)
	for(int j=mid+1;j<=r;++j)
	{
		int i=j-(maxn[j]-minn[j]);
		if((l<=i)&&(i<=mid))
		{
			if((maxn[i]<maxn[j])&&(minn[j]<minn[i]))
				++ans[i];
		}
	}
	
	//min左,max右
	//区间[i,j]
	//maxn[j]-minn[i]=j-i
	//minn[i]-i=maxn[j]-j
	int lpos=mid+1,rpos=mid;//legal range
	for(int i=mid;i>=l;--i)
	{
		//std::cout<<lpos<<" "<<rpos<<'\n'; 
		//while((rpos+1<=r)&&(minn[i]<minn[rpos+1])&&(maxn[i]<maxn[rpos+1]))
		while((rpos+1<=r)&&(minn[rpos+1]>minn[i]))
		{
			++rpos;
			++num[maxn[rpos]-rpos+N];
			//std::cout<<"l="<<i<<"  r="<<rpos<<' '<<maxn[rpos]+rpos<<'\n';
		}
		//while((lpos<=rpos)&&((minn[i]>minn[lpos])||(maxn[i]>maxn[lpos])))
		while((lpos<=rpos)&&(maxn[lpos]<maxn[i]))
		{
			--num[maxn[lpos]-lpos+N];
			++lpos;
		}
		ans[i]+=num[minn[i]-i+N];
	}
	while(lpos<=rpos)
	{
		--num[maxn[lpos]-lpos+N];
		++lpos;
	}
	
	//min右,max左
	//区间[i,j]
	//maxn[i]-minn[j]=j-i
	//maxn[i]+i=minn[j]+j
	lpos=mid+1,rpos=mid;//legal range
	for(int i=mid;i>=l;--i)
	{
		//while((rpos+1<=r)&&(minn[rpos+1]<minn[i])&&(maxn[rpos+1]<maxn[i]))
		while((rpos+1<=r)&&(maxn[rpos+1]<maxn[i]))
		{
			++rpos;
			++num[minn[rpos]+rpos];
		}
		//while((lpos<=rpos)&&((minn[lpos]>minn[i])||(maxn[lpos]>maxn[i])))
		while((lpos<=rpos)&&(minn[lpos]>minn[i]))
		{
			--num[minn[lpos]+lpos];
			++lpos;
		}
		ans[i]+=num[maxn[i]+i];
	}
	while(lpos<=rpos)
	{
		--num[minn[lpos]+lpos];
		++lpos;
	}
}
int main()
{
	n=read();
	for(int i=1;i<=n;++i)
		a[i]=read();
		
	calc(1,n);
	
	for(int i=1;i<=n;++i)
		printf("%d ",ans[i]);
		//std::cout<<ans[i]<<' ';
	return 0;
}
