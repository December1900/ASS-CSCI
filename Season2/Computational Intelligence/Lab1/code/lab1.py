import numpy as np

#create neurons of neural networks
class Neuron():
    def __init__(self,weights,bias):
        self.weights = weights
        self.bias = bias

#activation function
def sigmoid(x):
    return 1 / (1 + np.exp(-x))


def feedforward(w,b,inputs):
    h1_1 = np.dot(w[0:1],inputs) + b
    h1_2 = np.dot(w[1:2],inputs) + b
    t_1 = np.array([sigmoid(h1_1),sigmoid(h1_2)])
    h2_1 = np.dot(w[2:3],t_1) + b
    h2_2 = np.dot(w[3:4],t_1) + b
    return sigmoid(h2_1), sigmoid(h2_2)


#parameters w and b
weights = np.array([[3,1],[2,4],[3,2],[5,1]])
bias = 1
n = Neuron(weights,bias)

set_x = input() 
set_y = input()

inputs = np.array([int(set_x),int(set_y)])


print('The first ouput is ' + str(feedforward(n.weights,n.bias,inputs)[0]))
print('The second output is ' + str(feedforward(n.weights,n.bias,inputs)[1]))