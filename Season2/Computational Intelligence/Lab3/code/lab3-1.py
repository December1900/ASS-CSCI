import numpy as np
 
def tanh(x):
    return np.tanh(x)
 
def tanh_deriv(x):
    return 1.0 - np.tanh(x) * np.tanh(x)

class MLP:
    def __init__(self, layers):
        self.layers = layers
        self.activation = tanh
        self.activation_deriv = tanh_deriv
        self.num_layers = len(layers)
        self.bias = [np.random.randn(x) for x in layers[1:]]
        self.weights = [np.random.randn(y, x) for x, y in zip(layers[:-1], layers[1:])]
 
    def fit(self, X, y, learning_rate, epochs):
        for k in range(epochs):
            for i in range(len(X)):
                #store to use
                results = [X[i]]
                for b, w in zip(self.bias, self.weights):
                    z = np.dot(w, results[-1])+b
                    output = self.activation(z)
                    results.append(output)

                error = y[i] - results[-1]
                deltas = [error * self.activation_deriv(results[-1])]
 
                for l in range(self.num_layers-2, 0, -1):
                    deltas.append(self.activation_deriv(results[l]) * np.dot( deltas[-1],self.weights[l]))

                deltas.reverse()
           
                for j in range(self.num_layers-1):
                    layers = np.array(results[j])
                    delta_w = learning_rate * ((np.atleast_2d(deltas[j]).T).dot(np.atleast_2d(layers)))
                    self.weights[j] += delta_w
                    delta_t = learning_rate * deltas[j]
                    self.bias[j] += delta_t
 
    def predict(self, x):
        for b, w in zip(self.bias, self.weights):
            z = np.dot(w, x) + b
            x = self.activation(z)
        return x


mlp = MLP([2,4,3,1])
X = np.array([[0, 1], [1, 0], [0, 0], [1, 1]])
y = np.array([1, 1, 0, 0])
mlp.fit(X, y, 0.05, epochs=1000)
for i in [[0, 1], [1, 0], [0, 0], [1, 1]]:
  print(i, mlp.predict(i))