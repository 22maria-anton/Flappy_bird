#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "raylib.h"
#include "types.h"

/* Întoarce o culoare mai închisă folosit pentru umbre sa para
pasarea 3d sau butonul */
Color darker(Color c);

/* Desenează pasarea */
void draw_bird(float x, float y, int skin);

/* Desenează o țeavă (obstacol) */
void draw_pipe(float px, float top_h, float bot_y);
//px-pozititia orizontala de la marginea ecranului la teava
//top_h inaltimea tevii de sus
//bot_y ounctul unde teava de jso creste spre pamant

/* Desenează un buton */
void draw_btn(Rectangle r, const char *txt, Color col, int fs);//fs-marimea textului

/* Desenează nori */
void draw_clouds(float cx[4], float cy[4],float time);
//4 nori pe ecran ,avem coordonatele pentru a stabili pozitia pe cer

/* Desenează solul cu animație */
void draw_ground(float gscr);//gscr-ground scroll 

/* Desenează țevile active */
void draw_pipes(Pipe *pipes);

#endif
