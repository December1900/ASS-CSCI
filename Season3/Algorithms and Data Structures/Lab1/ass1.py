# num_count = int(input("input numbers of Integers:\n"))
import random

num_list = []

for i in range(0, 100):
    num = random.randint(0, 1000)
    num_list.append(num)

max_value = num_list[0]
for x in num_list:
    if x > max_value:
        max_value = x

min_value = num_list[0]
for i in num_list:
    if i < min_value:
        min_value = i

mean = sum(num_list) / len(num_list)

var = sum((x - mean)**2 for x in num_list) / len(num_list)

print("max value:", max(num_list))
print("min value:", min(num_list))
print("=========================")
print("max value:", max_value)
print("min value:", min_value)
print("mean value:", mean)
print("variance value:", var)