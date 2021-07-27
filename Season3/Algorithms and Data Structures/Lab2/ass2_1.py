def binary_search(find, raw_list):
    low = 0
    high = len(raw_list) - 1
    while low <= high:
        mid = (low + high) // 2
        if raw_list[mid] == find:
            return mid
        elif raw_list[mid] > find:
            high = mid - 1
        else:
            low = mid + 1
    return -1


raw_list = [1, 3, 8, 12, 23, 28, 37, 40, 48, 66]

raw_list.sort()

print("Origin list:", raw_list)
try:
    find = int(input("Please input key："))
except:
    print("Please input integer")
    exit()

result = binary_search(find, raw_list)
if result != -1:
    print("The element is %d and its number is %d" % (find, result))
else:
    print("Cannot find!")
