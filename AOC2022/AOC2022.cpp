#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Day21.h"

using namespace std;

int main()
{
    cout << "Starting" << endl;

    string inputFile = "input21.txt";
    string exampleFile = "example21.txt";
    ifstream file(inputFile);

    if (!file.is_open())
    {
        cout << "file error" << endl;
        return -1;
    }
    string line;

    vector<string> input;
    while (getline(file, line))
    {
        input.push_back(line);
    }

    Day21 solver;
    solver.debug = false;

    int64_t res1 = solver.solvePart1(input);
    int64_t res2 = solver.solvePart2(input);

    cout << "Part 1: " << res1 << endl;
    cout << "Part 2: " << res2 << endl;
    
}
