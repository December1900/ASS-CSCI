//
// Created by December on 2021/3/19.
//

#include <iostream>
#include <string>

using namespace std;

int main() {
    int a;
    string b;
    char c;
    float d;
    double e;
    cout << sizeof(a) << endl;
    cout << sizeof(b) << endl;
    cout << sizeof(c) << endl;
    cout << sizeof(d) << endl;
    cout << sizeof(e) << endl;

    char A[] = "Elephant";
    string B = "Elephant";
    int C[8] = {5};
    cout << sizeof(A) << endl;
    cout << sizeof(B) << endl;
    cout << sizeof(C) << endl;
    return 0;
}