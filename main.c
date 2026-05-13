#include "raylib.h"
#include "config.h"
#include "types.h"
#include "game.h"
#include "graphics.h"
#include "ui.h"
#include "score.h"
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

int main(void) {
    InitWindow(SW, SH, "Flappy Bird - C + Raylib");
    SetTargetFPS(60);//jocul ruleaza cu 60 cadre pe secunda

    /* Inițializare */
    State state = MENU;
    Bird bird = { SW * 0.25f, SH * 0.45f, 0.0f, 0 };
    Pipe pipes[MAX_PIPES];
    for (int i = 0; i < MAX_PIPES; i++)
        pipes[i].active = pipes[i].passed = false;

    int high_score = 0;
    bool new_record = false;
    hs_load(&high_score);

    int score = 0;
    float sp_t = 0.0f, sp_iv = 1.8f;
//la sp_timp se genereaza o noua teava,si la fiecare 1.8 secunde apare una noua

    /* Poziții nori (animație) */
    float cx[4] = {80.0f, 210.0f, 350.0f, 450.0f};
    float cy[4] = {80.0f, 115.0f,  72.0f, 130.0f};

    float gscr = 0.0f;//deplasarea solului 
    float mb_y = SH * 0.32f, mb_d = 1.0f;//pasarea se misca sus-jos pentru animatie

    /* Butoane MENU */
    //format e {x,y,widtch,height}
    Rectangle r_start = {SW / 2.0f - 100, SH * 0.52f,     200, 54};
    Rectangle r_sel   = {SW / 2.0f - 100, SH * 0.52f + 65, 200, 54};//+65 e mai jos cu 65 pixeli
    Rectangle r_exit  = {SW / 2.0f - 100, SH * 0.52f + 130, 200, 54};
    /* Butoane CHARSEL */
    Rectangle r_back  = {SW / 2.0f - 100, SH * 0.80f,     200, 54};
    /* Butoane DEAD */
    Rectangle r_retry = {SW / 2.0f - 95, SH * 0.62f,      190, 52};
    Rectangle r_menu2 = {SW / 2.0f - 95, SH * 0.62f + 65, 190, 52};

    const char **skin_names = get_skin_names();

    /* BUCLA PRINCIPALĂ */
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        if (dt > 0.05f) dt = 0.05f;   /* protecție spike de timp */

        /* Viteza crește cu scorul maxim pana la 520*/
        float speed = 220.0f + score * 10.0f;
        if (speed > 520.0f) speed = 520.0f;

        /* Scroll nori + sol */
        for (int i = 0; i < 4; i++) {
            cx[i] -= 28.0f * dt;//misca norul la stanga
            if (cx[i] < -130.0f) cx[i] = SW + 130.0f;//daca norul a iesit din stanga ecranului apare in dreaota
        }
        gscr += speed * dt * 0.22f;//solul se misca cu viteza jocului
        if (gscr > 48.0f) gscr -= 48.0f;
//solul are o textura care se repeta la 48 pixeli cand o depaseste se reseteaz

        /* MAȘINA DE STĂRI */
        switch (state) {

        case MENU:
            mb_y += mb_d * 55.0f * dt;//misca pasarea
            if (mb_y > SH * 0.37f) mb_d = -1.0f;//daca ajunge prea sus coboara
            if (mb_y < SH * 0.29f) mb_d =  1.0f;

            if (IsKeyPressed(KEY_SPACE) || btn_clicked(r_start)) {
                game_reset(&bird, pipes, &score, &sp_t, &sp_iv);
                state = PLAY;
            } else if (btn_clicked(r_sel)) {
                state = CHARSEL;
            } else if (btn_clicked(r_exit)) {
                CloseWindow();
                return 0;
            }
            break;

        case CHARSEL:
            if (IsKeyPressed(KEY_ESCAPE) || btn_clicked(r_back))
                state = MENU;

            for (int i = 0; i < N_SKINS; i++) {
                float rx = SW / 2.0f - 155 + (i % 3) * 110;
                float ry = SH * 0.22f + (i / 3) * 130;//calcul pozitii(3coloane,2randuri)
                if (btn_clicked((Rectangle){rx, ry, 90, 90}))//daca dam click pe skin
                    bird.skin = i;//selectam acel skin
            }
            break;

        case PLAY:
            if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                bird.vy = FLAP;//pasarea bate din aripi

            bird.vy += GRAVITY * dt;
            bird.y  += bird.vy  * dt;

            sp_t += dt;//acumuleaza timp
            if (sp_t >= sp_iv) {//daca sa terminat intervalul
                pipe_spawn(pipes);//creeaza o noua teava
                sp_t  = 0.0f;//reset timer
                sp_iv = 1.8f - score * 0.04f;//urmatorul interval il face mai scurt
                if (sp_iv < 0.9f) sp_iv = 0.9f;
            }

            /* Actualizează tevi și verifica coliziuni */
            for (int i = 0; i < MAX_PIPES; i++) {
                if (!pipes[i].active) continue;
                pipes[i].x -= speed * dt;

                if (!pipes[i].passed && pipes[i].x + PIPE_W < bird.x) {
                    pipes[i].passed = true;
                    score++;
                }
                if (pipes[i].x + PIPE_W < 0)//daca teava a iesit din ecran
                    pipes[i].active = false;
            }

            /* Verifică coliziuni */
            if (check_pipe_collision(&bird, pipes) || check_ground_collision(&bird)) {
                hs_save(score, &high_score, &new_record);
                state = DEAD;
            }
            break;

        case DEAD:
            bird.vy += GRAVITY * dt;
            bird.y  += bird.vy  * dt;
            if (bird.y > SH - GROUND - BIRD_R) {//daca a atins solul
                bird.y  = (float)(SH - GROUND - BIRD_R);//fixeazo pe sol
                bird.vy = 0.0f;//nu mai cade 
            }

            if (IsKeyPressed(KEY_SPACE) || btn_clicked(r_retry)) {
                game_reset(&bird, pipes, &score, &sp_t, &sp_iv);
                state = PLAY;
            } else if (btn_clicked(r_menu2)) {
                state = MENU;
            }
            break;
        }

        /* DESENARE */
        BeginDrawing();
        ClearBackground((Color){113, 197, 207, 255});

        draw_clouds(cx, cy,GetTime());
        draw_pipes(pipes);
        draw_ground(gscr);

        if (state != MENU)
            draw_bird(bird.x, bird.y, bird.skin);

        /* UI STĂRI */
        switch (state) {

        case MENU: {
            /* Titlu cu umbra */
            DrawText("FLAPPY BIRD",
                     SW / 2 - MeasureText("FLAPPY BIRD", 46) / 2 + 2, 74, 46,
                     (Color){0, 0, 0, 90});
            DrawText("FLAPPY BIRD",
                     SW / 2 - MeasureText("FLAPPY BIRD", 46) / 2, 72, 46, WHITE);

            /* Pasarea animata */
            draw_bird(SW / 2.0f, mb_y, bird.skin);

            /* Record */
            if (high_score > 0) {
                char buf[32];
                sprintf(buf, "Record: %d", high_score);
                DrawText(buf, SW / 2 - MeasureText(buf, 22) / 2,
                         (int)(SH * 0.44f), 22, YELLOW);
            }//afiseaza recordul daca e mai mare ca 0

            /* Butoane */
            draw_btn(r_start, "INCEPE JOC",     (Color){50, 185, 50, 255},  20);
            draw_btn(r_sel,   "ALEGE PERSONAJ", (Color){50, 130, 230, 255}, 17);
            draw_btn(r_exit,  "IESIRE",         (Color){210, 50, 50, 255},  20);

            DrawText("SPATIU sau Click = Start",
                     SW / 2 - MeasureText("SPATIU sau Click = Start", 14) / 2,
                     SH - GROUND - 24, 14, (Color){255, 255, 255, 180});
            break;
        }

        case CHARSEL: {
            DrawText("ALEGE PERSONAJUL",
                     SW / 2 - MeasureText("ALEGE PERSONAJUL", 28) / 2,
                     55, 28, WHITE);

            for (int i = 0; i < N_SKINS; i++) {
                float rx = SW / 2.0f - 155 + (i % 3) * 110;
                float ry = SH * 0.22f + (i / 3) * 130;
                Rectangle r = {rx, ry, 90, 90};

                DrawRectangleRec(r, (i == bird.skin)
                    ? (Color){255, 255, 255, 80} : (Color){0, 0, 0, 50});
//daca skinul e selectat culoarea alb semi-transparent daca nu negru semi-transparent
                if (i == bird.skin)
                    DrawRectangleLinesEx(r, 3, YELLOW);

                draw_bird(rx + 45, ry + 37, i);
                DrawText(skin_names[i],
                         (int)(rx + 45 - MeasureText(skin_names[i], 13) / 2),
                         (int)(ry + 68), 13, WHITE);
            }

            draw_btn(r_back, "INAPOI", (Color){200, 50, 50, 255}, 20);
            DrawText("ESC = Inapoi",
                     SW / 2 - MeasureText("ESC = Inapoi", 14) / 2,
                     (int)(SH * 0.89f), 14, LIGHTGRAY);
            break;
        }

        case PLAY: {
            char buf[16];
            sprintf(buf, "%d", score);
            DrawText(buf, SW / 2 - MeasureText(buf, 50) / 2 + 2, 42, 50,
                     (Color){0, 0, 0, 80});
            DrawText(buf, SW / 2 - MeasureText(buf, 50) / 2, 40, 50, WHITE);

            char sp_buf[32];
            sprintf(sp_buf, "Viteza: %.0f", speed);
            DrawText(sp_buf, 10, 10, 16, (Color){255, 255, 255, 210});

            DrawText("SPATIU / Click = Zbor",
                     SW / 2 - MeasureText("SPATIU / Click = Zbor", 14) / 2,
                     SH - GROUND - 22, 14, (Color){255, 255, 255, 160});
            break;
        }

        case DEAD: {
            DrawRectangle(0, 0, SW, SH, (Color){0, 0, 0, 110});

            DrawText("GAME OVER",
                     SW / 2 - MeasureText("GAME OVER", 50) / 2,
                     (int)(SH * 0.22f), 50, RED);

            char s1[32], s2[32];
            sprintf(s1, "Scor: %d",   score);
            sprintf(s2, "Record: %d", high_score);
            DrawText(s1, SW / 2 - MeasureText(s1, 28) / 2, (int)(SH * 0.40f), 28, WHITE);
            DrawText(s2, SW / 2 - MeasureText(s2, 26) / 2, (int)(SH * 0.47f), 26, YELLOW);

            if (new_record && score > 0)
                DrawText("NOU RECORD!",
                         SW / 2 - MeasureText("NOU RECORD!", 22) / 2,
                         (int)(SH * 0.54f), 22, (Color){255, 215, 0, 255});

            draw_btn(r_retry, "INCEARCA DIN NOU", (Color){50, 185, 50, 255},  15);
            draw_btn(r_menu2, "MENIU PRINCIPAL",  (Color){50, 130, 230, 255}, 15);

            DrawText("SPATIU = Incearca din nou",
                     SW / 2 - MeasureText("SPATIU = Incearca din nou", 14) / 2,
                     (int)(SH * 0.87f), 14, LIGHTGRAY);
            break;
        }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
