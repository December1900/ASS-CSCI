import csv
import random
import math
random.seed(250)

with open('iris.csv') as csvfile:
    csvreader = csv.reader(csvfile)
    next(csvreader, None)
    dataset = list(csvreader)

for row in dataset:
    row[4] = ["Iris-setosa", "Iris-versicolor", "Iris-virginica"].index(row[4])
    print(row[4])
    row[:4] = [float(row[j]) for j in range(len(row))]

random.shuffle(dataset)
datatrain = dataset[:int(len(dataset) * 0.8)]
datatest = dataset[int(len(dataset) * 0.8):]
train_X = [data[:4] for data in datatrain]
train_y = [data[4] for data in datatrain]
test_X = [data[:4] for data in datatest]
test_y = [data[4] for data in datatest]


def matrix_mul_bias(A, B, bias):
    C = [[0 for i in range(len(B[0]))] for i in range(len(A))]    
    for i in range(len(A)):
        for j in range(len(B[0])):
            for k in range(len(B)):
                C[i][j] += A[i][k] * B[k][j]
            C[i][j] += bias[j]
    return C

def vec_mat_bias(A, B, bias): 
    C = [0 for i in range(len(B[0]))]
    for j in range(len(B[0])):
        for k in range(len(B)):
            C[j] += A[k] * B[k][j]
            C[j] += bias[j]
    return C


def mat_vec(A, B):
    C = [0 for i in range(len(A))]
    for i in range(len(A)):
        for j in range(len(B)):
            C[i] += A[i][j] * B[j]
    return C

def sigmoid(A, deriv=False):
    if deriv:
        for i in range(len(A)):
            A[i] = A[i] * (1 - A[i])
    else:
        for i in range(len(A)):
            A[i] = 1 / (1 + math.exp(-A[i]))
    return A


alfa = 0.005
epoch = 2000
# [input layer:feature of Iris, hidden layer, output layer:class of Iris]
neuron = [4, 4, 3] 
weight = [[0 for j in range(neuron[1])] for i in range(neuron[0])]
weight_2 = [[0 for j in range(neuron[2])] for i in range(neuron[1])]
bias = [0 for i in range(neuron[1])]
bias_2 = [0 for i in range(neuron[2])]

for i in range(neuron[0]):
    for j in range(neuron[1]):
        weight[i][j] = 2 * random.random() - 1

for i in range(neuron[1]):
    for j in range(neuron[2]):
        weight_2[i][j] = 2 * random.random() - 1


for e in range(epoch):
    cost_total = 0
    for idx, x in enumerate(train_X):
        
        h_1 = vec_mat_bias(x, weight, bias)
        X_1 = sigmoid(h_1)
        h_2 = vec_mat_bias(X_1, weight_2, bias_2)
        X_2 = sigmoid(h_2)
    
        target = [0, 0, 0]
        target[int(train_y[idx])] = 1

        eror = 0
        for i in range(neuron[2]):
            eror +=  (target[i] - X_2[i]) ** 2 
        cost_total += eror * 1 / neuron[2]

        delta_2 = []
        for j in range(neuron[2]):
            delta_2.append(-1 * 2. / neuron[2] * (target[j]-X_2[j]) * X_2[j] * (1-X_2[j]))

        for i in range(neuron[1]):
            for j in range(neuron[2]):
                weight_2[i][j] -= alfa * (delta_2[j] * X_1[i])
                bias_2[j] -= alfa * delta_2[j]
        
        delta_1 = mat_vec(weight_2, delta_2)
        for j in range(neuron[1]):
            delta_1[j] = delta_1[j] * (X_1[j] * (1-X_1[j]))
        
        for i in range(neuron[0]):
            for j in range(neuron[1]):
                weight[i][j] -=  alfa * (delta_1[j] * x[i])
                bias[j] -= alfa * delta_1[j]

    cost_total /= len(train_X)
    if(e % 100 == 0):
        print(cost_total)


#Test
result = matrix_mul_bias(test_X, weight, bias)
output = matrix_mul_bias(result, weight_2, bias)

predict = []
for r in output:
    predict.append(max(enumerate(r), key=lambda x:x[1])[0])
print(predict)

acc = 0.0
for i in range(len(predict)):
    if predict[i] == int(test_y[i]):
        print(test_y[i])
        acc += 1
print(acc / len(predict) * 100, "%")

print("weight_2: ", weight_2)
print("bias_2: ", bias_2)
print("weight: ", weight)
print("bias: ", bias)