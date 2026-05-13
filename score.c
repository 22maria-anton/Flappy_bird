#include "score.h"
#include "config.h"
#include <stdio.h>
#include <stdbool.h>

//am facut acest cod pentru salvarea si incarcarea celui mai mare scor
void hs_load(int *high_score) {
    FILE *f = fopen(HIGH_SCORE_FILE, "r");
    if (f != NULL) {
        fscanf(f, "%d", high_score);
        fclose(f);
    }
}

void hs_save(int new_score, int *high_score, bool *new_record) {
    *new_record = (new_score > *high_score);
    if (*new_record) {
        *high_score = new_score;
        FILE *f = fopen(HIGH_SCORE_FILE, "w");
        if (f != NULL) {
            fprintf(f, "%d", *high_score);
            fclose(f);
        }
    }
}
