#include<cstdio>
#include<cstring>
#include<algorithm>
#define fc(i,j,k) for(int i=j,_LOOP=k;i<=_LOOP;++i)
#define rt(...) __VA_ARGS__
#define bl(def,...) {rt def;__VA_ARGS__;}
const int N=64, P=1000000009;
typedef long long ll;
int pw(int a,int e,int _=1){
	for(;e;e>>=1,a=ll(a)*a%P)if(e&1)_=ll(_)*a%P;
	return _;
}
int x[10010],y[10010];
int F[N][N];
int C[N][N];
int D(int n,int m,int a,int b,int I){
	if(~F[a][b])
		return F[a][b];
	int _=pw(I+1,n*m-(n-a)*(m-b));
	fc(i,0,a)
	 fc(j,0,b)
	  if(i||j)
		_=(_-C[a][i]*ll(C[b][j])%P*pw(I,n*m-(n-i)*(m-j))%P*D(n-i,m-j,a-i,b-j,I)%P+P)%P;
	return F[a][b]=_;
}
int main(){
	int n,m;scanf("%d%d",&n,&m);
	fc(i,1,n)bl((int t),scanf("%d",&t),++x[t]);
	fc(i,1,m)bl((int t),scanf("%d",&t),++y[t]);
	fc(i,0,std::max(n,m))bl((C[i][0]=1),fc(j,1,i)C[i][j]=(C[i-1][j]+C[i-1][j-1])%P);
	int ans=1;
	for(int c=0,d=0,i=10000;i;--i)
	 if(x[i]||y[i]){
		c+=x[i],d+=y[i];
		if(!c||!d)return puts("0"),0;
		memset(F,-1,sizeof(F)),F[0][0]=1;
		ans=ll(ans)*D(c,d,x[i],y[i],i)%P;
	 }printf("%d\n",ans);
	return 0;
}
