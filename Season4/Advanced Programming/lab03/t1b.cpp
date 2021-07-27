//
// Created by December on 2021/3/19.
//
#include <iostream>

using namespace std;

int main() {
    int *array = new int[3];
    for (int i = 0; i < 3; i++) {
        cout << "Please input the random integer:";
        cin >> *(array + i);
    }


    for (int i = 0; i < 3; i++) {
        cout << *(array + i) << endl;
    }
}
