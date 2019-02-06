from eulerlib import Divisors
from sympy.ntheory import mobius

#N = 101
#N = 1081080
N = 2000000

divobj = Divisors(N)


def funcion(n):
    return n ** 2 - 3 * n + 2

def sumatoria_convolucion(n):
    r=0
    for d in range(1,n+1):
        n_d=n//d
        for p in range(1,n_d+1):
            r+=funcion(d)*mobius(p)
    return r

def convolucion_dirichlet(n):
    divis = divobj.divisors(n)
    r = 0
#     print("divis {}".format(divis))
    for d in divis[:]:
        r += funcion(d) * mobius(n // d)
    if n==N:
        print("d {} f(d) {} cd {} morbiys {} es {}".format(d, funcion(d), n // d, mobius(n // d), r))
    return int(r)


r = 0
#for i in range(1, N + 1):
#    r += convolucion_dirichlet(i)
#    print("f[{}]={}".format(i, r % int(1E9 + 7)))
r = sumatoria_convolucion(N)
print("{}".format(r % int(1E9 + 7)))

