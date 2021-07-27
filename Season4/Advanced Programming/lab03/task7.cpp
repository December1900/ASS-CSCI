//
// Created by December on 2021/3/19.
//

#include <iostream>
#include <vector>

using namespace std;

int main() {
    size_t size;
    cout << "Enter the size of the container: ";
    cin >> size;
    vector<int> intArray(size);
    for (int i = 0; i < size; ++i)
        intArray[i] = i;
//    for (int j = 0; j < size; j++)
//        cout << intArray[j] << endl;
    for (const auto &i:intArray)
        cout << i << endl;
}