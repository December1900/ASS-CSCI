#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <chrono>
using namespace std;

class Thing
{
private:
    string th_name;
    int th_age;

public:
    Thing(string name, int age);
    void show() const;
};

Thing::Thing(string name, int age) : th_name(name), th_age(age)
{
}

void Thing::show() const
{
    cout << "Thing: " << th_name << " is " << th_age << " years old." << endl;
}

int main(int argc, char *argv[])
{
    unsigned int number = atoi(argv[1]);
    Thing myThing("The big blue dog", 5);

    vector<Thing> vThing;
    deque<Thing> dThing;
    list<Thing> lists;

    {
        vector<Thing> vThing1;

        auto start = chrono::system_clock::now();

        for (unsigned int i = 0; i < number; i++)
        {
            vThing1.insert(vThing1.begin(), myThing);
        }

        auto end = chrono::system_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;
        cout << "Vector executing push_front operation takes " << elapsed_seconds.count() << "s" << endl;
    }

    {

        auto start = chrono::system_clock::now();
        for (unsigned int i = 0; i < number; i++)
        {
            vThing.push_back(myThing);
        }

        auto end = chrono::system_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;
        cout << "Vector executing push_back operation takes " << elapsed_seconds.count() << "s" << endl;
    }

    {

        auto start = chrono::system_clock::now();

        for (unsigned int i = 0; i < number; i++)
        {
            dThing.push_front(myThing);
        }

        auto end = chrono::system_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;
        cout << "Deque executing push_front operation takes " << elapsed_seconds.count() << "s" << endl;
    }

    {

        auto start = chrono::system_clock::now();

        for (unsigned int i = 0; i < number; i++)
        {
            dThing.push_back(myThing);
        }

        auto end = chrono::system_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;
        cout << "Deque executing push_back operation takes " << elapsed_seconds.count() << "s" << endl;
    }
    {

        auto start = chrono::system_clock::now();

        for (unsigned int i = 0; i < number; i++)
        {
            lists.push_front(myThing);
        }

        auto end = chrono::system_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;
        cout << "List executing push_front operation takes " << elapsed_seconds.count() << "s" << endl;
    }

    {

        auto start = chrono::system_clock::now();

        for (unsigned int i = 0; i < number; i++)
        {
            lists.push_back(myThing);
        }

        auto end = chrono::system_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;
        cout << "List executing push_back operation takes " << elapsed_seconds.count() << "s" << endl;
    }
}
