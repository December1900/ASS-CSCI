import pandas as pd
import numpy as np
from lab5 import KMeansClassifier
import matplotlib.pyplot as plt
from sklearn import datasets

if __name__ == '__main__':
    iris = datasets.load_iris()
    X = iris.data
    data_X = X[:, [1, 3]]
    k = 5
    clf = KMeansClassifier(k)
    clf.fit(data_X)
    cents = clf.centroids
    labels = clf.labels
    sse = clf.sse
    colors = ['b', 'g', 'r', 'k', 'c', 'm', 'y', '#e24fff', '#524C90', '#845868']
    for i in range(k):
        index = np.nonzero(labels == i)[0]
        x0 = data_X[index, 0]
        x1 = data_X[index, 1]
        y_i = i
        for j in range(len(x0)):
            plt.text(x0[j], x1[j], str(y_i), color=colors[i], \
                     fontdict={'weight': 'bold', 'size': 6})
        plt.scatter(cents[i, 0], cents[i, 1], marker='x', color=colors[i], \
                    linewidths=7)

    plt.title("k=" + str(k) + "  SSE={:.2f}".format(sse))
    plt.axis([-7, 7, -7, 7])
    output = str(k) + ".png"
    plt.savefig(output)
    plt.show()
