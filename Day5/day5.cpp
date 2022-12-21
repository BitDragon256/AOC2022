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

void day5()
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

        vector<stack<char>*> stacks;
        for (int i = 0; i < (input[0].size() + 1) / 4; i++)
        {
            stack<char>* temp = new stack<char>();
            stacks.push_back(temp);
        }
        
        for (int i = 0; i < input.size(); i++)
        {
            if (input[i].length() == 0)
            {
                for (int j = i - 2; j >= 0; j--)
                {
                    for (int k = 1; k < input[j].size(); k += 4)
                    {
                        cout << j << " " << k << " " << input[j].size() << endl;
                        if (input[j].at(k) != ' ')
                        {
                            cout << input[j].at(k) << endl;
                            // stacks[k]->push(input[j].at(k));
                            cout << stacks[k]->top() << endl;

                            cout << "test" << endl;
                        }
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

void Solver::part01(vector<stack<char>*> stacks, vector<uint32_t> moves)
{
    uint16_t crateCount;
    uint8_t from, to;

    // Utils::printStacks(stacks);

    for (uint32_t move : moves)
    {
        crateCount = move >> 16;
        from = (move >> 8) & 0x0000FF;
        to = move & 0x000000FF;

        for (int i = 0; i < crateCount; i++)
        {
            cout << i << " " << crateCount << endl;
            // Utils::printStacks(stacks);

            stacks[to]->push(stacks[from]->top());
            stacks[from]->pop();
        }
    }

    for (int i = 0; i < stacks.size(); i++)
    {
        cout << stacks[i]->top();
    }
    cout << endl;
}

void Solver::part02(vector<stack<char>*> stacks, vector<uint32_t> moves)
{
    
}
