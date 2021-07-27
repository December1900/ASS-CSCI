#include <iostream>
using namespace std;

int main()
{
    int x;
    float y;
    double z;
    string o;
    char p;
    long int q;
    char j[5];
    bool k;
    cout<<typeid(x).before(typeid(y));
    cout<<typeid(x).before(typeid(z));
    cout<<typeid(x).before(typeid(o));
    cout<<typeid(y).before(typeid(p));
    cout<<typeid(y).before(typeid(q));
    cout<<typeid(y).before(typeid(j));
    cout<<typeid(j).before(typeid(k))<<endl;
    return 0 ;
}
