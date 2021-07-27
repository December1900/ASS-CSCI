#include<iostream>
#include<fstream>
#include<string>
#include <vector>


using namespace std;
int main()
{


     fstream f("word.txt");
     vector<string> words;
     string line;
     while (getline(f, line))
     {
        words.push_back(line);
     }
     cout << "Total words size:" << words.size() << endl;


     for (int i = 0; i < words.size(); i++)
     {
        cout << i << " : " << words[i] << endl;
     }
     return  0;
}
