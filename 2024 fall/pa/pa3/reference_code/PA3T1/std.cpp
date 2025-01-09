#include<vector>
#include<cstdio>
#include<algorithm>

const int N = 1e5+1;
const int M = 5e5+1;

using std::vector;
using std::sort;

struct edge{
	int u,v,w,c;
	edge(int x,int y,int k,int z):u(x),v(y),w(k),c(z){}
	edge(){}
	bool operator<(const edge& o) const{return w<o.w;}
}e[M];
vector<int> black,white;
vector<int> g[N];
int n,m,k;

int par[N];
int fF(int x){return par[x]==x?par[x]:par[x]=fF(par[x]);}
void fM(int x,int y){x=fF(x),y=fF(y);par[x]=y;} 

int ans = 0;
int wz, bs; 

int check(int x){ 
	int w=0,b=0;
	ans=0;
	for(int i = 0;i<=n;i++)par[i]=i;
	int wc=0,bc=0;
	for(;w<wz || b<bs;){
		if(wc+bc==n-1)break;
		if(w!=wz)
		while(fF(e[white[w]].u)==fF(e[white[w]].v)){
			w++;
			if(w==wz)break;
		}
		if(b!=bs)
		while(fF(e[black[b]].u)==fF(e[black[b]].v)){
			b++;
			if(b==bs)break;
		}
		int ww = w==wz?1e9+7:e[white[w]].w;
		int bx = b==bs?1e9+7:e[black[b]].w;
		ww+= x;
		if(ww>bx){
			ans+=bx;
			fM(e[black[b]].u,e[black[b]].v);
			b++;
			bc++;
		}else{
			ans+=ww;
			fM(e[white[w]].u,e[white[w]].v);
			w++;
			wc++;
		}
	} 
	return wc;
}

int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i = 1;i<=m;i++){
		int x,y,w,c;
		scanf("%d%d%d%d",&x,&y,&w,&c);
		e[i] = edge(x,y,w,c);
	}
	k = n-1-k;
	sort(e+1,e+1+m);
	for(int i = 1;i<=m;i++){
		g[e[i].u].push_back(i);
		g[e[i].v].push_back(i);
		if(e[i].c)black.push_back(i);else white.push_back(i);
	}
	wz = white.size(),bs = black.size();
	int now = 0;
	int l=-10000, r=10000;
	while(r-l>5){
		int mid = (r+l)>>1;
		int _ = check(mid);
		if(_>=k){
			now = mid;
			l = mid+1;
		}else{
			r = mid-1;
		}
	}
	for(int i = l;i<=r;i++){
		int _ = check(i);
		if(_>=k)now = i; 
	}
	check(now);
	printf("%d",ans-now*k);
}
