#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>

#include "../Util.h"

using namespace std;

class Solver
{
private:
    stringstream sol1, sol2;
public:
    void part01();
    void part02();

    void printResult();
};

int day19()
{
    cout << "Starting" << endl;

    ifstream file("input.txt");


    if (!file.is_open())
        return -1;
    string line;
    vector<string> split;
    
    while (getline(file, line))
    {
        // TODO input parsing
        split = Util::split(line, " ");
        

    }
    Solver s;

    s.part01();
    s.part02();

    s.printResult();
}

void Solver::part01()
{
    // TODO solving part 1

    

    sol1 << "not finished";
}

void Solver::part02()
{
    // TODO solving part 2

    sol2 << "not finished";
}

void Solver::printResult()
{
    cout << "Part 1: " << sol1.str() << endl << "Part 2: " << sol2.str() << endl;
}
