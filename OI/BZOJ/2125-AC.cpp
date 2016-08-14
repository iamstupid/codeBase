/// as a lesson...
#include<cstdio>
#include<cstring>
#include<cassert>
#include<algorithm>
#define itg(i,nx,tx) for(E*i=nx.h[tx];i;i=i->n)
#ifdef __GNUC__
	#define inl inline __attribute__((always_inline))
#else
	#define inl
#endif
const int N=200010,M=N*4;
struct Gr{
	struct E{int t,w;E*n;}*h[N],Al[M],*p;Gr():p(Al){}
	inl void _(int u,int v,int w){*p=(E){v,w,h[u]};h[u]=p++;}
}bg;
typedef Gr::E E;
int qb[M*2],*nqb=qb;
struct Cyc{
	int*dist,len,siz;
	inl void open(){dist=nqb;}
	inl int add(int l){return *(nqb++)=len+=l,siz++;}
	inl void close(int l){len+=l;}
	inl int dick(int x,int y){if(x>y)std::swap(x,y);return std::min(dist[y]-dist[x],len+dist[x]-dist[y]);}
};
namespace Cactree{
	Gr x;
	int cntb,id[N],fa[N],dfn[N],fdis[N],ms[N],dep[N],dik[N],cntr;
	int efa[N];
	Cyc cyc[N];
	void dfs(int n,int f=0,int dis=0){
		dfn[n]=++cntr,fa[n]=f,fdis[n]=dis;
		itg(i,bg,n)
		if(i->t!=f){
		 if(dfn[i->t]){
		  if(dfn[i->t]<dfn[n]){
			int cyc_no=++cntb;
			int cyc_id=cyc_no<<1|1;
			Cyc&now=cyc_no[cyc];
			now.open();
			id[n]=now.add(i->w);
			int px=n;
			while(fa[px]!=i->t)
				id[fa[px]]=now.add(fdis[px]),px=fa[px];
			now.close(fdis[px]);
			px=n;int pid=0;
			while(px!=i->t)
				x._(cyc_id,px<<1,std::min(now.len-now.dist[pid],now.dist[pid])),pid++,px=fa[px];
			x._(px<<1,cyc_id,0);
		  }
		 }else dfs(i->t,n,i->w);
		}
		if(id[n]==-1)
			x._(f<<1,n<<1,dis);
	}
	/// part decomposite
	typedef int* arr;
	const arr siz=fdis, top=dfn;
	int d1(int n=2,int f=0){
		siz[n]=1,fa[n]=f;
		itg(i,x,n){
			dep[i->t]=dep[n]+1;
			dik[i->t]=dik[n]+i->w;
			int sr=d1(i->t,n);
			if(sr>siz[ms[n]])
				ms[n]=i->t;
			siz[n]+=sr;
		}return siz[n];
	}
	void d2(int n=2,int t=2){
		top[n]=t;
		if(ms[n])d2(ms[n],t);
		itg(i,x,n)if(i->t!=ms[n])
			d2(i->t,i->t);
	}
	inl int LCA(int u,int v){
		int fu=top[u],fv=top[v];
		while(fu!=fv){
			if(dep[fu]<dep[fv])std::swap(u,v),std::swap(fu,fv);
			fu=top[u=fa[fu]];
		}return dep[u]<dep[v]?u:v;
	}
	inl int sLCA(int u,int t){
		int sv=top[t];
		while(top[u]!=sv)
			if(fa[top[u]]==t)return top[u];
			else u=fa[top[u]];
		return ms[t];
	}
	inl int dist(int u,int v){
		if(u==v)return 0;
		u<<=1,v<<=1;
		int L=LCA(u,v);
		if(L&1){
			int su=sLCA(u,L),sv=sLCA(v,L);
			return dik[u]-dik[su]+dik[v]-dik[sv]+cyc[L>>1].dick(id[su>>1],id[sv>>1]);
		}else return dik[u]+dik[v]-dik[L]*2;
	}
}
struct Ed{int u,v,w;}Eds[M] __attribute__((aligned(16)));
bool operator< (const Ed&a,const Ed&b){return a.u<b.u||(a.u==b.u&&(a.v<b.v||(a.v==b.v&&a.w<b.w)));}
bool operator==(const Ed&a,const Ed&b){return a.u==b.u&&a.v==b.v;}
int main(){
	using namespace Cactree;
	int n,m,q;scanf("%d%d%d",&n,&m,&q);
	for(int i=1,u,v,w;i<=m;++i){
		scanf("%d%d%d",&u,&v,&w);
		if(u==v){
			--i,--m;
			continue;
		}
		if(u>v)std::swap(u,v);
		Eds[i]=(Ed){u,v,w};
	}std::sort(Eds+1,Eds+m+1);
	m=std::unique(Eds+1,Eds+m+1)-(Eds+1);
	for(int i=1;i<=m;++i){
		bg._(Eds[i].u,Eds[i].v,Eds[i].w),bg._(Eds[i].v,Eds[i].u,Eds[i].w);
	} memset(id,-1,sizeof(id));
	dfs(1),siz[0]=0,d1(),d2();
	for(int i=1,u,v;i<=q;++i)
		scanf("%d%d",&u,&v),printf("%d\n",dist(u,v));
	return 0;
}
