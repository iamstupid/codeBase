part_memo=[-1 for i in xrange(0,10**4+1)]
part_memo[0]=1
def part(x):
	ans,sgn,k,a,b=0,1,1,2,1
	while b<=x:
		if a<=x:
			if sgn==-1:
				ans=ans-part_memo[x-a]
			else:
				ans=ans+part_memo[x-a]
		if sgn==-1:
			ans=ans-part_memo[x-b]
		else:
			ans=ans+part_memo[x-b]
		a=a+3*k+2
		b=b+3*k+1
		k=k+1
		sgn=-sgn
	part_memo[x]=ans
	return part_memo[x]

a=0
print 1,
for i in xrange(1,10001):
	a=part(i)
	print a,
