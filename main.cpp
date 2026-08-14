#include <iostream>
#include <cmath>
#include <fstream>
#include "vocaloidEngine/vocaloidEngine.h"

int main(){
    int duration = 2;
    SineOscillator osc(200.0, 0.5);

    osc.initWAV("test_new.wav");
    osc.initWAVHeaders();
    osc.generateConsonant(h_sound);
    osc.generateVowel(0.5, a_sound);
    osc.generateVowel(0.05, l_sound);
    osc.generateVowel(3, oo_sound);

    osc.finalizeWAV();
    osc.closeWAV();

    return 0;
}