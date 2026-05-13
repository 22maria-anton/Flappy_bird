#ifndef CONFIG_H
#define CONFIG_H

/* Dimensiuni fereastră */
#define SW          480      // screen width latime fereastra            
#define SH          720     // inaltime fereastra           

/* Fizică și mecanici */
#define GRAVITY     900.0f //cu cat cade pasarea pe secund
#define FLAP       -380.0f   // impuls la batai din aripi    

/* Țevi și obstacole */
#define PIPE_W       65      // latimea tevii                
#define GAP         175      // spatiul dintre tevi          
#define MAX_PIPES     6

/* Teren și pasare */
#define GROUND      100      // inaltimea solului            
#define BIRD_R       22      // raza pasarela                
#define N_SKINS       8

/* Fișier înregistrări */
#define HIGH_SCORE_FILE "hs.dat"

#endif
