//
// Created by December on 2021/3/19.
//

#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc > 1)
        cout << "Advanced" << argv[1] << endl;
    else
        cout << "Programming" << argv[0] << endl;
    cout << atoi(argv[1]) << endl;
    cout << atol(argv[2]) << endl;
    cout << atoll(argv[3]) << endl;
    return 0;
}