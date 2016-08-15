#include<cstdio>
#include<cstring>
#include<cassert>
#include<algorithm>
const int N=200100;
struct E{int t;E*n;};
struct G{
	E*h[N],Al[N],*p;G():p(Al){};
	void _(int u,int v){*p=(E){v,h[u]};h[u]=p++;}
}A,B;
#define $(u,v) (A._(u,v),A._(v,u))
#define D(u,v) (B._((u),(v)),fa[v]=(u))
#define C(x,y,z) for(E*y=x.h[z];y;y=y->n)
int cntr,cntc,dfn[N],fa[N],F[N],le[N];
void dc(int n,int f=0,int dis=0){
	dfn[n]=++cntr,F[n]=f;
	C(A,i,n)if(i->t!=f){
	 if(dfn[i->t]){
	  if(dfn[i->t]<dfn[n]){
		int lex=1,t=n,id=(++cntc)<<1|1;
		for(;t-i->t;t=F[t])D(id,t<<1),le[t<<1]=lex++;
		D(t<<1,id),le[id]=lex;
	  }
	 }else dc(i->t,n);
	}if(!fa[n<<1])D(f<<1,n<<1);
}using std::max;
int QB[N<<3],*qs=QB;
int dp(int n=2){
	int ma=F[n]=0;C(B,i,n)ma=max(dp(i->t),ma);
	if(n&1){
		int v=le[n],vk=v/2,
			*qf=qs,*qe=qs-1,
			*ff=qs+=v*3,
			*lf=qs+=v;qs+=v;
		C(B,i,n)
			F[n]=max(F[n],std::min(v-le[i->t],*(lf++)=le[i->t])+(*(ff++)=F[i->t])-1);
		std::reverse(qf+v*3,ff),std::reverse(qf+v*4,lf);
		ff=qf+v*3, lf=qf+v*4;
		for(int i=0;i<vk;*(++qe)=i++)
			while(qf<=qe&&ff[i]+lf[i]>=ff[*qe]+lf[*qe])--qe;
		for(int i=0,j=vk;i<v-1;++i,j=(j+1==v?0:j+1)){if(*qf==i)++qf;
			if(j!=v-1){
				while(qf<=qe&&ff[j]+lf[j]>=ff[*qe]+lf[*qe])--qe;*(++qe)=j;
			}
			if(qf<=qe)ma=max(ma,ff[i]+ff[*qf]+lf[*qf]-lf[i]),lf[i]+=v;
		}return ma;
	}else{int fma=-1,sma=-1;
		C(B,i,n)
			if(F[i->t]>=fma)sma=fma,fma=F[i->t];else
			if(F[i->t]>=sma)sma=F[i->t];
		return max(ma,(F[n]=fma+1)+sma+1);
	}
}
int main(){
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1,k,l;i<=m;++i){scanf("%d%d",&k,&l);
		for(int j=2,u;j<=k;++j,l=u)scanf("%d",&u),$(l,u);
	}dc(1),printf("%d\n",dp());
	return 0;
}
