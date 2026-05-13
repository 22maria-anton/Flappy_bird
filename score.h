#ifndef SCORE_H
#define SCORE_H

#include <stdbool.h>

/* Șterge recordul anterior și setează noul */
void hs_save(int new_score, int *high_score, bool *new_record);

/* Încarcă recordul din fișier */
void hs_load(int *high_score);

#endif
