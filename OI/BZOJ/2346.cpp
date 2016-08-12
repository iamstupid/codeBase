#include<cstdio>
#include<cstring>
#include<algorithm>
#define fc(i,j,k) for(int i=j,_L=k;i<_L;++i)
const int N=510,M=N*N;
int n,m,Q[M],d[M],qh,qt;
struct E{int t,w;E*n;}*h[M],Al[M*8],*p=Al;
#define $(x,y) ((x)*(m+1)+(y))
void A(int u,int v,int t){*p=(E){v,t,h[u]};h[u]=p++;}
void _(int u,int v,int t=0){A(u,v,t),A(v,u,t);}
char py[N];
int S2[M];
int main(){
	scanf("%d%d\n",&n,&m);
	if((n+m)&1)return puts("NO SOLUTION"),0;
	fc(i,0,n){
		gets(py);
		fc(j,0,m)if(py[j]=='\\')
			_($(i,j),$(i+1,j+1)),
			_($(i+1,j),$(i,j+1),1);
		else
			_($(i,j),$(i+1,j+1),1),
			_($(i+1,j),$(i,j+1));
	}memset(d,0x3f,sizeof(int)*(n+2)*(m+2));
	d[$(0,0)]=0,qt=1,Q[0]=$(0,0);
	int qx=$(n,m);
	while(qh-qt){
		int st=0,ed=d[Q[qh]];
		while(qh-qt){
			int v=Q[qh++];if(v==qx)goto FUCK;
			for(E*i=h[v];i;i=i->n){
				if(ed+i->w < d[i->t]){
					d[i->t]=ed+i->w;
					if(i->w)S2[st++]=i->t;
					else Q[qt++]=i->t;
				}
			}
		}++ed;
		fc(i,0,st)if(d[S2[i]]==ed)Q[qt++]=S2[i];
	}FUCK:;
	printf("%d\n",d[$(n,m)]);
	return 0;
}
