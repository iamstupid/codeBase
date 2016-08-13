//simple random cactus generator
#include<cmath>
#include<cstdio>
#include<random>
#include<cstring>
#include<algorithm>
using namespace std;

mt19937_64 rng1;
random_device rngdev;
int rngsed[16];

int p;
char ofile[5001000];
char*ofilex=ofile;

int main(){
	freopen("2125.in","w",stdout);
	int len_max=100, n=400, q=400;
	scanf("%d%d%d",&len_max,&n,&q);
	for(int i=0;i<16;++i)
		rngsed[i]=rngdev();
	rng1.seed(*(new seed_seq(rngsed,rngsed+16)));

	uniform_int_distribution<int> Len(1,len_max);
	uniform_real_distribution<double> Nar(0,1.);

	p=1;
	int m=0;
	while(p<n){
		int getLast=p==1?1:int(exp(pow(Nar(rng1),0.2)*log(p))+0.5);
		if(getLast>p)
			getLast=p;
		int eg=getLast;
		if(n-p>=2 && Nar(rng1)>=0.5){
			uniform_int_distribution<int> CycLen(2,std::max(std::min((n-p)/6,6),2));
			int G=CycLen(rng1);
			for(int last=eg,g=1;g<=G;g++,last=p){
				ofilex+=	sprintf(ofilex,"%d %d %d\n",last	,++p	,Len(rng1));		++m;
			}	ofilex+=	sprintf(ofilex,"%d %d %d\n",eg	,p		,Len(rng1));		++m;
		}else	ofilex+=	sprintf(ofilex,"%d %d %d\n",eg	,p+1	,Len(rng1)),++p,	++m;
	}

	printf("%d %d %d\n%s",n,m,q,ofile);
	uniform_int_distribution<int> Qry(1,n);
	for(int i=1;i<=q;++i)
		printf("%d %d\n",Qry(rng1),Qry(rng1));
	return 0;
}
