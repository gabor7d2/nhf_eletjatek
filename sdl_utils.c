#include "sdl_utils.h"

void sdl_init(int width, int height, char *title, SDL_Window **pwindow, SDL_Renderer **prenderer) {
    // SDL inicializálása és ablak megnyitása
    if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        SDL_Log("FATAL: SDL couldn't be initialized: %s", SDL_GetError());
        exit(1);
    }

    SDL_Window *window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        SDL_Log("FATAL: Couldn't create window: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        SDL_Log("FATAL: Couldn't create renderer: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);

    *pwindow = window;
    *prenderer = renderer;
}

void sdl_exit(SDL_Window **pwindow, SDL_Renderer **prenderer) {
    SDL_DestroyWindow(*pwindow);
    *pwindow = NULL;
    SDL_DestroyRenderer(*prenderer);
    *prenderer = NULL;
    SDL_Quit();
}

void set_color(Uint32 value, SDL_Color *color) {
    color->r = (value >> 24) & 0xff;
    color->g = (value >> 16) & 0xff;
    color->b = (value >> 8) & 0xff;
    color->a = value & 0xff;
}

void set_rect(int x, int y, int w, int h, SDL_Rect *rect) {
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;
}

TTF_Font *create_font(char *fontPath, int fontSize) {
    TTF_Font *font = TTF_OpenFont(fontPath, fontSize);
    if (font == NULL) {
        SDL_Log("FATAL: Couldn't open font! %s\n", TTF_GetError());
        exit(3);
    }
    return font;
}

void fill_rect(SDL_Renderer *renderer, SDL_Rect *area, SDL_Color color) {
    if (renderer == NULL) return;

    boxRGBA(renderer, (short) area->x, (short) area->y,
            (short) (area->x + area->w - 1), (short) (area->y + area->h - 1),
            color.r, color.g, color.b, color.a);
}

void fill_rect_offset(SDL_Renderer *renderer, SDL_Rect *area, SDL_Color color, Vector2s offset) {
    if (renderer == NULL) return;
    boxRGBA(renderer,
            (short) (area->x + offset.x), (short) (area->y + offset.y),
            (short) (area->x + area->w + offset.x - 1), (short) (area->y + area->h + offset.y - 1),
            color.r, color.g, color.b, color.a);
}

bool inside_rect(SDL_Rect *rect, SDL_Point *point, SDL_Rect *offset) {
    SDL_Rect offsetedRect = {offset->x + rect->x, offset->y + rect->y, rect->w, rect->h};
    return SDL_PointInRect(point, &offsetedRect);
}