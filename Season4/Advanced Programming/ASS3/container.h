#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// template Container
template <typename T>
class Container
{
private:
    string data;
    string out;

public:
    Container<T>(const string &d = "") : data(d) {}

    vector<string> split_str(string str)
    {
        if (data[data.size() - 1] == '\r' || data[data.size() - 1] == '\n')
            data.pop_back();
        vector<string> st;
        int begin = 0, end = 0, len = data.size();
        while (end < len)
        {
            while (end < len && data[end] != ' ')
                end++;
            st.push_back(data.substr(begin, end - begin));
            end++;
            begin = end;
        }
        return st;
    }

    vector<string> split_braille(const string &data)
    {
        vector<string> str;
        for (int i = 0; i < data.size(); i += 6)
        {
            str.push_back(data.substr(i, 6));
        }
        return str;
    }

    void show_data()
    {
        cout << "#############################################" << endl;
        cout << "The raw data: " << data << endl;
        cout << "The container length: " << data.size() << endl;
        map<char, int> f;
        for (int i = 0; i < data.size(); i++)
        {
            f[data[i]]++;
        }
        auto iter = f.begin();
        while (iter != f.end())
        {
            cout << iter->first << " -> " << iter->second << " ; ";
            iter++;
        }
        cout << endl;
        cout << "#############################################" << endl;
    }

    bool save(const string outfile, string str)
    {
        ofstream of;
        of.open(outfile);
        if (!of.is_open())
        {
            cerr << "Unabel opening " << outfile << endl;
            return false;
        }
        of << str;
        return true;
    }

    void load_data(string file);
    string transl2morse();
    string transl2braille();
    string transm2latin();
    string transb2latin();
};
