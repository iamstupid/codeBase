#include<cstdio>
#include<cstring>
const short wheel[210]={
	2,0,2,3,2,5,2,7,2,3,
	2,0,2,0,2,3,2,0,2,0,
	2,3,2,0,2,5,2,3,2,0,
	2,0,2,3,2,5,2,0,2,3,
	2,0,2,0,2,3,2,0,2,7,
	2,3,2,0,2,5,2,3,2,0,
	2,0,2,3,2,5,2,0,2,3,
	2,0,2,0,2,3,2,7,2,0,
	2,3,2,0,2,5,2,3,2,0,
	2,7,2,3,2,5,2,0,2,3,
	2,0,2,0,2,3,2,0,2,0,
	2,3,2,0,2,5,2,3,2,7,
	2,0,2,3,2,5,2,0,2,3,
	2,0,2,7,2,3,2,0,2,0,
	2,3,2,0,2,5,2,3,2,0,
	2,0,2,3,2,5,2,0,2,3,
	2,7,2,0,2,3,2,0,2,0,
	2,3,2,0,2,5,2,3,2,0,
	2,0,2,3,2,5,2,0,2,3,
	2,0,2,0,2,3,2,0,2,0,
	2,3,2,7,2,5,2,3,2,0
};
#define maxn 100000010
#define roll1(x,y) low[i##x]=y;
#define roll0(x) {i0+=x;         \
	if(!low[i0])pr[prl++]=i0; \
	for(int j=4;j<prl&&pr[j]*i0<=n;++j){ low[i0*pr[j]]=pr[j]; if(!(i0%pr[j]))break; }\
}
#define roll2(x) {i0+=x; if(!low[i0])pr[prl++]=i0;}

short low[maxn];
int pr[6000000],prl;
inline int qm(int n){
	return n-(((210+(~n))>>31)&210);
}
inline void memfill(short*arrde,const short*arrfr,int len,int len2=210){
	int i=0;
	for(;i+len2<=len;i+=len2) memcpy(arrde+i,arrfr,len2<<1);
	memcpy(arrde+i,arrfr,(len-i)<<1);
}
void sieve(int n=100000000){
	pr[0]=2,pr[1]=3,pr[2]=5,pr[3]=7,prl=4;
	memfill(low,wheel,n+1);
	for(int i=4,p=4;i<=209;++i,p=qm(p+1)){
		if(!wheel[p]){
			register int v;
			if(!(v=low[i])) v=pr[prl++]=i;
			for(int j=4;j<prl&&pr[j]*i<=n;++j){
				low[i*pr[j]]=pr[j];
				if(v==pr[j]) break;
			}
		}
	}
	int i0=210;
	int m=n/7;
	for(;i0+210<=m;){
		roll0(1);
		roll0(10);
		roll0(2);
		roll0(4);
		roll0(2);
		roll0(4);
		roll0(6);
		roll0(2);
		roll0(6);
		roll0(4);
		roll0(2);
		roll0(4);
		roll0(6);
		roll0(6);
		roll0(2);
		roll0(6);
		roll0(4);
		roll0(2);
		roll0(6);
		roll0(4);
		roll0(6);
		roll0(8);
		roll0(4);
		roll0(2);
		roll0(4);
		roll0(2);
		roll0(4);
		roll0(8);
		roll0(6);
		roll0(4);
		roll0(6);
		roll0(2);
		roll0(4);
		roll0(6);
		roll0(2);
		roll0(6);
		roll0(6);
		roll0(4);
		roll0(2);
		roll0(4);
		roll0(6);
		roll0(2);
		roll0(6);
		roll0(4);
		roll0(2);
		roll0(4);
		roll0(2);
		roll0(10);
		i0++;
	}
	int i=i0;
	for(int p=0;i<=m||(i%210!=0);++i,p=qm(p+1)){
		if(!wheel[p]){
			register int v;
			if(!(v=low[i])) v=pr[prl++]=i;
			for(int j=4;j<prl&&pr[j]*i<=n;++j){
				low[i*pr[j]]=pr[j];
				if(v==pr[j]) break;
			}
		}
	}
	i0=i;
	for(;i0+210<=n;){
		roll2(1);
		roll2(10);
		roll2(2);
		roll2(4);
		roll2(2);
		roll2(4);
		roll2(6);
		roll2(2);
		roll2(6);
		roll2(4);
		roll2(2);
		roll2(4);
		roll2(6);
		roll2(6);
		roll2(2);
		roll2(6);
		roll2(4);
		roll2(2);
		roll2(6);
		roll2(4);
		roll2(6);
		roll2(8);
		roll2(4);
		roll2(2);
		roll2(4);
		roll2(2);
		roll2(4);
		roll2(8);
		roll2(6);
		roll2(4);
		roll2(6);
		roll2(2);
		roll2(4);
		roll2(6);
		roll2(2);
		roll2(6);
		roll2(6);
		roll2(4);
		roll2(2);
		roll2(4);
		roll2(6);
		roll2(2);
		roll2(6);
		roll2(4);
		roll2(2);
		roll2(4);
		roll2(2);
		roll2(10);
		i0++;
	}
	i=i0;
	for(int p=0;i<=n;++i,p=qm(p+1)){
			if(!low[i]) pr[prl++]=i;
	}
	low[2]=low[3]=low[5]=low[7]=0;
}
int main(){
	sieve();
//	for(int i=0;i<prl;++i) printf("%d\n",pr[i]);
	printf("%d\n",prl);
	return 0;
}
