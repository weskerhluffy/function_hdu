from sympy.ntheory import mobius

N=101
r=0
for i in range(1,N+1):
#	print("u[{}]={}".format(i,mobius(i)))
	r+=mobius(i)
	print("f[{}]={}".format(i,r))
#print(r)
