#include "svm.h"
#include <ctype.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <sstream>
#include <stdlib.h>
#include <random>
#include <chrono> // std::chrono::system_clock

using namespace std;

int main() {
    string s;
    vector<string> tmp;
    char filename[100];
    double ratio;
    ifstream in;
    cout << "Please input filename:";
    cin >> filename;
    cout << "Please input train/test ratio:";
    cin >> ratio;
    in.open(filename);


    while (getline(in, s)) {
        tmp.push_back(s);
    }

    in.close();


    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(tmp.begin(), tmp.end(), std::default_random_engine(seed));

    int testNum = int(tmp.size() / (1 + ratio));
    cout << "Test Number: " << testNum << endl;
    cout << "Total Number: " << tmp.size() << endl;
    int trainNum = tmp.size() - testNum;
    cout << "Train Number: " << trainNum << endl;
    ofstream outfile;
    outfile.open("../test.txt", ios::app);
    for (int i = 0; i < testNum; i++) {
        outfile << tmp[i] << endl;
    }

    ofstream output;
    output.open("../train.txt", ios::app);
    for (int i = testNum; i < tmp.size(); i++) {
        output << tmp[i] << endl;
    }
    output.close();


    return 0;


}

