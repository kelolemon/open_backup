# include <cstdio>
# include <cmath>
# include <algorithm>

using namespace std;

int n,m,k,l,d;
struct node{
	int people;
	int id;
}r[100000],c[100000];

int lp[100000],rp[1000000];

inline int cmp(node a,node b){
	return a.people>b.people;
}

int main(){
	scanf("%d%d%d%d%d",&n,&m,&k,&l,&d);
	for (int i=1;i<=d;i++){
		int a,b,x,y;
		scanf("%d%d%d%d",&a,&b,&x,&y);
		a==x?c[min(b,y)].people++:r[min(a,x)].people++;
	}
	for (int i=1;i<=n;i++) r[i].id=i;
	for (int i=1;i<=m;i++) c[i].id=i;
	sort(c+1,c+1+m,cmp),sort(r+1,r+1+n,cmp);
	for (int i=1;i<=k;i++) lp[r[i].id]=1;
	for (int i=1;i<=1005;i++) if (lp[i]) printf("%d ",i);puts("");
	for (int i=1;i<=l;i++) rp[c[i].id]=1;
	for (int i=1;i<=1005;i++) if (rp[i]) printf("%d ",i);puts("");
}
