import numpy as np

inputs = np.array([[0,0,1],[0,1,1],[1,0,1],[1,1,1]])
y = np.array([0,0,1,1])
w = np.transpose(np.array([0,0,0]))
theta = 0.1
epoch = 2000

def sigmoid(x):
    return 1 / (1 + np.exp(-x))

for i in range(epoch):
    for j in range(4):
        y_hat = sigmoid(np.dot(w,inputs[j]))
        dw = theta * (y[j]-y_hat) * y_hat * (1-y_hat) * inputs[j]
        w = w + dw

for j in range(4):
    y_hat = sigmoid(np.dot(w,inputs[j]))
    print(y_hat)


w = np.transpose(np.array([0,0,0]))
y_avg = np.empty([2,3], dtype=float)
for i in range(epoch):
    for j in range(2):
      for k in range(2 * j,2 * j + 1):
          y_hat = sigmoid(np.dot(w,inputs[k]))
          y_avg[j] = (y[k]-y_hat) * y_hat * (1-y_hat) * inputs[k]
    dw = theta * ((y_avg[0] + y_avg[1])/2)
    w = w + dw

for k in range(4):
    y_hat = sigmoid(np.dot(w,inputs[k]))
    print(y_hat)