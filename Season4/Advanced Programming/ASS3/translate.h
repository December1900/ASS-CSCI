#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <typeinfo>
#include "latin.h"
#include "morse.h"
#include "braille.h"
#include "container.h"

using namespace std;

// latin
void Latin::read_l2m(string file)
{
    ifstream ifile(file);
    if (!ifile.is_open())
    {
        cout << "Unable loaing rule" << endl;
        return;
    }
    string temp;
    while (getline(ifile, temp))
    {
        if (temp[temp.size() - 1] == '\r' || temp[temp.size() - 1] == '\n')
            temp.pop_back();
        string chara = temp.substr(2);
        l2m_rule_file[temp[0]] = chara;
    }
    return;
}

void Latin::read_l2b(string file)
{

    ifstream ifile(file);
    if (!ifile.is_open())
    {
        cout << "Unble loading" << file << "rule" << endl;
        return;
    }
    string temp;
    while (getline(ifile, temp))
    {
        auto chara = temp.substr(2, 6);
        l2b_rule_file[temp[0]] = chara;
    }
    return;
}

// morse
void Morse::read_m2l(string file)
{
    ifstream ifile(file);
    if (!ifile.is_open())
    {
        cout << "Unble loading" << file << "rule" << endl;
        return;
    }
    string temp;
    while (getline(ifile, temp))
    {
        if (temp[temp.size() - 1] == '\r' || temp[temp.size() - 1] == '\n')
            temp.pop_back();
        string chara = temp.substr(2);
        m2l_rule_file[chara] = temp[0];
    }
    return;
}

// braille
void Braille::read_b2l(string file)
{
    fstream ifile(file);
    if (!ifile.is_open())
    {
        cout << "Unble loading" << file << "rule" << endl;
        return;
    }
    string temp;
    while (getline(ifile, temp))
    {
        string chara = temp.substr(2, 6);
        b2l_rule_file[chara] = temp[0];
    }
    return;
}

// translate

template <typename T>
void Container<T>::load_data(string file)
{
    ifstream infile(file);
    if (!infile.is_open())
    {
        cout << "Unable opening file" << endl;
        return;
    }
    string temp;
    while (getline(infile, temp))
    {
        data += temp;
    }
    if (data[data.size() - 1] == '\r' || data[data.size() - 1] == '\n')
        data.pop_back();
}

template <typename T>
string Container<T>::transl2morse()
{
    T type;
    auto morse = type.get_l2m();
    string str;
    for (int j = 0; j < data.size(); j++)
    {
        char i = data[j];
        if (morse.find(i) == morse.end())
        {
            return str;
        }
        else
        {
            string chara = morse[i];
            str += chara;
            str += ' ';
        }
    }
    return str;
}

template <typename T>
string Container<T>::transl2braille()
{
    T type;
    auto braille = type.get_l2b();
    string str;
    for (auto i : data)
    {
        if (braille.find(i) == braille.end())
        {
            return str;
        }
        str += braille[i];
    }
    return str;
}

template <typename T>
string Container<T>::transm2latin()
{
    T type;
    auto r = type.get_m2l();
    string str;
    auto vec = split_str(data);
    for (auto i : vec)
    {

        if (r.find(i) == r.end())
        {
            return str;
        }
        str += r[i];
    }

    return str;
}

template <typename T>
string Container<T>::transb2latin()
{
    T type;
    auto r = type.get_b2l();
    string str;
    auto vec = split_braille(data);
    for (auto i : vec)
    {
        if (r.find(i) == r.end())
        {
            return str;
        }
        str += r[i];
    }
    return str;
}
