#include <iostream>
#include <string>
#define N 1000002
using namespace std;

string s;
int len;
int nxt[N];
int cnt[N];
int length = 0;
int get_next()
{
    int j = 0;
    int k = -1;
    nxt[0] = -1;
    while(j<len)
    {
        if(k==-1||s[k]==s[j])
        {
            ++k;
            ++j;
            nxt[j] = k;
        }
        else
        {
            k=nxt[k];
        }
    }
    for(int i = 0;i<len;i++)
    {
        cnt[nxt[i]] = 1;
    }
}


int main()
{
    cin >> s;
    len = s.size();
    get_next();
    int k = nxt[len];
    int flag = 0;
    while(k>0)
    {
        if(cnt[k])
        {
            flag = 1;
            length = k;
            break;
        }
        k = nxt[k];
    }
    if(flag)
    {
        for(int i = len-length;i<len;i++)
        {
            cout << s[i];
        }
        cout << endl;
    }
    else
    {
        cout << "Just a legend" << endl;
    }
    return 0;
}