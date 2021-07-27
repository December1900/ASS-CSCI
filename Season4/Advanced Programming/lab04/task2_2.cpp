#include<iostream>
#include<fstream>
#include<string>
#include <vector>


using namespace std;
int main()
{
	int cnt2,cnt3,cnt4,cnt5,cnt6,cnt7,cnt8,cnt9,cnt1,cnt0 = 0;
	ofstream outFile;
	fstream f("digits.txt");
	vector<string> word;
	string line; 
	while (getline(f, line))
	{
		word.push_back(line);
	}
	cout << "Total words size:" << word.size() << endl;

	
	for (int i = 0; i < word.size(); i++)
	{
		for(int j=0;j<22;j++)
		{
			if (word[i][j] == '0'){
				cnt0 ++;
			}
			if (word[i][j] == '1'){
				cnt1 ++;
			}
			if (word[i][j] == '2'){
				cnt2 ++;
			}
			if (word[i][j] == '3'){
				cnt3 ++;
			}
			if (word[i][j] == '4'){
				cnt4 ++;
			}
			if (word[i][j] == '5'){
				cnt5 ++;
			}
			if (word[i][j] == '6'){
				cnt6 ++;
			}
			if (word[i][j] == '7'){
				cnt7 ++;
			}
			if (word[i][j] == '8'){
				cnt8 ++;
			}
			if (word[i][j] == '9'){
				cnt9 ++;
			}

		}
	}

	
    outFile.open("Distribution.txt",ios::app);
    outFile << "num 0 has: " << cnt0 << endl;
    outFile << "num 1 has: " << cnt1 << endl;
    outFile << "num 2 has: " << cnt2 << endl;
    outFile << "num 3 has: " << cnt3 << endl;
    outFile << "num 4 has: " << cnt4 << endl;
    outFile << "num 5 has: " << cnt5 << endl;
    outFile << "num 6 has: " << cnt6 << endl;
    outFile << "num 7 has: " << cnt7 << endl;
    outFile << "num 8 has: " << cnt8 << endl;
    outFile << "num 9 has: " << cnt9 << endl;
    outFile.close();
    
	return  0;


}