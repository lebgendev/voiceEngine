#include <iostream>
#include <cmath>
#include <fstream>
#include "vocaloidEngine/vocaloidEngine.h"

int main(){
    SineOscillator osc(175.0, 0.5);

    osc.initWAV("test2.wav");
    osc.initWAVHeaders();
    osc.generateVowel(0.2, ah_sound);
    osc.generateVowel(0.05, l_sound);
    osc.generateVowel(0.2, u_sound);
    osc.generateVowel(0.05, v_sound);
    osc.generateVoicelessConsonant(t_sound);
    osc.generateVowel(0.2, e_sound);
    osc.generateVoicelessConsonant(t_sound);
    osc.generateVowel(0.2, oh_sound);

    osc.finalizeWAV();
    osc.closeWAV();

    return 0;
}