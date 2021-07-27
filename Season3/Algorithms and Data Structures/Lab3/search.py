def search(tableau, key):

    i = 0
    j = len(tableau[0]) - 1

    while i < len(tableau) and j >= 0:

        if tableau[i][j] < key:
            i = i + 1

        elif tableau[i][j] > key:
            j = j - 1

        else:
            return True

    return False


tableau = [[10, 12, 15, 17], [11, 18, 20, 25], [22, 27, 30, 35],
           [34, 40, 44, 88]]


keys = [8, 17, 26, 88]

for key in keys:
    if search(tableau, key):
        print("Key", key, "found in table!")
    else:
        print("Error: No element found!")
