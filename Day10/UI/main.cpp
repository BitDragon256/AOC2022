#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "libraries/raygui.h"

#include "../../Util.h"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

bool** Display;

int Registry;
int Cycle, NextCycle;
int SpritePos;
int AddValue;
Util::vec2 PixelPos;
struct Operation {
public:
    Operation(string op, int param): operation(op), parameter(param) {}
    string operation;
    int parameter;
};
vector<Operation> Operations;
int OperationIndex;

void UpdateDisplay();


// Screen Constants
namespace SC
{

    const int ScreenDist = 20;
    const int Padding = 20;

    const int DisplayTileCountX = 40;
    const int DisplayTileCountY = 6;
    const int DisplayTileDist = 10;
    const int DisplayTileSize = 30;

    const int DataHeight = 40;
    const int DataDist = 10;
    const int OperationHeight = 20;

    const int ScreenHeight =    ScreenDist * 2                          +
                                Padding * 2                             +
                                DisplayTileDist * (DisplayTileCountY - 1)  + 
                                DisplayTileSize * DisplayTileCountY        +
                                DataHeight                              +
                                OperationHeight * DisplayTileCountX         ;
    const int ScreenWidth =     ScreenDist * 2                          +
                                DisplayTileDist * (DisplayTileCountX - 1)   +
                                DisplayTileSize * DisplayTileCountX         ;

};

int main()
{
    // Operations Reading
    ifstream file("Operations.txt");

    if (file.is_open())
        return -1;
    
    string line;
    vector<string> splitLine;
    while (getline(file, line))
    {
        splitLine = Util::split(line, " ");
        Operations.push_back( Operation(splitLine[0], stoi(splitLine[1])) );
    }

    InitWindow(SC::ScreenWidth, SC::ScreenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

            ClearBackground(RAYWHITE);


            // Draw the Screen
            
            for (int x = 0; x < SC::DisplayTileCountX; x++)
            {
                for (int y = 0; y < SC::DisplayTileCountY; y++)
                {
                    DrawCircle( (float) (x) * SC::DisplayTileSize + x * SC::DisplayTileDist + SC::ScreenDist + SC::DisplayTileSize / 2,
                                (float) (y) * SC::DisplayTileSize + y * SC::DisplayTileDist + SC::ScreenDist + SC::DisplayTileSize / 2,
                                SC::DisplayTileSize / 2, LIGHTGRAY                                                  );
                }
            }

            for (int i = 0; i < 3; i++)
                DrawRectangle(  SC::ScreenDist + i * SC::ScreenWidth / 3 + i * SC::DataDist,
                                SC::ScreenDist + SC::DisplayTileCountY * SC::DisplayTileSize + (SC::DisplayTileCountY - 1) * SC::DisplayTileDist + SC::Padding,
                                SC::ScreenWidth / 3 - SC::ScreenDist * 2 - SC::Padding * 2,
                                SC::DataHeight, LIGHTGRAY);

        EndDrawing();

        // UpdateDisplay();
    }

    CloseWindow();

    delete[] Display;
}

void UpdateDisplay()
{
    Cycle++;

    PixelPos = { (float) (Cycle % SC::DisplayTileCountX), (float) ((int) (Cycle / SC::DisplayTileCountY)) };

    if (NextCycle > Cycle)
    {
        Display[PixelPos.y][PixelPos.x] = Util::clamp(Registry - PixelPos.x, -1, 1) == (Registry - PixelPos.x);
        return;
    }

    Registry += AddValue;
    AddValue = 0;
    OperationIndex++;
    Display[PixelPos.y][PixelPos.x] = Util::clamp(Registry - PixelPos.x, -1, 1) == (Registry - PixelPos.x);

    if (OperationIndex >= Operations.size())
        return;

    if (Operations[OperationIndex].operation == "noop")
    {
        NextCycle++;
        return;
    }

    AddValue = Operations[OperationIndex].parameter;
    NextCycle += 2;
}