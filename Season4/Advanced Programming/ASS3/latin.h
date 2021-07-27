#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

class Latin
{
public:
    map<char, string> l2m_rule_file;
    map<char, string> l2b_rule_file;

    void read_l2m(string file);
    void read_l2b(string file);

    map<char, string> get_l2m()
    {
        return l2m_rule_file;
    }

    map<char, string> get_l2b()
    {
        return l2b_rule_file;
    }

    Latin()
    {
        read_l2m("./Morse.txt");
        read_l2b("./Braille.txt");
    }
};