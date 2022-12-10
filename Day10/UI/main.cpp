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
const int Display_WIDTH = 40;
const int Display_HEIGHT = 6;

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

int main()
{
    // Operations Reading
    ifstream file("Operations.txt");

    vector<string> Operations;

    if (file.is_open())
        return -1;
    
    string line;
    vector<string> splitLine;
    while (getline(file, line))
    {
        splitLine = Util::split(line, " ");
        Operations.push_back( Operation(splitLine[0], stoi(splitLine[1])) );
    }

    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    delete[] Display;
}

void UpdateDisplay()
{
    Cycle++;

    PixelPos = { (float) (Cycle % Display_WIDTH), (float) ((int) (Cycle / Display_HEIGHT)) };

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