#include <iostream>
#include <random>
using namespace std;

int main(int argc, char* argv[])
{
	int N,tmp;
	N=atoi(argv[1]);
    int array[10]={0}; 
	uniform_int_distribution<int> u(0,9);
	default_random_engine e; 
	for (int i=0;i<N; i++){
		tmp=u(e);
    	cout<<tmp<<" ";
    	array[tmp]++;
	}
	cout<<endl;
	for(int i=0;i<10;i++)
		cout<<i<<'\t'<<array[i]<<endl;   
    return 0;
}

