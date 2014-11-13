#!/anaconda/bin/python
import os,sys
import numpy as np
from math import sqrt
from math import pow
import matplotlib.pyplot as plt
'''
	given x, compute y by solving the equation:
		y^2 - (x^2)^(1/3)*y + (x^2 - 1) = 0
	
	deduced from:
		(x^2 + y^2 - 1)^3 = x^2*y^3
'''
def get_under_sqrt(x, a):
# first square, then 1/3 power, or the result may be complex number
# and the results is wrong
	b = -pow(x**2, 1/3.0)
	c = x**2 - 1
	return b**2 - 4*a*c, b

step = 0.05
yabove = []
ybelow = []
xlist = []
x = 0
# forward search
a = 1.0
u, b = get_under_sqrt(x, a)
while u > 0:
	xlist.append(x)
	yabove.append((-b + sqrt(u))/2/a)
	ybelow.append((-b - sqrt(u))/2/a)
	x0 = x
	x += step
	u, b = get_under_sqrt(x, a)
	while u < 0 and step > 1e-8:
		step *= 0.9
		x = x0 + step
		u, b = get_under_sqrt(x, a)
# delete too near points in yary
n = len(yabove) - 1
y = yabove[n]
while n >= 0 and np.abs(yabove[n] - y) < 0.05:
	y = yabove[n]
	n -= 1
half_xa = xlist[:(n+1)] + [xlist[-1]]
half_xb = xlist[:(n+1)]
half_ya = yabove[:(n+1)] + [yabove[-1]]
half_yb = ybelow[:(n+1)]
xary1 = np.array(half_xa + half_xb)
yary1 = np.array(half_ya + half_yb)
plt.plot(np.hstack((xary1, -xary1)), np.hstack((yary1, yary1)), 'ro')
plt.plot(half_xa, half_ya, 'g*')
plt.plot(-np.array(half_xb), half_yb, 'y.')
plt.savefig('myheart.png', format='png')
