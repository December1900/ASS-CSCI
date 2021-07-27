#include<iostream>
using namespace std;

void CD(int highest, int lowest);


// Prints integers from highest to lowest, inclusive.

int main()
{   

   int high, low, temp;

   cout << "Enter an integer " << endl ;
   cin >> high;

   cout << "Enter another integer " << endl;
   cin >> low;

   if (high < low)
   {
       temp = high;
       high = low;
       low = temp;
   }

   CD(high, low);
   return 0;
}

void CD(int highest, int lowest)
{
   int x;
   for (x = lowest; x < highest; x++){
        cout << x << " " << endl;
   }
}
