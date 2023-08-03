import numpy as np
from matplotlib import pyplot as plt

def get_convolution_function(f1, f2, x_max=15):
  x_values = np.arange(x_max + 1)
  conv_arr = np.zeros_like(x_values, dtype=float)

  for i in x_values:
      for j in x_values:
          if i - j >= 0:
              conv_arr[i] += f1(j) * f2(i - j)

  return lambda n: conv_arr[n]

figure, axis = plt.subplots(2, 2)

figure.set_figheight(7)
figure.set_figwidth(9.5)
figure.subplots_adjust(hspace=0.35, wspace=0.35)
title = 'Signal Linear Convolution'
plt.suptitle(title)
plt.get_current_fig_manager().set_window_title(title)

def plot_for_func(f, color, label, plot, max_x = 8):
  print(label + ':')
  for x in range(max_x + 1):
    f_x = f(x)
    plot.vlines(x, 0, f_x, colors=color)
    print(f'({x:.2f}, {f_x:.2f})')
  plot.legend([label])
  plot.set_title(label)

x_n = lambda n: 0.8**n if 0 <= n <= 6 else 0
g_n = lambda n: 0.3**n if 0 <= n <= 4 else 0

c1_n = get_convolution_function(x_n, g_n, max_x=15)

c2_n = get_convolution_function(g_n, x_n, max_x=15)

plot_for_func(x_n, color='teal', label='x[n]', plot=axis[0, 0])
plot_for_func(g_n, color='orange', label='g[n]', plot=axis[0, 1])
plot_for_func(c1_n, color='purple', label='c1[n] = x[n] * g[n]', plot=axis[1, 0], max_x=15)
plot_for_func(c2_n, color='brown', label='c2[n] = g[n] * x[n]', plot=axis[1, 1], max_x=15)

plt.show()