#include<iostream> 
#include<string>
using namespace std;

struct Dog {
	string name; 
	string breed;
	int age; 
	static const string licFee;
};


const string Dog::licFee = "$17.55";

int main()
{
	Dog dog;
	cout<<"input dog name: "; 
	cin>>dog.name;
	cout<<"input dog breed: "; 
	cin>>dog.breed;
	cout<<"input dog age: "; 
	cin>>dog.age;
	cout<<endl;
	cout<<"Dog name: "<< dog.name <<endl;
	cout<<"Dog breed: "<< dog.breed <<endl;
	cout<<"Dog age: "<< dog.age <<endl;
	cout<<"Dog license fee: "<< dog.licFee <<endl; 
	return 0;
}