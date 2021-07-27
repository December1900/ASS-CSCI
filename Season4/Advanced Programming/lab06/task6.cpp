#include <iostream>
using namespace std;

class Staff {
public:
    string staffNum;
    string lastName;
    string firstName;
    int salesMade;
    char staffClass;
    double bonus;

    void setFields();
    void display();
    void computeBouns();
};

void Staff::setFields(){
    staffNum = "123456";
    lastName = "Sweeney";
    firstName = "Di";
    salesMade = 1;
    staffClass = 'A';
}

void Staff::computeBouns(){
    if (staffClass == 'A' && (salesMade >= 0 && salesMade <= 20)){
        bonus = 0.03;
    }
    if (staffClass == 'B' && (salesMade >= 0 && salesMade <= 20)) {
        bonus = 0.02;
    }
    if (staffClass == 'C' && (salesMade >= 0 && salesMade <= 20)) {
        bonus = 0.005;
    }

    if (staffClass == 'A' && (salesMade >= 21 && salesMade <= 50)){
        bonus = 0.05;
    }
    if (staffClass == 'B' && (salesMade >= 21 && salesMade <= 50)){
        bonus = 0.035;
    }
    if (staffClass == 'C' && (salesMade >= 21 && salesMade <= 50)){
        bonus = 0.015;
    }

    if (staffClass == 'A' && (salesMade >= 51)){
        bonus = 0.075;
    }
    if (staffClass == 'B' && (salesMade >= 51)){
        bonus = 0.055;
    }
    if (staffClass == 'C' && (salesMade >= 51)){
        bonus = 0.04;
    }
}


void Staff::display(){
    cout << "Staff Num: " << staffNum << endl;
    cout << "First Name: " << firstName << endl;
    cout << "Last Name: " << lastName << endl;
    cout << "Sales Made: " << salesMade << endl;
    cout << "Staff Class: " << staffClass << endl;
    cout << "Bouns: " << bonus << endl;
}

int main(){
    Staff staff;
    staff.setFields();
    staff.computeBouns();
    staff.display();
    return 0;
}

