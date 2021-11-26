#ifndef ELETJATEK_TYPEDEFS_H
#define ELETJATEK_TYPEDEFS_H

#include <SDL.h>
#include <stdbool.h>
#include <SDL_ttf.h>

// Enum a cellaállapotokhoz
typedef enum {
    DEAD, LIVE
} CellState;

typedef enum {
    CLICKME
} MenuAction;

typedef struct {
    short x, y;
} Vector2s;

typedef struct {
    double x, y;
} Vector2d;

// Struct a játéktér (cellák) tárolására
typedef struct {
    // Jelenlegi cellák és új cellák
    // (a newCells tömbbe kerülnek a következő iteráció cellaértékei majd a 2 fel lesz cserélve)
    CellState **cells, **newCells;
    // Cellák mennyisége mindkét irányban
    short sizeX, sizeY;
} GameField;

// Struct a grid paramétereknek
typedef struct {
    SDL_Rect gameArea;
    Vector2s borderWidth, padding, cells;
    Vector2d cellSize;
    SDL_Color *deadColor, *liveColor, *borderColor, *bgColor;
} GridParams;

// Struct a szimulációhoz szükséges adatok mozgatására
typedef struct {
    bool *running, *renderNeeded;
    int *speedMs;
    GameField *gameField;
} SimData;

typedef struct {
    int w, h;
    SDL_Texture *texture;
} Text;

typedef struct {
    SDL_Rect area;
    Text text;
    bool hovered, clicked;
    MenuAction action;
} Button;

typedef struct {
    SDL_Rect area;
    TTF_Font *font;
    char *text;
    bool hovered, clicked, selected;
} TextField;

typedef struct {
    SDL_Rect *area;
    SDL_Color *bgColor;
    int buttonCount;
    Button **buttons;
    int textFieldCount;
    TextField **textFields;
} Menu;

#endif //ELETJATEK_TYPEDEFS_H
