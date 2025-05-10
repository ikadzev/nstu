import matplotlib.pyplot as pp
from math import sqrt

G = 6.67e-7
m = 10000
M = 10000
x = -20
y = 10
Vx = 0
Vy = 0
dt = 0.1
t = 0
T = 100

dot = [x, y]

_, ax = pp.subplots()
ax.grid()
ax.axis('equal')
ax.scatter(0, 0, color='black', s=20)

while t < T:
    r_2 = y**2 + x**2
    r = sqrt(r_2)
    F = G * M * m / r_2

    Vx -= (x / r) * F * dt
    Vy -= (y / r) * F * dt

    x += Vx * dt
    y += Vy * dt

    ax.plot([dot[0], x], [dot[1], y], 'b-')
    # ax.plot([dot[0], x], [dot[1], y], 'bo-', markersize=1)
    dot = [x, y]

    t += dt
    pp.pause(0.01)