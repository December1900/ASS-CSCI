from sklearn import datasets
from sklearn import svm
import numpy as np

iris = datasets.load_iris()
print(type(iris), dir(iris))

x = iris.data
y = iris.target

data = x.shape[0]
print(data)
ratio = 8/2
data_test = int(data / (1 + ratio))
data_train = data - data_test
index = np.arange(data)
np.random.shuffle(index)

x_test = x[index[:data_test],:] 
y_test = y[index[:data_test]]
x_train = x[index[data_test:],:] 
y_train = y[index[data_test:]]

svm_linear = svm.SVC(decision_function_shape="ovo", kernel="linear")
svm_poly = svm.SVC(decision_function_shape="ovo", kernel="poly")
svm_rbf = svm.SVC(decision_function_shape="ovo", kernel="rbf")

svm_linear.fit(x_train, y_train)
svm_poly.fit(x_train, y_train)
svm_rbf.fit(x_train, y_train)
pre_linear_y_test = svm_linear.predict(x_test)
pre_poly_y_test = svm_poly.predict(x_test)
pre_rbf_y_test = svm_rbf.predict(x_test)


acc_linear = sum(pre_linear_y_test == y_test) / data_test
print('The accuracy of linear kernel is: ', acc_linear)
acc_poly = sum(pre_poly_y_test == y_test) / data_test
print('The accuracy of poly kernel is: ', acc_poly)
acc_rbf = sum(pre_rbf_y_test == y_test) / data_test
print('The accuracy of rbf kernel is: ', acc_rbf)