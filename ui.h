#ifndef UI_H
#define UI_H

#include "raylib.h"
#include <stdbool.h>

/* Verifică dacă un buton a fost apăsat */
bool btn_clicked(Rectangle r);

/* Returnează lista cu numele skin-urilor */
const char** get_skin_names(void);

#endif
