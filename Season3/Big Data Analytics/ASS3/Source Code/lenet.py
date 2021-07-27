import torch
from torchvision import transforms
import torchvision.datasets as dsets
from torch.autograd import Variable

batch_size = 16
n_epochs = 5
train_dataset = dsets.MNIST(root='mnist',
                            train=True,
                            transform=transforms.ToTensor(),
                            download=True)
test_dataset = dsets.MNIST(root='mnist',
                           train=False,
                           transform=transforms.ToTensor(),
                           download=True)

train_loader = torch.utils.data.DataLoader(dataset=train_dataset,
                                           batch_size=batch_size,
                                           shuffle=True)
test_loader = torch.utils.data.DataLoader(dataset=test_dataset,
                                          batch_size=batch_size,
                                          shuffle=True)


class Model(torch.nn.Module):
    def __init__(self):
        super(Model, self).__init__()
        self.conv1 = torch.nn.Sequential(
            torch.nn.Conv2d(1, 64, kernel_size=3, stride=1, padding=1),
            torch.nn.ReLU(),
            torch.nn.Conv2d(64, 128, kernel_size=3, stride=1, padding=1),
            torch.nn.ReLU(), torch.nn.MaxPool2d(stride=2, kernel_size=2))
        self.dense = torch.nn.Sequential(torch.nn.Linear(14 * 14 * 128, 1024),
                                         torch.nn.ReLU(),
                                         torch.nn.Dropout(p=0.5),
                                         torch.nn.Linear(1024, 10))

    def forward(self, x):
        x = self.conv1(x)
        x = x.view(-1, 14 * 14 * 128)
        x = self.dense(x)
        return x


model = Model()
if torch.cuda.is_available():
    model.cuda()

cost = torch.nn.CrossEntropyLoss()
optimzer = torch.optim.Adam(model.parameters())

for epoch in range(n_epochs):
    running_loss = 0.0
    running_correct = 0
    print('Epoch{}/{}'.format(epoch + 1, n_epochs))
    print('-' * 10)

    for data in train_loader:
        X_train, y_train = data
        X_train, y_train = X_train.cuda(), y_train.cuda()
        X_train, y_train = Variable(X_train), Variable(y_train)
        outputs = model(X_train)
        _, pred = torch.max(outputs.data, 1)
        optimzer.zero_grad()
        loss = cost(outputs, y_train)
        loss.backward()
        optimzer.step()
        running_loss += loss.item()
        running_correct += torch.sum(pred == y_train.data)

    testing_correct = 0

    for data in test_loader:
        X_test, y_test = data
        X_test, y_test = X_test.cuda(), y_test.cuda()
        X_test, y_test = Variable(X_test), Variable(y_test)
        outputs = torch.mode(X_test)
        _, pred = torch.max(outputs, 1)
        testing_correct += torch.sum(pred == y_test.data)

    print(
        "Train Accuracy is :{:.4f}%, Test Accuracy is :{:.4f}%, Loss is : {:.4f}%"
        .format(100 * running_correct / len(train_dataset),
                100 * testing_correct / len(test_dataset),
                running_loss / len(train_dataset)))
