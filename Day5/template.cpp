#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

class Solver
{
public:
    void part01(vector<stack<char>> stacks, vector<string> moves);
    void part02(vector<stack<char>> stacks, vector<string> moves);
};

int main()
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

        vector<stack<char>> stacks((input[0].size() + 1) / 4, stack<char>());
        
        for (int i = 0; i < input.size(); i++)
        {
            if (input[i].length() == 0)
            {
                for (int j = i - 3; j >= 0; j--)
                {
                    for (int k = 1; k < stacks.size(); k += 4)
                    {
                        if (input[j].at(k) != ' ')
                            stacks[k].push(input[j].at(k));
                    }
                }
                input.erase(input.begin(), input.begin() + i + 1);
                break;
            }
        }

        Solver s;
        s.part01(stacks, input);
        s.part02(stacks, input);
    }
    else
    {
        cout << "error with file" << endl;
    }
}

void Solver::part01(vector<stack<char>> stacks, vector<string> moves)
{
    uint16_t crateCount, from, to;
    for (string move : moves)
    {
        cout << move << endl;

        cout << move.substr(5, move.find(' ', 5) - 5) << " ";
        crateCount = stoi(move.substr(5, move.find(' ', 5) - 5));

        cout << move.substr(move.find(' ', crateCount + 1) + 1, 1) << " ";
        from = stoi(move.substr(move.find(' ', crateCount + 1) + 1, 1));

        to = stoi(move.substr(move.length() - 1, 1));
        cout << move.substr(move.length() - 1, 1) << endl;

        cout << crateCount << " " << from << " " << to << endl;
    }
}

void Solver::part02(vector<stack<char>> stacks, vector<string> moves)
{
    
}
