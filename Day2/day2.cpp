#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Solver
{
public:
    void part01(vector<string>);
    void part02(vector<string>);
};

void day2()
{
    cout << "Starting" << endl;

    ifstream file("input.txt");

    vector<string> input;

    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            input.push_back(line);
        }
        Solver s;
        s.part01(input);
        s.part02(input);
    }
    else
    {
        cout << "error with file" << endl;
    }
}

void Solver::part01(vector<string> input)
{
    int score = 0;
    int a, b, res;
    for (string s : input)
    {
        a = *(s.c_str()) - 'A';
        b = *(s.c_str() + 2) - 'X';

        res = a - b;
        if (res == 2 || res == -1)
            score += 6;
        else if (res == 0)
            score += 3;
        
        score += b + 1;
    }

    cout << score << endl;
}

void Solver::part02(vector<string> input)
{
    int score = 0;
    int a, b, res;
    for (string s : input)
    {
        a = *(s.c_str()) - 'A';
        b = *(s.c_str() + 2) - 'X';

        score += b * 3;
        if (b == 1)
            score += a + 1;
        else
            score += (a + b - 1 + 3) % 3 + 1;
    }

    cout << score << endl;
}
