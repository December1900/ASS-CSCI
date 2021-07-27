def res_tableau(tableau, i=0, j=0):

    bottom = tableau[i + 1][j] if (i + 1 < m) else float('inf')
    right = tableau[i][j + 1] if (j + 1 < n) else float('inf')

    if bottom < right:

        temp = tableau[i][j]
        tableau[i][j] = tableau[i + 1][j]
        tableau[i + 1][j] = temp

        res_tableau(tableau, i + 1, j)

    if bottom > right:

        temp = tableau[i][j]
        tableau[i][j] = tableau[i][j + 1]
        tableau[i][j + 1] = temp

        res_tableau(tableau, i, j + 1)


def extract_min(tableau):

    min = tableau[0][0]

    tableau[0][0] = float('inf')

    res_tableau(tableau)

    return min


tableau = [[10, 12, 15, 17], [11, 18, 20, 25], [22, 27, 30, 35],
           [34, 40, 44, 88]]

(m, n) = (len(tableau), len(tableau[0]))

for i in range(m * n):
    print(extract_min(tableau))
