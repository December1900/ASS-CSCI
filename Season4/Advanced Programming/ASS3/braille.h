#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

class Braille
{

public:
    map<string, char> b2l_rule_file;

    void read_b2l(string file);

    map<string, char> get_b2l()
    {
        return b2l_rule_file;
    }

    Braille()
    {
        read_b2l("./Braille.txt");
    }
};