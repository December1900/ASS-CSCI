import torch
import torch.nn as nn
import torchvision.datasets as dsets
import torchvision.transforms as transforms
from torch.autograd import Variable

device = 0 if torch.cuda.is_available() else 'cpu'

input_size = 784
num_classes = 10
num_epochs = 50 
batch_size = 64
learning_rate = 0.01

train_dataset = dsets.MNIST(root='mnist',
                            train=True,
                            transform=transforms.ToTensor(),
                            download=True)
test_dataset = dsets.MNIST(root='mnist',
                           train=False,
                           transform=transforms.ToTensor(),
                           download=True)

# Data loader
train_loader = torch.utils.data.DataLoader(dataset=train_dataset,
                                           batch_size=batch_size,
                                           shuffle=True)
test_loader = torch.utils.data.DataLoader(dataset=test_dataset,
                                          batch_size=batch_size,
                                          shuffle=True)

# LRC model
model = nn.Linear(input_size, num_classes).cuda()
# Loss and optimizer
criterion = nn.CrossEntropyLoss()
optimizer = torch.optim.SGD(model.parameters(), lr=learning_rate)

# Train
total_step = len(train_loader)
for epoch in range(num_epochs):
    for i, (images, labels) in enumerate(train_loader):
        # Reshape images
        images = Variable(images.view(-1, 28 * 28).cuda())
        labels = Variable(labels.cuda())
        outputs = model(images.cuda())
        loss = criterion(outputs, labels)
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()
        if (i + 1) % 100 == 0:
            print('Epoch [{}/{}], Step [{}/{}], Loss: {:.4f}'.format(
                epoch + 1, num_epochs, i + 1, total_step, loss.item()))

# Test
with torch.no_grad():
    correct = 0
    total = 0
for images, labels in test_loader:
    images = Variable(images.view(-1, 28 * 28).cuda())
    labels = Variable(labels.cuda())
    outputs = model(images.cuda())
    _, predicted = torch.max(outputs.data, 1)
    total += labels.size(0)
    correct += (predicted == labels).sum()

print('Accuracy is: {} %'.format(100 * correct / total))