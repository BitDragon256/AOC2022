#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Solver
{
public:
    void part01();
    void part02();
};

struct vec2
{
public:
    uint x, y;
    vec2(uint x, uint y): x(x), y(y) {}
    vec2(): x(0), y(0) {}

    vec2 operator+ (vec2 other)
    {
        return vec2(this->x + other.x, this->y + other.y);
    }

    vec2& operator+=(vec2& other)
    {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }
};

struct Grid
{
public:
    vector<vector<uint8_t>> height;
    vec2 size;

    Grid(): height(), size(vec2()) {}
    Grid(vector<vector<uint8_t>> data): height(data)
    {
        size = vec2(data.size(), data.size() > 0 ? data[0].size() : 0);
    }
    Grid(vector<string> input)
    {
        size.y = input.size();

        for (string line : input)
        {
            height.push_back(vector<uint8_t>());
            for (char c : line)
            {
                (*height.rbegin()).push_back(c - '0');
            }
        }
        size.x = height[0].size();
    }

    const uint8_t operator [] (vec2 pos)
    {
        return height[pos.x][pos.y];
    }
} grid;

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
        grid = Grid(input);

        /*
        vec2 pos;
        for (pos.x = 0; pos.x < grid.size.x; pos.x++)
        {
            for (pos.y = 0; pos.y < grid.size.y; pos.y++)
            {
                cout << (int) grid[pos];
            }
            cout << endl;
        }
        */

        Solver s;
        s.part01();
        s.part02();
    }
    else
    {
        cout << "error with file" << endl;
    }
}

vec2 directions[] = { vec2(-1, 0), vec2(1, 0), vec2(0, -1), vec2(0, 1) };

bool isVisible(vec2 pos)
{
    vec2 cur;
    uint8_t startHeight = grid[pos];
    vector<bool> visible;

    for (vec2 dir : directions)
    {
        cur = pos + dir;
        while (cur.x >= 0 && cur.x < grid.size.x && 
               cur.y >= 0 && cur.y < grid.size.y)
        {
            cout << cur.x << " " << cur.y << " " << (int) grid[cur] << " " << (int) startHeight;
            if (grid[cur] >= startHeight)
            {
                cout << "pushed" << endl;
                visible.push_back(false);
                break;
            }
            cout << endl;

            cur += dir;
        }
        visible.push_back(true);
    }

    for (int i = 0; i < visible.size(); i++)
    {
        if (!visible[i])
        {
            return false;
        }
    }
    return true;
}

void Solver::part01()
{
    uint visibleCount = 0;
    vec2 pos;
    for (pos.x = 0; pos.x < grid.size.x; pos.x++)
    {
        for (pos.y = 0; pos.y < grid.size.y; pos.y++)
        {
            if (isVisible(pos))
            {
                visibleCount++;
            }
        }
    }

    cout << visibleCount << endl;
}

void Solver::part02()
{
    
}
