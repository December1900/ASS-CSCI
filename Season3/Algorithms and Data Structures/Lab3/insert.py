def insert(tableau, i, j):
    if i == 0 and j == 0:
        return

    if i == 0:
        if tableau[i][j] < tableau[i][j - 1]:
            temp = tableau[i][j]
            tableau[i][j] = tableau[i][j - 1]
            tableau[i][j - 1] = temp

            insert(tableau, i, j - 1)
        return

    if j == 0:
        if tableau[i][j] < tableau[i - 1][j]:

            temp = tableau[i][j]
            tableau[i][j] = tableau[i - 1][j]
            tableau[i - 1][j] = temp
            insert(tableau, i - 1, j)
        return

    if tableau[i][j] < tableau[i - 1][j]:
        temp = tableau[i][j]
        tableau[i][j] = tableau[i - 1][j]
        tableau[i - 1][j] = temp

        insert(tableau, i - 1, j)

    if tableau[i][j] < tableau[i][j - 1]:
        temp = tableau[i][j]
        tableau[i][j] = tableau[i][j - 1]
        tableau[i][j - 1] = temp

        insert(tableau, i, j - 1)


def print_tableau(tableau):

    for i in range(M):
        for j in range(N):
            print(tableau[i][j], end=' ')
        print()


def insert_keys(tableau, keys):

    for key in keys:
        if tableau[M - 1][N - 1] != float('inf'):
            print("Full! Skip key:", key)
        else:
            tableau[M - 1][N - 1] = key

            insert(tableau, M - 1, N - 1)


M = N = 4

tableau = [[float('inf') for x in range(N)] for y in range(M)]

keys = [12, 8, 20, 22, 25, 32, 34, 11, 43, 27, 16, 40, 88, 15, 18, 45]

insert_keys(tableau, keys)
print_tableau(tableau)