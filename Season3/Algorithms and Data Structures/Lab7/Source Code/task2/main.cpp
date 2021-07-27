#include <iostream>
#include "stdc++.h"

using namespace std;
#define N 4

struct Node {
    Node *parent;
    int pathCost;
    int cost;
    int machineID;
    int taskID;
    bool assigned[N];
};

struct comp {
    bool operator()(const Node *lhs,
                    const Node *rhs) const {
        return lhs->cost > rhs->cost;
    }
};

Node *newNode(int x, int y, bool assigned[],
              Node *parent) {
    Node *node = new Node;

    for (int j = 0; j < N; j++)
        node->assigned[j] = assigned[j];
    node->assigned[y] = true;

    node->parent = parent;
    node->machineID = x;
    node->taskID = y;

    return node;
}

int calculateCost(int costMatrix[N][N], int x,
                  int y, bool assigned[]) {
    int cost = 0;

    bool available[N] = {true};

    for (int i = x + 1; i < N; i++) {
        int min = INT_MAX, minIndex = -1;

        for (int j = 0; j < N; j++) {
            if (!assigned[j] && available[j] &&
                costMatrix[i][j] < min) {
                minIndex = j;

                min = costMatrix[i][j];
            }
        }

        cost += min;

        available[minIndex] = false;
    }

    return cost;
}

void printAssignments(Node *min) {
    if (min->parent == NULL)
        return;

    printAssignments(min->parent);
    cout << "Assign Machine " << char(min->machineID + '1')
         << " to Task " << min->taskID << endl;

}

// Finds minimum cost using Branch and Bound
int findMinCost(int costMatrix[N][N]) {
    priority_queue<Node *, std::vector<Node *>, comp> prq;

    bool assigned[N] = {false};
    Node *root = newNode(-1, -1, assigned, NULL);
    root->pathCost = root->cost = 0;
    root->machineID = -1;

    prq.push(root);

    while (!prq.empty()) {
        Node *min = prq.top();

        prq.pop();

        int i = min->machineID + 1;

        if (i == N) {
            printAssignments(min);
            return min->cost;
        }

        for (int j = 0; j < N; j++) {
            if (!min->assigned[j]) {
                Node *child = newNode(i, j, min->assigned, min);

                child->pathCost = min->pathCost + costMatrix[i][j];

                child->cost = child->pathCost +
                              calculateCost(costMatrix, i, j, child->assigned);

                prq.push(child);
            }
        }
    }
}

int main() {
    int costMatrix[N][N] =
            {
                    {13, 4,  7, 6},
                    {1,  11, 5, 4},
                    {6,  7,  2, 8},
                    {1,  3,  5, 9}
            };


    cout << findMinCost(costMatrix)
         << " is optimal min cost!";
    return 0;
}


