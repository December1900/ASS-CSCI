#include <iostream>
#include <string>
using namespace std;

class Cat{
    public:
        string instruction;
        int age;
        int fee;
};

int main(){
    Cat cat;
    cat.instruction = "Tigger is a Fluffy unit.";
    cat.age = 3;
    cat.fee = 10;
    cout << "Cat: " << cat.instruction << endl << "The cat's age is " << cat.age << endl << "License fee: $" << cat.fee <<endl;
}

