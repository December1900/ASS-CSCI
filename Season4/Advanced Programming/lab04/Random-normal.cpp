#include <iostream>
#include<ctime>
#include<random>
using namespace std;
static default_random_engine e;
int main(int argc, char* argv[]) {
	srand(time(0));
	int num = atoi(argv[1]);
	int mean = atoi(argv[2]);
	int stdev = atoi(argv[3]);
	static normal_distribution<double> u(mean, stdev);
	cout << num << endl;
	int counter[10]={0};
	for ( int i=0; i < num; i++ )
		{
			int dis = int(u(e));
			if(dis<0||dis>9){
				continue;
			}
			counter[dis]++;
		}
	for ( int i=0; i < 10; i++ )
		cout << i << " : " << counter[i] << endl;
	return 0;
}
