#include<bits/stdc++.h>
using std::swap;
using std::fill;
using std::copy;
using std::reverse;
using std::reverse_copy;
typedef int value_t;
typedef long long calc_t;
const int MaxN = 1 << 24;
const value_t mod_base = 7, mod_exp = 26;
const value_t mod_v = (mod_base << mod_exp) + 1;
const value_t primitive_root = 3;
int epsilon_num;
value_t eps[MaxN], inv_eps[MaxN];
value_t dec(value_t x, value_t v) { x -= v; return x < 0 ? x + mod_v : x; }
value_t inc(value_t x, value_t v) { x += v; return x >= mod_v ? x - mod_v : x; }
value_t pow(value_t x, value_t p){
	value_t v = 1;
	for(; p; p >>= 1, x = (calc_t)x * x % mod_v)
		if(p & 1) v = (calc_t)x * v % mod_v;
	return v;
}
void init_eps(int num){
	epsilon_num = num;
	value_t base = pow(primitive_root, (mod_v - 1) / num);
	value_t inv_base = pow(base, mod_v - 2);
	eps[0] = inv_eps[0] = 1;
	for(int i = 1; i != num; ++i){
		eps[i] = (calc_t)eps[i - 1] * base % mod_v;
		inv_eps[i] = (calc_t)inv_eps[i - 1] * inv_base % mod_v;
	}
}
void transform(int n, value_t *x, value_t *w = eps){
	for(int i = 0, j = 0; i != n; ++i){
		if(i > j) swap(x[i], x[j]);
		for(int l = n >> 1; (j ^= l) < l; l >>= 1);
	}
	for(int i = 2; i <= n; i <<= 1){
		int m = i >> 1, t = epsilon_num / i;
		for(int j = 0; j < n; j += i){
			for(int p = 0, q = 0; p != m; ++p, q += t){
				value_t z = (calc_t)x[j + m + p] * w[q] % mod_v;
				x[j + m + p] = dec(x[j + p], z);
				x[j + p] = inc(x[j + p], z);
			}
		}
	}
}
void inverse_transform(int n, value_t *x){
	transform(n, x, inv_eps);
	value_t inv = pow(n, mod_v - 2);
	for(int i = 0; i != n; ++i)
		x[i] = (calc_t)x[i] * inv % mod_v;
}
struct poly_t{
	int deg;
	value_t x[MaxN];
	poly_t() : deg(0) { x[0] = 0; }
};
void polynomial_inverse(int n, const poly_t& A, poly_t& B){
	if(n == 1){
		B.deg = 1;
		B.x[0] = pow(A.x[0], mod_v - 2);
		return;
	}
	static value_t X[MaxN];
	polynomial_inverse((n + 1) >> 1, A, B);
	int p = 1;
	for(; p < n << 1; p <<= 1);
	copy(A.x, A.x + n, X);
	fill(X + n, X + p, 0);
	transform(p, X);
	fill(B.x + B.deg, B.x + p, 0);
	transform(p, B.x);
	for(int i = 0; i != p; ++i)
		B.x[i] = (calc_t)B.x[i] * dec(2, (calc_t)X[i] * B.x[i] % mod_v) % mod_v;
	inverse_transform(p, B.x);
	B.deg = n;
}
poly_t a,b;
#define bs 1024
int main(){
	init_eps(1<<24);
	int n=(1<<22)-1;
	int deg=n-1;
	b.x[0]=1;
	for(int i=1;i<=bs;++i){
		int sgn=1,k=1,A=2,B=1;
		long long ans=0;
		while(B<=i){
			if(~sgn){
				if(A<=i)ans+=b.x[i-A];
				ans+=b.x[i-B];
			}else{
				if(A<=i)ans-=b.x[i-A];
				ans-=b.x[i-B];
			}
			A=A+3*k+2;
			B=B+3*k+1;
			k=k+1;
			sgn=-sgn;
		}b.x[i]=((ans%mod_v)+mod_v)%mod_v;
	}
	long long pans[bs];
	for(int i=bs+1;i<n;i+=bs){
		memset(pans,0,sizeof(pans));
		int imax=i+bs-1;
		int sgn=1,k=1,A=2,B=1;
		while(B<=imax){
			if(~sgn){
				for(int j=imax;j-A>=0&&j>=i;--j)pans[j-i]+=b.x[j-A];
				for(int j=imax;j-B>=0&&j>=i;--j)pans[j-i]+=b.x[j-B];
			}else{
				for(int j=imax;j-A>=0&&j>=i;--j)pans[j-i]-=b.x[j-A];
				for(int j=imax;j-B>=0&&j>=i;--j)pans[j-i]-=b.x[j-B];
			}
			A=A+3*k+2;
			B=B+3*k+1;
			k=k+1;
			sgn=-sgn;
		}pans[0]=((*pans%mod_v)+mod_v)%mod_v;
		for(int i=1;i<bs;++i){
			int sgn=1,k=1,A=2,B=1;
			long long ans=pans[i];
			while(B<=i){
				if(~sgn){
					if(A<=i)ans+=pans[i-A];
					ans+=pans[i-B];
				}else{
					if(A<=i)ans-=pans[i-A];
					ans-=pans[i-B];
				}
				A=A+3*k+2;
				B=B+3*k+1;
				k=k+1;
				sgn=-sgn;
			}pans[i]=((ans%mod_v)+mod_v)%mod_v;
		}
		for(int j=0;j<bs;++j)
			b.x[i+j]=pans[j];
	}
//	polynomial_inverse(deg, a, b);
	for(int i=0;i<n;++i)
		printf("%d\n",b.x[i]);
	return 0;
}
