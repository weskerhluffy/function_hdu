from sympy.ntheory import mobius

#N=1081080
N=2000000
r=0
for i in range(1,N+1):
#	print("u[{}]={}".format(i,mobius(i)))
	r+=mobius(i)
	print("f[{}]={}".format(i,r))
print(r)
