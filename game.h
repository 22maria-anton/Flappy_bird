#ifndef GAME_H
#define GAME_H

#include "types.h"

/* Reseteaza jocul */
void game_reset(Bird *b, Pipe *pipes, int *score, float *t, float *iv);

/* Spawneaza o noua teava */
void pipe_spawn(Pipe *pipes);

/* Verifica lovitura cu tevi */
bool check_pipe_collision(Bird *b, Pipe *pipes);

/* Verifica daca pasarea a cazut jos */
bool check_ground_collision(Bird *b);

#endif
