#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

class Morse
{

public:
    map<string, char> m2l_rule_file;

    void read_m2l(string file);

    map<string, char> get_m2l()
    {
        return m2l_rule_file;
    }

    Morse()
    {
        read_m2l("./Morse.txt");
    }
};