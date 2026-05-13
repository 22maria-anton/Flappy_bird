#ifndef TYPES_H
#define TYPES_H

#include "raylib.h"
#include <stdbool.h>

/* Stări ale jocului */
typedef enum { MENU, CHARSEL, PLAY, DEAD } State;

/* Structura pasării */
typedef struct {
    float x, y;    /* Poziție */
    float vy;      /* Viteză verticală */
    int skin;      /* Index skin */
} Bird;

/* Structura țevii (obstacol) */
typedef struct {
    float x;       /* Poziție orizontală */
    float gap_y;   /* Centrul spațiului liber */
    bool passed;   /* Dacă pasarea a trecut */
    bool active;   /* Dacă teava este activă */
} Pipe;

#endif
