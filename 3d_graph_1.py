from mpl_toolkits import mplot3d
import numpy as np
import matplotlib.pyplot as plt


x = np.outer(np.linspace(-1, 1, 10), np.ones(10))
y = x.copy().T
z = np.e**(x + y )

fig = plt.figure()


ax = plt.axes(projection='3d')


ax.plot_surface(x, y, z, cmap='viridis',edgecolor='green')
ax.set_title('Surface plot')
plt.show()
