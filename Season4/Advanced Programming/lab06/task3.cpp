#include<iostream>
using namespace std;

class Basic
{
    public:
        int publicNum;
        void showPublicNum();
};

void Basic::showPublicNum(){
    cout << "Constructing" << endl;
}

int main(){
    Basic basic;
    basic.showPublicNum();

}
