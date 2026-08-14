#include "sounds.h"

float applyBiquadFilter(float sample, float targetFreq, float bandwidth, int sampleRate, float& x1, float& x2, float& y1, float& y2){
    float omega = 2.0f * M_PI * targetFreq / sampleRate;

    float Q = targetFreq / bandwidth;
    float alpha = sin(omega) / (2.0f * Q);

    float b0 = alpha;
    float b1 = 0.0f;
    float b2 = -alpha;

    float a0 = 1.0f + alpha;
    float a1 = -2.0f * cos(omega);
    float a2 = 1.0f - alpha;

    b0 /= a0;
    b1 /= a0;
    b2 /= a0;
    a1 /= a0;
    a2 /= a0;

    float y0 =
        b0 * sample +
        b1 * x1 +
        b2 * x2 -
        a1 * y1 -
        a2 * y2;

    x2 = x1;
    x1 = sample;

    y2 = y1;
    y1 = y0;

    return y0;
}

void resetFrequencies(Frequencies &sound){
    sound.f1_x1 = 0;
    sound.f1_x2 = 0;
    sound.f1_y1 = 0;
    sound.f1_y2 = 0;

    sound.f2_x1 = 0;
    sound.f2_x2 = 0;
    sound.f2_y1 = 0;
    sound.f2_y2 = 0;

    sound.f3_x1 = 0;
    sound.f3_x2 = 0;
    sound.f3_y1 = 0;
    sound.f3_y2 = 0;
}

Frequencies i_sound = {240.0f, 2400.0f, 3000.0f, 60.0f, 100.0f, 120.0f};
Frequencies e_sound = {530.0f, 1840.0f, 2480.0f, 70.0f, 100.0f, 120.0f};
Frequencies ae_sound = {660.0f, 1720.0f, 2410.0f, 80.0f, 100.0f, 120.0f};
Frequencies ah_sound = {730.0f, 1090.0f, 2440.0f, 80.0f, 90.0f, 120.0f};
Frequencies a_sound = {850.0f, 1610.0f, 2700.0f, 100.0f, 120.0f, 150.0f};
Frequencies oh_sound = {450.0f, 800.0f, 2830.0f, 70.0f, 80.0f, 120.0f};
Frequencies oo_sound = {350.0f, 600.0f, 2400.0f, 70.0f, 80.0f, 120.0f};
Frequencies u_sound = {300.0f, 870.0f, 2240.0f, 60.0f, 90.0f, 120.0f};
Frequencies er_sound = {490.0f, 1350.0f, 1690.0f, 80.0f, 100.0f, 120.0f};
Frequencies schwa_sound = {500.0f, 1500.0f, 2500.0f, 80.0f, 100.0f, 120.0f};


Frequencies b_sound = {
    500.0f, 1200.0f, 2500.0f,
    700.0f, 1000.0f, 1500.0f
};

Frequencies d_sound = {
    1500.0f, 3000.0f, 5000.0f,
    700.0f, 1200.0f, 1800.0f
};

Frequencies g_sound = {
    2000.0f, 3500.0f, 5500.0f,
    800.0f, 1200.0f, 1800.0f
};

Frequencies h_sound = {
    1200.0f, 2500.0f, 4000.0f,
    1000.0f, 1500.0f, 2000.0f
};

Frequencies j_sound = {
    1800.0f, 3500.0f, 6000.0f,
    900.0f, 1500.0f, 2200.0f
};

Frequencies z_sound = {
    3500.0f, 6000.0f, 8500.0f,
    1500.0f, 2200.0f, 3000.0f
};

Frequencies zh_sound = {
    1800.0f, 3200.0f, 5000.0f,
    1200.0f, 1700.0f, 2500.0f
};

Frequencies th_sound = {
    2500.0f, 5000.0f, 8000.0f,
    1200.0f, 2000.0f, 3000.0f
};

Frequencies dh_sound = {
    1200.0f, 3000.0f, 5000.0f,
    1000.0f, 1800.0f, 2500.0f
};

Frequencies m_sound = {
    250.0f, 1000.0f, 2500.0f,
    100.0f, 300.0f, 700.0f
};

Frequencies n_sound = {
    300.0f, 1700.0f, 2500.0f,
    120.0f, 400.0f, 700.0f
};

Frequencies ng_sound = {
    300.0f, 2200.0f, 3000.0f,
    100.0f, 500.0f, 800.0f
};

Frequencies l_sound = {
    400.0f, 1200.0f, 3000.0f,
    100.0f, 400.0f, 800.0f
};

Frequencies r_sound = {
    300.0f, 1500.0f, 1700.0f,
    100.0f, 400.0f, 500.0f
};

Frequencies w_sound = {
    300.0f, 900.0f, 2200.0f,
    100.0f, 300.0f, 600.0f
};

Frequencies y_sound = {
    250.0f, 2200.0f, 3000.0f,
    100.0f, 500.0f, 800.0f
};