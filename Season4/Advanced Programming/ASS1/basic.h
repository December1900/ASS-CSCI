#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <random>

using namespace std;

struct Animal
{
    string name;
    string type;
    string registration;
    int problem;
};

struct Vet
{
    string name;
    int quality;
};

struct Problem
{
    string name;
    int det_complexity;
    int treat_complexity;
    int treatment;
};

struct Treatment
{
    string name;
};

vector<Animal> get_animals(string file);
vector<Vet> get_vets(string file);
vector<Problem> get_problems(string file);
vector<Treatment> get_treatments(string file);

vector<Animal> get_animals(string file)
{
    vector<Animal> animals;
    ifstream f(file);
    if (!f)
    {
        cout << "Error open!" << endl;
        exit(1);
    }
    string s;
    while (getline(f, s))
    {
        int j = 0;
        string list[4] = {"", "", "", ""};
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == ':')
                j++;
            else if (s[i] == '.')
                break;
            else
                list[j] += s[i];
        }
        Animal animal;
        animal.name = list[0];
        animal.type = list[1];
        animal.registration = list[2];
        animal.problem = stoi(list[3]);
        animals.push_back(animal);
    }
    f.close();
    return animals;
}

vector<Vet> get_vets(string file)
{
    vector<Vet> vets;
    ifstream f(file);
    if (!f)
    {
        cout << "Error open!" << endl;
        exit(1);
    }
    string s;
    while (getline(f, s))
    {
        int j = 0;
        string list[2] = {"", ""};
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == ':')
                j++;
            else if (s[i] == '.')
                break;
            else
                list[j] += s[i];
        }
        Vet vet;
        vet.name = list[0];
        vet.quality = stoi(list[1]);
        vets.push_back(vet);
    }
    f.close();
    return vets;
}

vector<Problem> get_problems(string file)
{
    vector<Problem> problems;
    ifstream f(file);
    if (!f)
    {
        cout << "Error open!" << endl;
        exit(1);
    }
    string s;
    while (getline(f, s))
    {
        int j = 0;
        string list[4] = {"", "", "", ""};
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == ':')
                j++;
            else if (s[i] == '.')
                break;
            else
                list[j] += s[i];
        }
        Problem problem;
        problem.name = list[0];
        problem.det_complexity = stoi(list[1]);
        problem.treat_complexity = stoi(list[2]);
        problem.treatment = stoi(list[3]);
        problems.push_back(problem);
    }
    f.close();
    return problems;
}

vector<Treatment> get_treatments(string file)
{
    vector<Treatment> treatments;
    ifstream f(file);
    if (!f)
    {
        cout << "Error open!" << endl;
        exit(1);
    }
    string s;
    while (getline(f, s))
    {
        Treatment treatment;
        treatment.name = s.substr(0, s.length() - 1);;
        treatments.push_back(treatment);
    }
    f.close();
    return treatments;
}