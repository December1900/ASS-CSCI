#include <iostream>
using namespace std;

template<typename R, typename S>
class Two {
    private:
        R r;
        S s;
    public:
        Two(R first, S second);
        void display();
        int total();
};

template<typename R, typename S>
Two<R, S>::Two(R first, S second) : r(first), s(second) {
}

template<typename R, typename S>
void Two<R, S>::display() {
    cout << r << "\n"
         << s << endl;
}

template<typename R, typename S>
int Two<R, S>::total() {
    return r + s;
}

class Pencil;
class Erase;

class Pencil {
        friend ostream& operator<<(ostream &out, const Pencil &pencil);
    public:
        Pencil(int value);
        friend int operator+(const Pencil &pencil, const Erase &erase);
        friend int operator+(const Erase &erase, const Pencil &pencil);

    private:
        int m_Value;
};

Pencil::Pencil(int value) : m_Value(value) {
}

ostream& operator<<(ostream &out, const Pencil &pencil) {
    out << "Pencil values " << pencil.m_Value << " dollars.";
    return out;
}


class Erase {
        friend ostream& operator<<(ostream &out, const Erase &erase);
    public:
        Erase(int value);
        friend int operator+(const Pencil &pencil, const Erase &erase);
        friend int operator+(const Erase &erase, const Pencil &pencil);

    private:
        int m_Value;
};

Erase::Erase(int value) : m_Value(value) {
}

ostream& operator << (ostream &out, const Erase &erase) {
    out << "Erase values " << erase.m_Value << " dollars.";
    return out;
}

struct Fruit {
    int value;
};

int operator+(const Pencil &pencil, const Erase &erase) {
	return pencil.m_Value + erase.m_Value;
}

int operator+(const Erase &erase, const Pencil &pencil) {
	return pencil.m_Value + erase.m_Value;
}

int main() {
    Pencil pencil(2);
    Erase erase(1);

    Two<Pencil, Erase> two1(pencil, erase);
    two1.display();
    cout << "Total values: " << two1.total() << " dollars" << endl;

    // two2 can be instantiated, but it will crash if tring to use display() or total() 
    Two<Pencil, Fruit> two2(pencil, Fruit());

    return 0;
}
