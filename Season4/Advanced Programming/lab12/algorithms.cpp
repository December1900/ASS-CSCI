#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include <random>
#include <iterator>

using namespace std;

static default_random_engine ran;
static uniform_int_distribution<unsigned> u(1, 50);



int main()
{
    list<int> list1, list2;

    list1.push_back(u(ran));
    list1.push_back(u(ran));
    list1.push_back(u(ran));
    list1.push_back(u(ran));
    list1.push_back(u(ran));
    list1.push_back(u(ran));
    list1.push_back(u(ran));
    list1.push_back(u(ran));

    list2.push_back(1);
    list2.push_back(2);
    list2.push_back(3);
    list2.push_back(4);
    list2.push_back(5);
    list2.push_back(6);
    list2.push_back(7);
    list2.push_back(8);

    cout << "\nsort(): ==========================" << endl;
    list1.sort();
    for (auto item = list1.begin(); item != list1.end(); ++item)
    {
        cout << *item << " ";
    }
    cout << endl;

    cout << "\nmerge(): ==========================" << endl;
    list2.merge(list1);
    for (auto item = list2.begin(); item != list2.end(); ++item)
    {
        cout << *item << " ";
    }
    cout << endl;

    cout << "\npartial_sum(): ====================" << endl;
    int val[] = {10, 20, 30, 40, 50};
    std::cout << "Elements: ";
    for (int i = 0; i < 5; i++)
    {
        std::cout << val[i] << " ";
    }
    std::cout << endl;
    int result[5];
    std::partial_sum(val, val + 5, result);
    std::cout << "Partial sum is" << endl;
    for (int i = 0; i < 5; i++)
    {
        std::cout << result[i] << " ";
    }
    cout << endl;

    cout << "\nshuffle(): ========================" << endl;
    std::vector<int> v = {10, 20, 40, 22, 66, 79, 72, 0, 12, 15};
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(v.begin(), v.end(), g);
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    cout << endl;

    cout << "\nnext_permutation(): ===============" << endl;
    std::string s = "0011";
    std::sort(s.begin(), s.end());
    do
    {
        std::cout << s << '\n';
    } while (std::next_permutation(s.begin(), s.end()));
}