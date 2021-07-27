#include <iostream>
using namespace std;

class thing {
public:
    int value1 = 5;
    void display(){cout << value2 << endl;}
    int Get(){return value2;}
private:
    int value2 = 77;
};

int main()
{
    thing A;
    cout << A.value1 << endl;
    cout << A.Get() << endl;
    cout << *(&A.value1 + 1) << endl;
    A.display();
    cin >> *(&(A.value1) + 1);
    A.display();
    return 0;
}
