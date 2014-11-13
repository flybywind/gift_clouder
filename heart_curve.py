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

step = 0.005
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

# delete too near points in curve
i = 0
indx = [i]
x0 = xlist[i]
y0 = yabove[i]
for i, x in enumerate(xlist[1:]):
	y = yabove[i+1]
	if sqrt((x0 - x)**2 + (y0 - y)**2) < 0.1:
		continue
	indx.append(i+1)
	x0 = x
	y0 = y

xary = np.array(xlist)
# above part
half_xa = xary[indx]
# below part
half_xb = xary[indx]
yary1 = np.array(yabove)
yary2 = np.array(ybelow)
half_ya = yary1[indx]
half_yb = yary2[indx]
# merge above and below parts
half_x = np.hstack((half_xa, half_xb))
half_y = np.hstack((half_ya, half_yb))
plt.plot(np.hstack((half_x, -half_x)), np.hstack((half_y, half_y)), 'ro')
plt.plot(half_xa, half_ya, 'g*')
plt.plot(-half_xb, half_yb, 'y.')
plt.savefig('myheart.png', format='png')
