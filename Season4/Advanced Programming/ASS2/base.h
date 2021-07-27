#include <iostream>
#include <random>
#include <cstdlib>

using namespace std;

static default_random_engine r;
static uniform_int_distribution<unsigned> low(65, 90);
static uniform_int_distribution<unsigned> high(97, 122);

int get_random(int start, int end)
{
    return rand() % (end - start + 1) + start;
}

std::string create_name(int len)
{
    string name;
    char charat;

    for (int i = 0; i < len; ++i)
    {
        if (i == 0)
            charat = low(r);
        else
            charat = high(r);
        name = name + charat;
    }
    return name;
}