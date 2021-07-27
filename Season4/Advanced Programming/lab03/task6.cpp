//
// Created by December on 2021/3/19.
//


#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>

using namespace std;

bool get_vowel(char c) {
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
        return true;
    else
        return false;
}

int main() {
    string str;
    vector<string> obj;
    char a;
    cout << "Type start with #" << endl;
    while (getline(cin, str)) {
        obj.push_back(str);
        if (!str.find('#'))
            break;
    }
    cout << obj[0] << endl;
    for (int i = 0; i < obj.size(); i++) {
        str = obj[i];
        for (auto c : str) {
            a = tolower(char(c));
            if (get_vowel(a))
                cout << "*";
            else
                cout << a;
        }
        cout << endl;
    }

    return 0;
}
