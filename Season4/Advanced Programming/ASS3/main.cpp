//
//  main.cpp
//  Ass3
//
//  Created by Zebiao Guo on 2021/5/27.
//

#include "translate.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace ::std;

int main(int argc, char **argv)
{
    if (argc != 5)
    {
        cout << "Please input the correct parameter as below" << endl;
        cout << "./TS From To In.txt Out.txt" << endl;
        return 0;
    }

    char From = *argv[1];
    char To = *argv[2];
    string inputFile = string(argv[3]);
    string outputFile = string(argv[4]);
    if (From == 'L' && To == 'M')
    {
        Container<Latin> c;
        c.load(inputFile);
        cout << "Before Translate" << endl;
        c.report();
        auto ret = c.Latin2Morse();
        Container<Morse> l(ret);
        cout << "After Translate" << endl;
        l.report();
        c.flush(outputFile, ret);
    }
    else if (From == 'L' && To == 'B')
    {
        Container<Latin> c;
        c.load(inputFile);
        cout << "Before Translate" << endl;
        c.report();
        auto ret = c.Latin2Braille();
        Container<Braille> l(ret);
        cout << "After Translate" << endl;
        l.report();
        c.flush(outputFile, ret);
    }
    else if (From == 'B' && To == 'L')
    {
        Container<Braille> c;
        c.load(inputFile);
        cout << "Before Translate" << endl;
        c.report();
        auto ret = c.Braille2Latin();
        Container<Latin> l(ret);
        cout << "After Translate" << endl;
        l.report();
        c.flush(outputFile, ret);
    }
    else if (From == 'M' && To == 'L')
    {
        Container<Morse> c;
        c.load(inputFile);
        cout << "Before Translate" << endl;
        c.report();
        auto ret = c.Morse2Latin();
        Container<Latin> l(ret);
        cout << "After Translate" << endl;
        l.report();
        c.flush(outputFile, ret);
    }
    else if (From == 'B' && To == 'M')
    {
        Container<Braille> c;
        c.load(inputFile);
        cout << "Before Translate" << endl;
        c.report();
        auto tmp = c.Braille2Latin();
        Container<Latin> l(tmp);
        cout << "Intermediate Container" << endl;
        l.report();
        auto ret = l.Latin2Morse();
        Container<Morse> m(ret);
        cout << "After Translate" << endl;
        m.report();
        m.flush(outputFile, ret);
    }
    else if (From == 'M' && To == 'B')
    {
        Container<Morse> c;
        c.load(inputFile);
        cout << "Before Translate" << endl;
        c.report();
        auto tmp = c.Morse2Latin();
        Container<Latin> l(tmp);
        cout << "Intermediate Container" << endl;
        l.report();
        auto ret = l.Latin2Braille();
        Container<Braille> m(ret);
        cout << "After Translate" << endl;
        m.report();
        m.flush(outputFile, ret);
    }
    else
    {
        cout << "Parameter error" << endl;
    }

    return 0;
}
