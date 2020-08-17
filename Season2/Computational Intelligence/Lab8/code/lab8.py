import numpy as np
from sko.GA import GA
import pandas as pd
import matplotlib.pyplot as plt


def schaffer(p):
    x = p
    return x + 10 * np.sin(5 * x) + 7 * np.cos(4 * x)


ga = GA(func=schaffer, n_dim=2, max_iter=800, lb=[0], ub=[10], precision=1e-05)
best_x, best_y = ga.run()

Y_history = pd.DataFrame(ga.all_history_Y)
fig, ax = plt.subplots(2, 1)
ax[0].plot(Y_history.index, Y_history.values, '.', color='red')
Y_history.min(axis=1).cummin().plot(kind='line')
plt.show()
