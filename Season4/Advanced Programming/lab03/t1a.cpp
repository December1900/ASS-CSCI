//
// Created by December on 2021/3/19.
//

#include <iostream>

using namespace std;

int main() {
    int arr[3];
    for (int i = 0; i < 3; i++){
        cout << "Please input the random integer:";
        cin >> arr[i];
    }
    for (const auto &j:arr)
        cout << j << endl;

}
