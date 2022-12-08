#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>

#include "../Util.h"

using namespace std;

class Solver
{
public:
    void part01(vector<stack<char>*> stacks, vector<uint32_t> moves);
    void part02(vector<stack<char>*> stacks, vector<uint32_t> moves);
};

int main()
{
    cout << "Starting" << endl;

    ifstream file("input.txt");

    vector<string> input;
    vector<uint32_t> moves; // move X from Y to Z : 16*X 8*Y 8*Z

    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            input.push_back(line);
        }

        vector<stack<char>*> stacks((input[0].size() + 1) / 4, new stack<char>());
        
        for (int i = 0; i < input.size(); i++)
        {
            if (input[i].length() == 0)
            {
                for (int j = i - 3; j >= 0; j--)
                {
                    for (int k = 1; k < stacks.size(); k += 4)
                    {
                        if (input[j].at(k) != ' ')
                            stacks[k]->push(input[j].at(k));
                    }
                }
                input.erase(input.begin(), input.begin() + i + 1);
                break;
            }
        }
        uint16_t crateCount;
        uint8_t from, to;
        vector<string> split;
        for (string line : input)
        {
            split = Util::split(line, " ");
            crateCount = stoi(split[1]);
            from = stoi(split[3]);
            to = stoi(split[5]);

            moves.push_back(crateCount << 16 | from << 8 | to);
        }

        Solver s;
        s.part01(stacks, moves);
        s.part02(stacks, moves);

        while (stacks.size() > 0)
        {
            delete stacks[0];
            stacks.erase(stacks.begin());
        }
    }
    else
    {
        cout << "error with file" << endl;
    }
}

void printStacks(vector<stack<char>> stacks)
{
    uint8_t remaining = stacks.size();
    uint maxStack;
    while (remaining > 0)
    {

    }
}

void Solver::part01(vector<stack<char>*> stacks, vector<uint32_t> moves)
{
    
}

void Solver::part02(vector<stack<char>*> stacks, vector<uint32_t> moves)
{
    
}
