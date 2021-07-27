#include "basic.h"
#include <cstdlib>

using namespace std;

int limit;

vector<Animal> animals;
vector<Vet> vets;
vector<Problem> problems;
vector<Treatment> treatments;

static default_random_engine ran;
static uniform_int_distribution<unsigned> u(1, 100);

void treat_animal(Problem problem, bool checked, ofstream &of)
{
    int chance = u(ran);
    int success_treat;
    if (checked)
        success_treat = 100 - problem.treat_complexity;
    else
        success_treat = 25;

    of << "Step 3. -> Treating... " << endl;
    if (chance <= success_treat)
    {
        of << "Treat success!" << endl;
        of << "==================================================" << endl;
    }
    else
    {
        of << "Treat failed!" << endl;
        of << "==================================================" << endl;
    }

    of << "The animal leaves !" << endl;
}

void dx_animal(Problem problem, Vet vet, ofstream &of)
{

    float proportion = float(vet.quality / problem.det_complexity);
    int success_chance;

    if (proportion >= 1 && vet.quality >= 70)
    {
        success_chance = 85;
    }
    else if (proportion < 1 && vet.quality <= 50)
    {
        success_chance = 40;
    }
    else
    {
        success_chance = 50;
    }

    of << "Step 2. -> Diagnosing... " << endl;
    int rate = u(ran);
    if (rate <= success_chance)
    {
        of << "Diagnose succeed!" << endl;
        of << "The diagnosis is the correct problem." << endl;
        of << "Adopt treatment: " << treatments[problem.treatment - 1].name << endl;
        of << "==================================================" << endl;
        treat_animal(problem, true, of);
    }
    else
    {
        int error_dx = u(ran) % treatments.size();
        of << "Diagnose failed!" << endl;
        of << "The guess problem: " << problems[error_dx].name << endl;
        of << "Adopt treatment: " << treatments[error_dx].name << endl;
        of << "==================================================" << endl;
        treat_animal(problem, false, of);
    }
}

void check_animal(Animal animal, ofstream &of)
{
    int num_vet = u(ran) % vets.size();
    of << "Step 1 -> Animal basic info" << endl;
    of << "Name: " << animal.name << endl;
    of << "Correct Problem: " << problems[animal.problem - 1].name << endl;
    of << "VET." << vets[num_vet].name << " comes to check..." << endl;
    of << "==================================================" << endl;
    dx_animal(problems[animal.problem - 1], vets[num_vet], of);
}

int main(int argc, char *argv[])
{

    limit = atoi(argv[1]);
    animals = get_animals(argv[2]);
    vets = get_vets(argv[3]);
    problems = get_problems(argv[4]);
    treatments = get_treatments(argv[5]);
    ofstream of(argv[6]);
    for (int i = 0; i < limit; ++i)
    {
        of << "===================NO." << i + 1 << " coming====================" << endl;
        check_animal(animals[i], of);
        of << endl;
    }
    of.close();
    return 0;
}