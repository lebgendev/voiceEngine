#include <iostream>
#include <cmath>
#include <fstream>
#include "vocaloidEngine/vocaloidEngine.h"

int main(){
    SineOscillator osc(200.0, 0.5);

    osc.initWAV("test_new.wav");
    osc.initWAVHeaders();
    osc.generateVowel(0.5, ah_sound);
    osc.generateVowel(0.05, l_sound);
    osc.generateVowel(0.5, u_sound);
    osc.generateVowel(0.05, v_sound);
    osc.generateVowel(0.05, y_sound);
    osc.generateVowel(0.5, oo_sound);

    osc.finalizeWAV();
    osc.closeWAV();

    return 0;
}