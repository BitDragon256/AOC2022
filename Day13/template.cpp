#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../Util.h"

using namespace std;

class Solver
{
public:
    void part01(vector<string>);
    void part02(vector<string>);
};

int main()
{
    cout << "Starting" << endl;

    ifstream file("input.txt");

    vector<string> input;

    if (file.is_open())
    {
        cerr << "File Error" << endl;
        return -1;
    }
    string line;
    while (getline(file, line))
    {
        input.push_back(line);
    }
    Solver s;
    s.part01(input);
    s.part02(input);
}

void Solver::part01(vector<string> input)
{
    
}

void Solver::part02(vector<string> input)
{
    
}
