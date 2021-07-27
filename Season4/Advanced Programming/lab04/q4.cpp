#include<iostream>
using namespace std;

int main(){

	int *array = new int[10]{3, 5, 7, 10, 3, 5, 4, 4, 9, 3};
	int i;
	for(i=0;i<10;i++){
		cout << array[i] * array[i] << endl;
	}
            
}