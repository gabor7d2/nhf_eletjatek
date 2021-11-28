#include "menu_element.h"
#include "menu_text.h"
#include "sdl_utils.h"

MenuElement *create_menu_element(SDL_Renderer *renderer, SDL_Rect area, MenuAction action, MenuElementType type,
                           char *text, TTF_Font *textFont, Uint32 textColor, MenuElementColors colors) {
    MenuElement *btn = (MenuElement *) malloc(sizeof(MenuElement));
    btn->area = area;
    btn->action = action;
    btn->type = type;
    btn->colors = colors;
    btn->text = create_text(renderer, area, text, textFont, textColor);
    btn->interactAlpha = 0;
    btn->clicked = false;
    return btn;
}

MenuElement *create_button(SDL_Renderer *renderer, SDL_Rect area, MenuAction action,
                           char *text, TTF_Font *textFont, Uint32 textColor, MenuElementColors colors) {
    return create_menu_element(renderer, area, action, BUTTON, text, textFont, textColor, colors);
}

MenuElement *create_text_field(SDL_Renderer *renderer, SDL_Rect area, MenuAction action,
                           char *text, TTF_Font *textFont, Uint32 textColor, MenuElementColors colors) {
    return create_menu_element(renderer, area, action, TEXTFIELD, text, textFont, textColor, colors);
}

void edit_element_text(SDL_Renderer *renderer, MenuElement *element, char *newText) {
    edit_text(renderer, element->text, element->area, newText);
}

void draw_element(SDL_Renderer *renderer, MenuElement *element, Vector2s offset) {
    SDL_Rect innerArea = {element->area.x + 4, element->area.y + 4, element->area.w - 8, element->area.h - 8};
    fill_rect_offset(renderer, &element->area, element->colors.edgeColor, offset);
    fill_rect_offset(renderer, &innerArea, element->colors.normalColor, offset);

    SDL_Color interactColor = element->colors.interactColor;
    interactColor.a = element->clicked ? 200 : element->interactAlpha;

    fill_rect_offset(renderer, &innerArea, interactColor, offset);
}

void free_element(MenuElement *element) {
    free(element);
}