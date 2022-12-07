#include <iostream>
#include <fstream>
#include <string>
#include <set>

using namespace std;

class Solver
{
public:
    void part01(string);
    void part02(string);
};

int main()
{
    cout << "Starting" << endl;

    ifstream file("input.txt");

    string input;

    if (file.is_open())
    {
        getline(file, input);
        Solver s;
        s.part01(input);
        s.part02(input);
    }
    else
    {
        cout << "error with file" << endl;
    }
}

bool isDistinct(string input)
{
    set<char> distinct;
    size_t size = 0;
    for (char c : input)
    {
        distinct.insert(c);
        if (size == distinct.size())
            return false;
        size = distinct.size();
    }
    return true;
}

void Solver::part01(string input)
{
    for (int i = 0; i < input.length() - 4; i++)
    {
        if (isDistinct(input.substr(i, 4)))
        {
            cout << i + 4 << endl;
            break;
        }
    }
}

void Solver::part02(string input)
{
    for (int i = 0; i < input.length() - 14; i++)
    {
        if (isDistinct(input.substr(i, 14)))
        {
            cout << i + 14 << endl;
            break;
        }
    }
}
