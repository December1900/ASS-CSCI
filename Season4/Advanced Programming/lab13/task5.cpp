#include <iostream>
using namespace std;

class Mod11
{
private:
    int value;

public:
    Mod11(int n);
    void print() { cout << value << endl; }

    Mod11 operator+(const Mod11 &obj);
    Mod11 operator-(const Mod11 &obj);
    Mod11 operator*(const Mod11 &obj);
};

Mod11::Mod11(int n)
{
    value = n % 11;
}

Mod11 Mod11::operator+(const Mod11 &obj)
{
    return Mod11(value + obj.value);
}

Mod11 Mod11::operator-(const Mod11 &obj)
{
    return Mod11(value - obj.value);
}

Mod11 Mod11::operator*(const Mod11 &obj)
{
    return Mod11(value * obj.value);
}

int main()
{
    Mod11 m1(12);
    Mod11 m2(19);
    Mod11 m3(78);
    Mod11 m4(58);

    Mod11 m5 = m1 + m3;
    Mod11 m6 = m1 - m3;
    Mod11 m7 = m1 * m3;

    m1.print();
    m2.print();
    m3.print();
    m4.print();
    m5.print();
    m6.print();
    m7.print();

    return 0;
}