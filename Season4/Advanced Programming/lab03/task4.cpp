//
// Created by December on 2021/3/19.
//

#include <iostream>
#include <string>

using namespace std;

class table {
public:
    void get_surface(float &sur);

    void display();

    void get_chair(int &chair);

    void get_color(string &color);

    void get_type(string &type);

    void set_cost();

    void put_cost();

    table();

private:
    int chair;
    float sur;
    string color;
    string type;
    int price;
    float cost;
};

table::table() {
    table::get_color(table::color);
    table::set_cost();
}

void table::put_cost() {
    cout << "Total cost is:" << table::cost << endl;
}

void table::set_cost() {
    table::get_chair(table::chair);
    table::get_surface(table::sur);
    table::get_type(table::type);
    table::cost = float(table::price) * (table::sur + 0.5 * float(table::chair));
}

void table::get_type(string &type) {
    while (true) {
        cout << "Input type of wood(m:mahogony,o:oak,p:pine)" << endl;
        cin >> type;
        if (type.compare("m") == 0) {
            table::price = 200;
            break;
        } else if (type.compare("o") == 0) {
            table::price = 150;
            break;
        } else if (type.compare("p") == 0) {
            table::price = 95;
            break;
        } else
            continue;
    }
}

void table::get_chair(int &chair) {
    cout << "Input chair counts" << endl;
    cin >> chair;
}


void table::display() {
    cout << "Chairs count:" << table::chair << endl;
    cout << "Table area(m2):" << table::sur << endl;
    cout << "Table color:" << table::color << endl;
    cout << "Wood type:" << table::type << endl;
    cout << "Wood price:" << table::price << endl;
    cout << "Total cost:" << table::cost << endl;
}

void table::get_surface(float &sur) {
    cout << "Input table area(m2)" << endl;
    cin >> sur;
}

void table::get_color(string &color) {
    cout << "Input cushions colors" << endl;
    cin >> color;
}

int main() {
    table t;
    t.display();
    return 0;
}