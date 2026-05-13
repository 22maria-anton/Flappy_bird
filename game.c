#include "game.h"
#include "config.h"
#include "raylib.h"
#include <stdbool.h>

void game_reset(Bird *b, Pipe *pipes, int *score, float *t, float *iv) {
    b->x  = SW * 0.25f;//pune pasarea la 25% din latimea ecranului
    b->y  = SH * 0.45f;//o pune aprope de centru ecranului
    b->vy = 0.0f;//opreste caderea
    *score = 0;//reseteaza scorul
    *t = 0.0f;//reseteaza timpul
    *iv = 1.8f;//intervalul de aparitie a tavilor
    
    for (int i = 0; i < MAX_PIPES; i++) {
        pipes[i].active = false;
        pipes[i].passed = false;
    }//ia toate tavile si le face inactive,ecranul e curat
}

void pipe_spawn(Pipe *pipes) {
    for (int i = 0; i < MAX_PIPES; i++) {
        if (!pipes[i].active) {
            pipes[i].x      = SW + 10.0f;
            pipes[i].gap_y  = 200.0f + (float)GetRandomValue(0, 270);
            //foloseste o functie din Raylib pentru a da un nr aleator
            pipes[i].passed = false;
            pipes[i].active = true;
            return;
        }
    }
}

bool check_pipe_collision(Bird *b, Pipe *pipes) {
    for (int i = 0; i < MAX_PIPES; i++) {
        if (!pipes[i].active) continue;
//daca o teava nu e activa trece la urmatoarea
        float topH = pipes[i].gap_y - GAP / 2.0f;
        float botY = pipes[i].gap_y + GAP / 2.0f;
//afla unde se termina teava de sus si unde se incepe cea de jos      
        // Dreptunghi pentru pasare (mai mic decât raza pentru hit-box mai mic) 
        Rectangle bR = {
            b->x - BIRD_R + 7,
            b->y - BIRD_R + 7,
            (BIRD_R - 7) * 2.0f,
            (BIRD_R - 7) * 2.0f
        };
        
        /* Dreptunghiuri pentru tevi */
        Rectangle rT = { pipes[i].x, 0,    PIPE_W, topH };
        Rectangle rB = { pipes[i].x, botY, PIPE_W, (float)SH };

        if (CheckCollisionRecs(bR, rT) || CheckCollisionRecs(bR, rB)) {
            return true;
        }//CheckCollisionRec verifica matematic daca se suprapun adica
//daca atinge teva de sus sau jos e game over
    }
    return false;//esti in siguranta
}

bool check_ground_collision(Bird *b) {
    return b->y + BIRD_R >= SH - GROUND || b->y - BIRD_R <= 0;
}
//verifica daca partea de jos a atins solul sau tavanul ecranului
