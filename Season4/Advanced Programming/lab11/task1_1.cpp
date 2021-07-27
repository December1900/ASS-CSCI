#include <iostream>
using namespace std;

class B {
    public:
        virtual void X() = 0;
};

class D : B {
    public:
        virtual void X() {cout << "D object" << endl;}
};

int main() {
    D objD;
}
