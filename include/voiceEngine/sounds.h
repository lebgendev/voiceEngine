#ifndef SOUNDS_H
#define SOUNDS_H
#include <cmath>

typedef struct{
    float f1;
    float f2;
    float f3;
    float bw1;
    float bw2;
    float bw3;
    float f1_x1 = 0, f1_x2 = 0, f1_y1 = 0, f1_y2 = 0;
    float f2_x1 = 0, f2_x2 = 0, f2_y1 = 0, f2_y2 = 0;
    float f3_x1 = 0, f3_x2 = 0, f3_y1 = 0, f3_y2 = 0;
} Frequencies;

extern Frequencies i_sound;
extern Frequencies k_sound;
extern Frequencies t_sound;
extern Frequencies v_sound;
extern Frequencies e_sound;
extern Frequencies ae_sound;
extern Frequencies ah_sound;
extern Frequencies a_sound;
extern Frequencies oh_sound;
extern Frequencies oo_sound;
extern Frequencies u_sound;
extern Frequencies er_sound;
extern Frequencies schwa_sound;

extern Frequencies b_sound;
extern Frequencies d_sound;
extern Frequencies g_sound;
extern Frequencies h_sound;
extern Frequencies j_sound;
extern Frequencies z_sound;
extern Frequencies zh_sound;
extern Frequencies th_sound;
extern Frequencies dh_sound;
extern Frequencies m_sound;
extern Frequencies n_sound;
extern Frequencies ng_sound;
extern Frequencies l_sound;
extern Frequencies r_sound;
extern Frequencies w_sound;
extern Frequencies y_sound;

float applyBiquadFilter(float sample, float targetFreq, float bandwidth, int sampleRate, float& x1, float& x2, float& y1, float& y2);
void resetFrequencies(Frequencies &sound);


#endif