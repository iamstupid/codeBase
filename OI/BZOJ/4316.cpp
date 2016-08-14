#include<map>
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef std::pair<int,int> pii;
using std::max;
const int N=100010, M=N*2;
struct E{int t;E*n;};
struct G{
	E*h[N],Al[M],*p;G():p(Al){}
	void _(int u,int v){*p=(E){v,h[u]};h[u]=p++;}
}bg;
#define $(u,v) (bg._(u,v),bg._(v,u))
#define D(G,i,u) for(E*i=G.h[u];i;i=i->n)
namespace tr{
	#define U(u,v) (trx._((u),(v)),fa[v]=(u))
	#define _a first
	#define _b second
	G trx;
	int st[N],stl,dfn[N],cntr,cntc,fa[N];
	void dfs(int n=1,int f=0){
		st[++stl]=n,dfn[n]=++cntr;
		D(bg,i,n)if(i->t!=f){if(dfn[i->t]){
			if(dfn[i->t]<dfn[n]){
				int qd=(++cntc)<<1|1,e;
				while(stl&&dfn[e=st[stl--]]>dfn[i->t])
					e<<=1,U(qd,e);
				U(i->t<<1,qd),++stl;
			}
		}else dfs(i->t,n);}n<<=1,f<<=1;
		if(!fa[n])U(f,n),--stl;
	}
	pii dlj(int n=2){
		if(n&1){E*i=trx.h[n];
			pii Q=dlj(i->t),A=Q,B(Q._a,0),tA,tB;
			for(i=i->n;i;i=i->n){
				Q=dlj(i->t);
				tA=pii(Q._a+max(A._a,A._b),Q._b+A._a);
				if(i->n)tB=pii(Q._a+max(B._a,B._b),Q._b+B._a);
				else tB=pii(Q._a+max(B._a,B._b),0);
				A=tA,B=tB;
			}
			return pii(max(A._a,A._b),B._a);
		}else{pii dx(0,1),dy;
			D(trx,i,n){dy=dlj(i->t);
				if(i->t&1)dx=pii(dx._a+dy._a,dx._b+dy._b);
				else dx=pii(dx._a+max(dy._a,dy._b),dx._b+dy._a);
			}return dx;
		}
	}
}
int main(){
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;++i)
		scanf("%d%d",&u,&v),$(u,v);
	tr::dfs();
	pii e=tr::dlj();
	printf("%d\n",max(e._a,e._b));
	return 0;
}
