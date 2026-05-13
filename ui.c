#include "ui.h"
#include "raylib.h"
#include <stdbool.h>

/* Nume pentru fiecare skin */
static const char *SKIN_NAMES[8] = {
    "Galben", "Rosu", "Albastru", "Portocaliu",
    "Mov", "Roz", "Limegreen", "Negru"
};

bool btn_clicked(Rectangle r) {
    bool mouse_pressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    bool click_on_button = CheckCollisionPointRec(GetMousePosition(), r);
    
    return mouse_pressed && click_on_button;
}

const char** get_skin_names(void) {
    return (const char**)SKIN_NAMES;
}
