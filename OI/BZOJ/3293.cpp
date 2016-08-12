#include<cstdio>
#include<algorithm>
const int N=100100;
int c[N],d[N];
int main(){
	int n,q=0,t,i=0;scanf("%d",&n);for(;i<n;++i)scanf("%d",c+i),q+=c[i];
	for(q/=n,i=1;i<n;++i)d[i]=d[i-1]+c[i]-q;std::sort(d,d+n);
	long long v=0;for(t=d[n>>1],i=0;i<n;++i)v+=std::abs(t-d[i]);
	return printf("%lld\n",v),0;
}
