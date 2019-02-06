from ctypes import c_long,c_ulong
#a=c_ulong(-407794678950258602)
a=c_ulong(2666662666668000256)
g=lambda nl:((nl * (nl + 1) * (2 * nl + 1)) / 6) - (3 * (((nl * (nl + 1)) / 2)))+ 2 * nl
print(a.value)
