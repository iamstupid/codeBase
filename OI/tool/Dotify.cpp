/**
 * convert OI-format graphs(LINE[u v w]=>has edge (u,v) of weight w) into dot files.
 */
#include<cstdio>
int main(){
	int n,m;scanf("%d%d%d",&n,&m);
	puts	("graph a{");
	for(int i=1;i<=n;++i)
		printf("	A%d[label=\"%d\"];\n",i,i);
	for(int i=1,u,v,w;i<=m;++i)
		scanf("%d%d%d",&u,&v,&w),
		printf("	A%d--A%d[label=\"%d\"];\n",u,v,w);
	puts("}");
	return 0;
}
