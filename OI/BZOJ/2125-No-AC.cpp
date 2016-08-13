/// the code contains some sensitive words.. (hand cover face)
#include<cstdio>
#include<cstring>
#include<algorithm>
#ifdef __GNUC__
	#define inl
#else
	#define inl
#endif
#define itg(i,G,nt) for(E*i=G.h[nt];i;i=i->n)
//#define __debug_open
#ifdef __debug_open
	#define If_1(A,B) A
	#define If_0(A,B) B
	#define cat(A,B) A##B
	#define eval(...) __VA_ARGS__
	#define Empty
	#define Block(x) x Empty
	#define Raw(...) __VA_ARGS__
	#define Expr(...) Block(Raw)(__VA_ARGS__)
	#define If(cond,A,B) cat(If_,cond)(A,B)
	#define version_0 0
	#define version_1 1
	#define version_at 1
	#define depug(id,...) eval(eval(If(cat(version_,id),Expr(__VA_ARGS__),Empty)))
	#define debug(id,...) depug(id,{fprintf(stderr,##__VA_ARGS__),fflush(stderr);})
	#define codei(id,...) depug(id,__VA_ARGS__;)
#else
	#define debug(...)
	#define codei(...)
#endif
const int N=20010,M=N*4;
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
	Cyc cyc[N];
	/// part build
	void dfs(int n,int f=0,int dis=0){
		dfn[n]=++cntr,fa[n]=f,fdis[n]=dis;
		itg(i,bg,n)
		if(i->t!=f){
		 if(dfn[i->t]){
		  if(dfn[i->t]<dfn[n]){
			//cycle found
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
			while(px!=i->t){
				debug(1,"%d -> Cycle %d with top %d: %d\n",px,cyc_no,i->t,std::min(now.len-now.dist[pid],now.dist[pid]));
				x._(cyc_id,px<<1,std::min(now.len-now.dist[pid],now.dist[pid])),pid++,px=fa[px];
			}
			x._(px<<1,cyc_id,0);
		  }
		 }else dfs(i->t,n,i->w);
		}
		if(!id[n])// if n not on cycle add w(fa->n)=dis edge
			x._(f<<1,n<<1,dis);
	}
	/// part decomposite
	typedef int* arr;
	const arr siz=fdis, top=dfn;
	int d1(int n=2,int f=0){
		siz[n]=0,fa[n]=f;
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
			debug(1,"%d -> %d on cycle %d is %d\n",su>>1,sv>>1,L>>1,cyc[L>>1].dick(id[su>>1],id[sv>>1]));
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
	}
	dfs(1),d1(),d2();
	for(int i=1,u,v;i<=q;++i)
		scanf("%d%d",&u,&v),printf("%d\n",dist(u,v));
	return 0;
}
