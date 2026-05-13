#include "graphics.h"
#include "config.h"
#include "raylib.h"
#include<math.h>

/* Paletă de culori pentru skins */
static const Color SKINS[N_SKINS] = {
    YELLOW, RED, SKYBLUE, ORANGE, PURPLE, (Color){255, 179, 179, 255}, LIME, BLACK
};

Color darker(Color c) {
    return (Color){
        (unsigned char)(c.r * 0.70f),//reduce intensitatea de rosu
        (unsigned char)(c.g * 0.70f),//de green
        (unsigned char)(c.b * 0.70f),//de blue
        c.a
    };
}//fara asta pasarea ar fi plata

void draw_bird(float x, float y, int skin) {
    Color c = SKINS[skin];
    
    /* Corp */
    DrawCircle((int)x, (int)y, BIRD_R, c);
//deseneaza un cerc de c-culoare ,centru la(x,y),raza-Bird_R pixeli

    /* Aripa */
    DrawCircle((int)(x - 8), (int)(y + 6), 10, darker(c));
//un cerc mai mic cu centru mai la stanga si mai jos,culoarea mai inchisa

    /* Ochi */
    DrawCircle((int)(x + 10), (int)(y - 7), 6, WHITE);
    DrawCircle((int)(x + 12), (int)(y - 7), 3, BLACK);
    
    /* Cioc */
    DrawTriangle(
        (Vector2){x + BIRD_R,      y - 4},
        (Vector2){x + BIRD_R + 12, y + 1},
        (Vector2){x + BIRD_R,      y + 6},
        ORANGE
    );
}

void draw_pipe(float px, float top_h, float bot_y) {
    Color body = (Color){83,  167,  72, 255};
    Color cap  = (Color){59,  130,  50, 255};
    
    /* Teava sus */
    DrawRectangle((int)px,      0,             PIPE_W,      (int)top_h, body);
    DrawRectangle((int)px - 6,  (int)(top_h - 28), PIPE_W+12, 28,        cap);
    
    /* Teava jos */
    DrawRectangle((int)px,      (int)bot_y,    PIPE_W,      SH,         body);
    DrawRectangle((int)px - 6,  (int)bot_y,    PIPE_W+12,   28,         cap);
}

void draw_btn(Rectangle r, const char *txt, Color col, int fs) {
    DrawRectangleRec(r, col);
    DrawRectangleLinesEx(r, 3, darker(col));
    int tw = MeasureText(txt, fs);
    DrawText(txt,
             (int)(r.x + r.width  / 2 - tw / 2),
             (int)(r.y + r.height / 2 - fs / 2),
             fs, WHITE);
}

void draw_clouds(float cx[4], float cy[4], float time) {
    for (int i = 0; i < 4; i++) {
        float bob = sinf(time + i) * 2;  // Mișcare sus-jos
        
        DrawEllipse((int)cx[i], (int)(cy[i] + bob), 52, 22, WHITE);
        DrawEllipse((int)cx[i] - 30, (int)(cy[i] + 10 + bob), 36, 18, WHITE);
        DrawEllipse((int)cx[i] + 34, (int)(cy[i] + 8 + bob), 38, 20, WHITE);
    }
}

void draw_ground(float gscr) {
    DrawRectangle(0, SH - GROUND, SW, GROUND, (Color){222, 193, 143, 255});
    DrawRectangle(0, SH - GROUND, SW, 14,     (Color){111, 196, 89, 255});
    for (int x = -(int)gscr; x < SW; x += 48)
        DrawRectangle(x, SH - GROUND + 14, 24, 8, (Color){200, 175, 130, 255});
}

void draw_pipes(Pipe *pipes) {
    for (int i = 0; i < MAX_PIPES; i++) {
        if (pipes[i].active) {
            draw_pipe(pipes[i].x,
                      pipes[i].gap_y - GAP / 2.0f,
                      pipes[i].gap_y + GAP / 2.0f);
        }
    }
}
