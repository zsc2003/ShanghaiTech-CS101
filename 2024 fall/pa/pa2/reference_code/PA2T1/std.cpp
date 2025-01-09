#include<cstdio> 

const int MAXN = 1e6+1;

int par[MAXN],lc[MAXN],rc[MAXN],color[MAXN];

int tot[MAXN];


int coeff = 1009, emp = 0,dep = 1e6+577; // Prime is ok
unsigned long long hashl[MAXN],hashr[MAXN];

int dfs(int u){
	if(u==0) return 0;
	tot[u] = (dfs(lc[u])+dfs(rc[u])+1);
	hashl[u] += tot[u]*3 + color[u] + dep*(hashl[lc[u]] + hashl[rc[u]]*coeff);
	hashr[u] += tot[u]*3 + color[u] + dep*(hashr[lc[u]]*coeff + hashr[rc[u]]);
	return tot[u];
}


int n;

int ans = 1;

int main(){
	scanf("%d",&n);
	for(int i = 1;i<=n ;i++){
		scanf("%d",color+i);
	}
	for(int i = 1;i<=n;i++){
		scanf("%d%d",lc+i,rc+i);
		if(lc[i]==-1)lc[i] = 0;
		if(rc[i]==-1)rc[i] = 0;
	}
	dfs(1);
	if(hashl[lc[1]]==hashr[rc[1]]){
		printf("%d",n);
		return 0;
	}
	for(int u = 2;u<=n;u++){
		if(ans>=tot[u])continue;
		if(hashl[lc[u]] == hashr[rc[u]] )ans = tot[u];
	}
	printf("%d",ans);
}
