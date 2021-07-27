#include "translate.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

void get_trans(char from, char to, string input, string output)
{

    if (from == 'L')
    {
        Container<Latin> latin;
        latin.load_data(input);
        latin.show_data();

        cout << endl;
        cout << "Translating...." << endl;
        cout << endl;

        if (to == 'B')
        {
            auto l2b = latin.transl2braille();
            Container<Braille> b(l2b);
            b.show_data();
            latin.save(output, l2b);
        }
        else if (to == 'M')
        {
            auto l2m = latin.transl2morse();
            Container<Morse> m(l2m);
            m.show_data();
            latin.save(output, l2m);
        }
    }

    if (from == 'B')
    {
        Container<Braille> braille;
        braille.load_data(input);
        braille.show_data();

        cout << endl;
        cout << "Translating...." << endl;
        cout << endl;

        if (to == 'L')
        {
            auto b2l = braille.transb2latin();
            Container<Latin> l(b2l);
            l.show_data();
            braille.save(output, b2l);
        }
        else if (to == 'M')
        {
            auto b2l = braille.transb2latin();
            Container<Latin> l(b2l);
            cout << "Here is relay !!!" << endl;
            l.show_data();
            cout << endl;
            cout << "Translating...." << endl;
            cout << endl;
            auto l2m = l.transl2morse();
            Container<Morse> m(l2m);
            m.show_data();
            m.save(output, l2m);
        }
    }

    if (from == 'M')
    {
        Container<Morse> morse;
        morse.load_data(input);
        morse.show_data();

        cout << endl;
        cout << "Translating...." << endl;
        cout << endl;

        if (to == 'L')
        {
            auto m2l = morse.transm2latin();
            Container<Latin> l(m2l);
            l.show_data();
            morse.save(output, m2l);
        }
        else if (to == 'B')
        {
            auto m2l = morse.transm2latin();
            Container<Latin> l(m2l);
            cout << "Here is relay !!!" << endl;
            l.show_data();
            cout << endl;
            cout << "Translating...." << endl;
            cout << endl;
            auto l2b = l.transl2braille();
            Container<Braille> b(l2b);
            b.show_data();
            b.save(output, l2b);
        }
    }
}

int main(int argc, char **argv)
{
    if (argc != 5)
    {
        cout << "@NOTICE: The format is ./TS from To input_file output_file" << endl;
        return 0;
    }

    get_trans(*argv[1], *argv[2], string(argv[3]), string(argv[4]));

    return 0;
}