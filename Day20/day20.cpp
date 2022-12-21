#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>

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

vector<int> input;

int day20(int argc, char** argv)
{
    cout << "Starting" << endl;

    string inputFile = "input.txt";
    if (argc > 1)
        inputFile = argv[1];
    ifstream file(inputFile);


    if (!file.is_open())
        return -1;
    string line;
    while (getline(file, line))
    {
        // TODO input parsing
        input.push_back(stoi(line));
    }
    Solver s;

    s.part01();
    s.part02();

    s.printResult();
}

void Solver::part01()
{
    // TODO solving part 1

    vector<int> indeces;

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
