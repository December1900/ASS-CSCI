import numpy as np

inputs = np.array([[0,0,1],[0,1,1],[1,0,1],[1,1,1]])
outputs = np.array([0,0,1,1])
w = np.transpose(np.array([0,0,0]))
theta = 0.1
epoch = 2000

for i in range(epoch):
    for j in range(4):
        y_hat=1/(1+np.exp(-np.dot(w,inputs[j])))
        dw=theta*(outputs[j]-y_hat)*y_hat*(1-y_hat)*outputs[j]
        w=w+dw


for j in range(4):
    y_hat=1/(1+np.exp(-np.dot(w,inputs[j])))
    print(y_hat)
