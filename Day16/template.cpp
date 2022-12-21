#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
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

    ifstream file("example.txt");

    vector<string> input;

    if (!file.is_open())
        return -1;
    string line;
    while (getline(file, line))
    {
        input.push_back(line);
    }
    Solver s;
    s.part01(input);
    s.part02(input);
}

struct Vertex
{
    uint flowRate;
    uint id;
    vector<Vertex*> neighbors;

    Vertex(uint flowRate, string name): flowRate(flowRate)
    {
        id = 0;
        for (char c : name)
        {
            id >>= 8;
            id += c;
        }
    }

    void setStringNeighbors(vector<string>::iterator start, vector<string>::iterator end)
    {

    }

    void applyStringNeighbors(vector<Vertex*> allVertices)
    {

    }

    void setNeighbors(vector<Vertex*> neighbors)
    {
        this->neighbors = vector<Vertex*>(neighbors);
    }

    void newNeighbor(Vertex* neighbor)
    {
        this->neighbors.push_back(neighbor);
    }
};

struct Path
{
    vector<Vertex*> vertices;
    vector<bool> opened;
    uint releasedPressure;
    uint time;
    uint visitedVertices;

    Path(Vertex* start): releasedPressure(0), time(0), visitedVertices(0)
    {
        appendVertex(start);
    }

    Path(Path* copy, Vertex* append):
    releasedPressure(copy->releasedPressure), time(copy->time)
    {
        appendVertex(append);
    }

    void appendVertex(Vertex* vertex)
    {
        vertices.push_back(vertex);
        opened.push_back(false);

        for (Vertex* v : vertices)
            if (vertex->id == v->id)
                return;
        
        visitedVertices++;
    }

    void openValve()
    {
        opened[vertices.size() - 1] = true;
    }

    void tick()
    {
        time++;
        for (int i = 0; i < vertices.size(); i++)
            if (opened[i])
                releasedPressure += vertices[i]->flowRate;
    }

    Vertex* lastVisited()
    {
        return vertices[vertices.size() - 1];
    }
};

void Solver::part01(vector<string> input)
{
    vector<Vertex*> vertices;

    Vertex* v;
    vector<string> split;
    for (string line : input)
    {
        split = Util::splitMulti(line, {" ", "=", ";", ","});
        v = new Vertex(stoi(split[5]), split[1]);
        v->setNeighbors()
        vertices.push_back(v);
    }

    /*
    

    P := set of paths
    P[0] = ({ starting vertex }, 0, 0)   # (visited, pressure released, time elapsed)
    
    while true:
        for all p in P:
            if all vertices visited in p:
                return p
            V_next = p.lastVisited.neighbors
            if all vertices in V_next visited:
                while V_next not empty:
                    p_n := p
                    p_n.visited += pop(V_next)
                    P += p_n
            else:
                for all not visited v in V_next:
                    p_n := p
                    p_n.visited += v
                    P += p_n

            remove p from V_next


    */

    vector<Path*> paths;
    vector<Vertex*> neighbors;

    paths.push_back(new Path(vertices[0]));

    // temp vars
    size_t size;

    while (true)
    {
        size = paths.size();
        for (int i = 0; i < size; i++)
        {
            cout << paths[i]->visitedVertices << endl;
            if (paths[i]->visitedVertices == vertices.size())
            {
                cout << paths[i]->releasedPressure << endl;
                for (int j = 0; j < paths.size(); j++)
                {
                    delete paths[j];
                }
                for (int j = 0; j < vertices.size(); j++)
                {
                    delete vertices[j];
                }
                return;
            }


            neighbors = vector<Vertex*>(paths[i]->lastVisited()->neighbors);
            for (Vertex* v : neighbors)
            {
                paths.push_back(new Path(paths[i], v));
            }

            delete paths[i];
        }
        paths.erase(paths.begin(), paths.begin() + size);
    }
}

void Solver::part02(vector<string> input)
{
    
}
